//-------------------------------------------------------------------------------------------------------------------
// Include Libraries
#include <esp_now.h>                  // for ESP NOW communication
#include <WiFi.h>                     // for ESP NOW communication
#include "Protocentral_ADS1220_mod.h" // for ADS1220 communication
#include <SPI.h>                      // for ADS1220 communication

//-------------------------------------------------------------------------------------------------------------------
// Define Pins

// ADS1220 (4x)
int CS_Pins[] = {12, 13, 14, 15};
int DRDY_Pins[] = {8, 9, 10, 11};
#define SCK     7   // SPI Clock
#define MISO    6   // SPI MISO
#define MOSI    5   // SPI MOSI
#define SS      12  // Chip Select for ADC1, usable for SPI.begin(); -> for library. Later only the CS_Pins-array is used for CS pins.

// LEDs
#define LED1 33   // LED Green    -> status indicator if program is working
#define LED2 34   // LED Green    -> battery status indicator, blinking if VCC is below a threshold
#define LED3 35   // LED Blue     -> status indicator if UART2 is connected/working
#define LED4 36   // LED Blue     -> status indicator if ESP NOW is connected

#define VCC 1       // VCC, measured with internal ADC of ESP32

// UART2 Pins
#define UART2TXD 4  
#define UART2RXD 37

// 5V generation enable
#define EN_5V 48

//-------------------------------------------------------------------------------------------------------------------
// Settings and constants

uint8_t broadcastAddress1[] = {0x08, 0x3a, 0xf2, 0xb9, 0x02, 0x40};   // REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS

bool esp_now_connection = false;  // Decide if ESPNOW connection shall be used or not (required for ESP to ESP wireless connection)
bool uart2_connection = true;     // Decide if UART2 shall be used (required for Nextion display)
bool voltage_generation = true;   // Decide if the 5V voltage generation should work (required for Nextion display)

#define UART2BAUD 115200          // Define the baud rate for UART2 communication

#define CF 360                    // Feedback capacitance [pF] (Q = C * U, Charge = CF * Voltage)
double maxCharge = 1.7 * CF;      // max voltage (plus or minus) * feedback capacitance.

#define thresVCC 3.2              // Threshold for VCC, where the battery indicator should start blinking (ESP 32 recommended minimum voltage is 3.0V)

#define PGA          1                        // ADS1220, Programmable Gain = 1
#define VREFADC      3.28                     // ADS1220, Reference voltage
#define VFSR         VREFADC/PGA              // ADS1220
#define FULL_SCALE   (((long int)1<<23)-1)    // ADS1220

//-------------------------------------------------------------------------------------------------------------------
// Variables

int lastBlink;                // time of last blink for LED1 blinking
int lastBlinkBattery;         // time of last blink for Battery Warning LED2
bool uartConnected;           // marker wheter UART2 is connected or not -> shown by blue LED3
bool espNowConnected;         // marker whether ESP NOW is connected -> shown by blue LED4
bool batteryAlert;            // marker if the voltage is too low

Protocentral_ADS1220_mod adc[4];  // Four ADCs...
int32_t adc_data[4];          // ... and a place to store their readings

int displayPage;              // display page as int. 1 is the first page, 7 the last one.

// Struct, in which all measurement data is stored
typedef struct four_ch_struct {
  double vcc;
  double vref;
  double ferro1;
  double ferro2;
  double ferro3;
  double ferro4;
} four_ch_struct;

four_ch_struct data_struct;

//-------------------------------------------------------------------------------------------------------------------
// Setup for ESP_NOW
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  /*
  // Debug Information
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
          mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  */
}
//-------------------------------------------------------------------------------------------------------------------
// Setup for UART2

// used for display here (NX3224K024)
HardwareSerial displaySerial(2);
String endChar = String(char(0xff)) + String(char(0xff)) + String(char(0xff));

//-------------------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);
  Serial.println("Setup started.");

  batteryAlert = false;

  // -------------------------------------------------------
  // 5V generation setup
  pinMode(EN_5V, OUTPUT);         // 5V generation pin is output
  if (voltage_generation) {
    digitalWrite(EN_5V, HIGH);    // 5V shall be generated
    delay(200);                   // Delay that the display or other connected device can start.
  } else {
    digitalWrite(EN_5V, LOW);
  }
  
  // -------------------------------------------------------
  // ESP NOW Start
  espNowConnected = false;

  if (esp_now_connection) {
    WiFi.mode(WIFI_STA);
  
    if (esp_now_init() != ESP_OK) {
      Serial.println("Error initializing ESP-NOW");
      espNowConnected = false;
    } else {
      espNowConnected = true;
    }
    
    esp_now_register_send_cb(OnDataSent);
    
    // register peer
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    // register first peer  
    memcpy(peerInfo.peer_addr, broadcastAddress1, 6);
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      Serial.println("Failed to add peer");
      espNowConnected = false;
    } else {
      espNowConnected = true;
    }
  }
  // -------------------------------------------------------
  // UART2 Connection
  uartConnected = false;

  // If UART2 connection is wished, it is started here.
  if (uart2_connection) {
    displaySerial.begin(UART2BAUD, SERIAL_8N1, UART2RXD, UART2TXD);
    Serial.print("UART2 connection started with baud rate ");
    Serial.println(UART2BAUD);

    displaySerial.print(endChar);                           // Send end Char to start a clean conversation
    displaySerial.print("page All_Channels_A" + endChar);   // Send page command to start on the first page.
    displayPage = 1;
  }  

  // -------------------------------------------------------

  pinMode(LED1, OUTPUT);        // LEDs as digital output pins (Program working)
  pinMode(LED2, OUTPUT);        // ...  (Battery Status)
  pinMode(LED3, OUTPUT);        // ...  (UART2 connected)
  pinMode(LED4, OUTPUT);        // ...  (ESP NOW connected)

  startupLEDshow();             // Little lightshow at the start, because it is cool.
  
  setupADCs();
  
  // Initialisieren von Variablen (für LEDs)
  lastBlink = millis();
  lastBlinkBattery = millis();

  Serial.println("Setup finished.");
}

//-------------------------------------------------------------------------------------------------------------------

void loop() {

  refreshLEDs();        // update LEDs for blinking and status etc.
  readoutADCs();        // read ADC data from all four ADCs

  data_struct.vcc = getVCC();                           // read and store VCC (internal ADC)
  data_struct.vref = getVRef();                         // read and store VRef (internal ADC)
  data_struct.ferro1 = convertToPicoC(adc_data[0]);    // compute charge of Ferro 1 (ADS1220)
  data_struct.ferro2 = convertToPicoC(adc_data[1]);    // compute charge of Ferro 2(ADS1220)
  data_struct.ferro3 = convertToPicoC(adc_data[2]);    // compute charge of Ferro 3 (ADS1220)
  data_struct.ferro4 = convertToPicoC(adc_data[3]);    // compute charge of Ferro 4 (ADS1220)

  //data_struct.ferro1 = convertToMilliV(adc_data[0]);    // compute voltage of Ferro 1 (ADS1220)
  //data_struct.ferro2 = convertToMilliV(adc_data[1]);    // compute voltage of Ferro 2(ADS1220)
  //data_struct.ferro3 = convertToMilliV(adc_data[2]);    // compute voltage of Ferro 3 (ADS1220)
  //data_struct.ferro4 = convertToMilliV(adc_data[3]);    // compute voltage of Ferro 4 (ADS1220)

  // Serial print the measured values
  // -> Serial print should work with BetterSerialPlotter on a PC
  // VCC und VRef
  // Serial.print(data_struct.vcc, 6);       // The number (6) indicates how many decimal digits will be shown.
  // Serial.print(" ");
  // Serial.print(data_struct.vref, 6);
  // Serial.print(" ");

  // Four Channel
  Serial.print(data_struct.ferro1, 6);
  Serial.print(" ");
  Serial.print(data_struct.ferro2, 6);
  Serial.print(" ");
  Serial.print(data_struct.ferro3, 6);
  Serial.print(" ");
  Serial.print(data_struct.ferro4, 6);
  Serial.print(" ");
  
  // --------------------------------------------------------------------
  // End print with new line
  Serial.println();

  // --------------------------------------------------------------------
  // Send data via ESPNOW
  if (esp_now_connection) {
    esp_err_t result = esp_now_send(0, (uint8_t *) &data_struct, sizeof(four_ch_struct));
    
    if (result == ESP_OK) {
      Serial.println("Sent with success");
      espNowConnected = true;
    }
    else {
      Serial.println("Error sending the data");
      espNowConnected = false;
    }
  }

  // send data via UART2 (to display)
  if (uart2_connection) {
    uartConnected = true;
    readFromDisplay();
    sendDataToDisplay();
  }
}
// End of loop

//-------------------------------------------------------------------------------------------------------------------

// Calculates the VCC voltage from the analog read of BatState
double getVCC() {
  int batState = analogRead(VCC);
  // Factor 11 from voltage divider
  double vcc = 11 * batState * (3.3 / 4095);
  if (vcc < thresVCC) {
    batteryAlert = true;
  } else {
    batteryAlert = false;
  }
  return vcc;
}

// Calculates the VRef voltage from the analog read of VRef
double getVRef() {
  // Read AIN1 (absolute) of any of the four ADCs (here Nr. 0), then return to the usual measurement mode of that ADC (differential Input!)
  // Do all this only if the VRef is shown on the display, otherwise this just reduces performance.
  if (displayPage == 7) {
    // Read AIN1 once
    int32_t vref_adc = adc[0].Read_SingleShot_SingleEnded_WaitForData(MUX_SE_CH1);
    // Convert to voltage
    double vref_double = (double)convertToMilliV(vref_adc)/1000;

    // Return to differential measurement mode
    adc[0].select_mux_channels(MUX_AIN0_AIN1);
    return vref_double;
  } else {
    return 0;
  }
  
}


// Converts the given ads data to mV
float convertToMilliV(int32_t i32data) {
    return (float)((i32data*VFSR*1000)/FULL_SCALE);
}

// Converts the given voltage (millivolt) to charge (mC), with given feedback capacitance CF
float convertToPicoC(int32_t i32data) {
  return (float) CF * convertToMilliV(i32data) / 1000; //Conversion from pF and mV to pC 
}

// Inverts the digital output (e.g. LED) of a pin
inline void digitalToggle(byte pin){
  digitalWrite(pin, !digitalRead(pin));
}

// Refreshs the LED status by given markers (lastBlink, espNow, uart, batteryAlert)
void refreshLEDs() {
  // LED1 blinking five times per second to show the program is working.
  if (millis() - lastBlink > 200) {
    digitalToggle(LED1);
    lastBlink = millis();
  }

  // Switch LED status if uart status changes.
  if (uartConnected) {
    if(!digitalRead(LED3)) {
      digitalWrite(LED3, HIGH);
    }    
  } else {
    if(digitalRead(LED3)) {
      digitalWrite(LED3, LOW);
    }
  }

  // Switch LED status if espNow status changes.
  if (espNowConnected) {
    if(!digitalRead(LED4)) {
      digitalWrite(LED4, HIGH);
    }    
  } else {
    if(digitalRead(LED4)) {
      digitalWrite(LED4, LOW);
    }
  }

  // Blink battery LED if marker batteryAlert is set.
  if (batteryAlert && (millis() - lastBlinkBattery > 100)) {
    digitalToggle(LED2);
    lastBlinkBattery = millis();
  } else {
    digitalWrite(LED2, LOW);
  }
}

//-------------------------------------------------------------------------------------------------------------------
// Start of the four ADCs
void setupADCs() {

  // Start SPI connection to ADCs
  Serial.println("Start SPI");
  SPI.begin(SCK, MISO, MOSI, SS);
  Serial.println("Configured SPI");

  // Setup CS pins (output and HIGH)
  for (int i = 0; i < 4; i++) {
    pinMode(CS_Pins[i], OUTPUT);
    digitalWrite(CS_Pins[i], HIGH);

    // Fill array with ADS1220-objects
    adc[i] = Protocentral_ADS1220_mod();
  }

  for (int i = 0; i < 4; i++) {
    // setup for each ADC
    setupADC(i);
    Serial.println("ADC " + String(i) + " is set up.");    
  }  
}

// Setup ADS1220
void setupADC(int nr) {
  adc[nr].begin(CS_Pins[nr],DRDY_Pins[nr]);
  // Set data rate of ADC to 1kHz
  adc[nr].set_data_rate(DR_1000SPS);
  // Set internal gain in ADC to 1
  adc[nr].set_pga_gain(PGA_GAIN_1);
  // Set Single shot mode
  adc[nr].set_conv_mode_single_shot();
  // Set reference voltage to VREF0
  adc[nr].set_VREF(VREF_REFP0);
  // Set Mux to Differenital CH0-CH1
  adc[nr].select_mux_channels(MUX_AIN0_AIN1);   // Measurement mode. Set up once, the mux channel will not be changed during runtime.
}

// Readout all four ADCs simultaneously -> Faster than waiting for each ADC after another.
void readoutADCs() {
  // Start ADC measurement
  for(int i = 0; i < 4; i++){    
    adc[i].Start_Conv();
  }
  // read ADC data
  for(int i = 0; i < 4; i++){    
    adc_data[i] = adc[i].Read_WaitForData();
  }
}

//-------------------------------------------------------------------------------------------------------------------
// Send data to display on UART2
void sendDataToDisplay() {
  // Decide which data to send by the given display page
  // Graph values are shown between 0 and 255 -> Conversion needed.
  switch(displayPage) {
    case 3:   // Channel 1
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro1)) + endChar);
      break;

    case 4:   // Channel 2
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro2)) + endChar);
      break;

    case 5:   // Channel 3
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro3)) + endChar);
      break;

    case 6:   // Channel 4
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro4)) + endChar);
      break;

    case 1:   // All Channels A
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro1)) + endChar);
      displaySerial.print("add 1,1," + String(convertToDisplay(data_struct.ferro2)) + endChar);
      displaySerial.print("add 1,2," + String(convertToDisplay(data_struct.ferro3)) + endChar);
      displaySerial.print("add 1,3," + String(convertToDisplay(data_struct.ferro4)) + endChar);
      break;

    case 2:   // All Channels B
      displaySerial.print("add 1,0," + String(convertToDisplay(data_struct.ferro1)) + endChar);
      displaySerial.print("add 5,0," + String(convertToDisplay(data_struct.ferro2)) + endChar);
      displaySerial.print("add 6,0," + String(convertToDisplay(data_struct.ferro3)) + endChar);
      displaySerial.print("add 7,0," + String(convertToDisplay(data_struct.ferro4)) + endChar);
      break;

    case 7:   // Voltage Display
      // Display values put a comma between the 10 and 100, therefore multipliing by 100 to get two after-comma digits (3.67 V -> *10 = 367 -> shown as 3.67)
      displaySerial.print("vcc.val=" + String(int(data_struct.vcc*100)) + endChar);     // Send VCC Value
      displaySerial.print("vref.val=" + String(int(data_struct.vref*100)) + endChar);   // Send VRef Value
      break;

    default:
      break;
  }
}

// Conversion to "display graph values"
// -max to max mapped onto 0 to 255
// Charge in pC as input value
// Voltage: max. +/- 1.7V -> max. +/- 612 pC with CF = 360pF
int convertToDisplay(double value) {
  // map value relative to maxCharge to the 128 possible values in positive or negative direction
  double ret = value/maxCharge * 128 + 128;
  //Serial.print("Display Value: ");
  //Serial.print(ret);
  return (int) ret;
}

// read Messages from display (for information about the shown page)
void readFromDisplay() {
  while (displaySerial.available()) {
    String s = displaySerial.readString();
    if(s.indexOf("page_ch_1") >= 0) {
      displayPage = 3;
    } else if(s.indexOf("page_ch_2") >= 0) {
      displayPage = 4;
    } else if(s.indexOf("page_ch_3") >= 0) {
      displayPage = 5;
    } else if(s.indexOf("page_ch_4") >= 0) {
      displayPage = 6;
    } else if(s.indexOf("page_voltage") >= 0) {
      displayPage = 7;
    } else if(s.indexOf("page_all_A") >= 0) {
      displayPage = 1;
    } else if(s.indexOf("page_all_B") >= 0) {
      displayPage = 2;
    } else {
      // DisplayPage has not changed.
    }
  }
}

//-------------------------------------------------------------------------------------------------------------------
// Little Lightshow for startup. (No real use :D)
void startupLEDshow() {
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(50);
  digitalWrite(LED2, HIGH);
  delay(50);
  digitalWrite(LED3, HIGH);
  delay(50);
  digitalWrite(LED4, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  delay(200);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  delay(200);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
}
