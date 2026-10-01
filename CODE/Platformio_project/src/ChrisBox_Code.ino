/*
  ChrisBox_Code.ino - Code for the ChrisBox - a multi-channel ferroelectret measurement device
  @authors Dominik Werner and Luis Gross
  @date   2026-02-04
  @version 1.1
  at MUST-TU Darmstadt, Germany
*/
//-------------------------------------------------------------------------------------------------------------------
// Include Libraries
#include <esp_now.h>                  // for ESP NOW communication
#include <WiFi.h>                     // for ESP NOW communication
#include <ADS1220_WE.h>                      // for ADS1220 communication

//-------------------------------------------------------------------------------------------------------------------
// Define Pins

// ADS1220 (4x)
int CS_Pins[] = {12, 13, 14, 15};
int DRDY_Pins[] = {8, 9, 10, 11};
#define SCK     7   // SPI Clock
#define MISO    6   // SPI MISO
#define MOSI    5   // SPI MOSI

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

bool display_charge = true;    // Decide if the charge value shall be displayed (true) or the voltage value (false) on the Nextion display
bool esp_now_connection = false;  // Decide if ESPNOW connection shall be used or not (required for ESP to ESP wireless connection)
bool uart2_connection = true;     // Decide if UART2 shall be used (required for Nextion display)
bool voltage_generation = true;   // Decide if the 5V voltage generation should work (required for Nextion display)

#define UART2BAUD 115200          // Define the baud rate for UART2 communication

#define CF 360                    // Feedback capacitance [pF] (Q = C * U, Charge = CF * Voltage)

#define thresVCC 3.2              // Threshold for VCC, where the battery indicator should start blinking (ESP 32 recommended minimum voltage is 3.0V)
  
#define VREFADC  3.28         // ADS1220, Reference voltage
#define NUM_ADCS 4
//-------------------------------------------------------------------------------------------------------------------
// Variables

int lastBlink;                // time of last blink for LED1 blinking
int lastBlinkBattery;         // time of last blink for Battery Warning LED2
bool uartConnected;           // marker wheter UART2 is connected or not -> shown by blue LED3
bool espNowConnected;         // marker whether ESP NOW is connected -> shown by blue LED4
bool batteryAlert;            // marker if the voltage is too low
double vRef_mV;             // measured VRef in millivolt
double maxVoltagePlus;        // maximum voltage for positive charge calculation
double maxChargePlus;         // maximum charge for positive charge calculation
double maxVoltageMinus;       // maximum voltage for negative charge calculation
double maxChargeMinus;        // maximum charge for negative charge calculation


ADS1220_WE adc[NUM_ADCS] = {
  ADS1220_WE(&SPI, CS_Pins[0], DRDY_Pins[0], MOSI, MISO, SCK, true, false),
  ADS1220_WE(&SPI, CS_Pins[1], DRDY_Pins[1], MOSI, MISO, SCK, true, false),
  ADS1220_WE(&SPI, CS_Pins[2], DRDY_Pins[2], MOSI, MISO, SCK, true, false),
  ADS1220_WE(&SPI, CS_Pins[3], DRDY_Pins[3], MOSI, MISO, SCK, true, false)
};  // Four ADCs...
float adc_data[4];          // ... and a place to store their readings

int displayPage = 0;              // display page as int. 1 is the first page, 7 the last one.

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
    
    // esp_now_register_send_cb(OnDataSent); //Produces Errors
    
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
    displaySerial.print("page Splash" + endChar);   // Send page command to start on the first page.
    displayPage = 1;
  }  

  // -------------------------------------------------------

  pinMode(LED1, OUTPUT);        // LEDs as digital output pins (Program working)
  pinMode(LED2, OUTPUT);        // ...  (Battery Status)
  pinMode(LED3, OUTPUT);        // ...  (UART2 connected)
  pinMode(LED4, OUTPUT);        // ...  (ESP NOW connected)

  startupLEDshow();             // Little lightshow at the start, because it is cool.
  
  setupADCs();
  
  // Initialisieren von Variablen
  vRef_mV = getVRef()*1000;                    // VRef in millivolt
  maxVoltagePlus = 3.3 - (vRef_mV / 1000.0);   // max voltage for display plus 
  maxChargePlus = maxVoltagePlus * CF;         // max voltage plus * feedback capacitance.
  maxVoltageMinus = 0 - (vRef_mV / 1000.0);    // max voltage for display minus
  maxChargeMinus = maxVoltageMinus * CF;       // max voltage minus * feedback capacitance.

  lastBlink = millis();
  lastBlinkBattery = millis();

  Serial.println("Setup finished.");
}

//-------------------------------------------------------------------------------------------------------------------

void loop() {

  refreshLEDs();        // update LEDs for blinking and status etc.
  readoutADCs();        // read ADC data from all four ADCs

  // // Debug
  // adc_data[0] = 3300;
  // adc_data[1] = 0;
  // adc_data[2] = 2000;
  // adc_data[3] = 1000;


  if(displayPage == 7){
    data_struct.vcc = getVCC();                           // read and store VCC (internal ADC)
    data_struct.vref = getVRef();                         // read and store VRef (internal ADC)
  }  
  if(display_charge) {
    // Convert ADC voltage readings to charge values
    data_struct.ferro1 = convertToPicoC(adc_data[0]);    // compute charge of Ferro 1 (ADS1220)
    data_struct.ferro2 = convertToPicoC(adc_data[1]);    // compute charge of Ferro 2(ADS1220)
    data_struct.ferro3 = convertToPicoC(adc_data[2]);    // compute charge of Ferro 3 (ADS1220)
    data_struct.ferro4 = convertToPicoC(adc_data[3]);    // compute charge of Ferro 4 (ADS1220)
  } else {
    // Store ADC voltage readings directly
    data_struct.ferro1 = adc_data[0];    // voltage of Ferro 1 (ADS1220)
    data_struct.ferro2 = adc_data[1];    // voltage of Ferro 2(ADS1220)
    data_struct.ferro3 = adc_data[2];    // voltage of Ferro 3 (ADS1220)
    data_struct.ferro4 = adc_data[3];    // voltage of Ferro 4 (ADS1220)
  }


  // --------------------------------------------------------------------
  // Serial print the measured values
  // -> Serial print should work with BetterSerialPlotter on a PC
  // VCC und VRef
  Serial.print(data_struct.vcc, 6);       // The number (6) indicates how many decimal digits will be shown.
  Serial.print(" ");
  Serial.print(data_struct.vref, 6);
  Serial.print(" ");

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

// Measures the VRef voltage from the read of VRef at ADC1
double getVRef() {
  // Do all this only if the VRef is shown on the display, otherwise this just reduces performance.
    adc[0].setCompareChannels(ADS1220_MUX_1_AVSS);
    // adc[0].start(); // ADC Ferro

    // while(digitalRead(DRDY_Pins[0])){}

    double vref_double = adc[0].getVoltage_mV() / 1000;
    adc[0].setCompareChannels(ADS1220_MUX_0_AVSS);

    return vref_double;
  }


// Converts the given voltage (millivolt) to charge (mC), with given feedback capacitance CF
// Voltage Jumps: max. +/- 1.5V -> max. +/- 540 pC with CF = 360pF
float convertToPicoC(double voltage_mV) {
  float charge_pC = CF * ((voltage_mV - vRef_mV) / 1000); //Conversion from pF and mV to pC 
  if(charge_pC > maxChargePlus) {
    charge_pC = maxChargePlus;
  } else if(charge_pC < maxChargeMinus) {
    charge_pC = maxChargeMinus;
  }
  return charge_pC;
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
void setupADC(int nr) {
  if(!adc[nr].init()){
    Serial.println("ADC is not connected!");
    while(1);
  }

  adc[nr].bypassPGA(false);
  adc[nr].setDataRate(ADS1220_DR_LVL_6);
  adc[nr].setConversionMode(ADS1220_SINGLE_SHOT);
  adc[nr].setVRefSource(ADS1220_VREF_REFP0_REFN0);
  adc[nr].setRefp0Refn0AsVrefAndCalibrate(); // Sets
  // adc[nr].setVRefValue_V(VREFADC); // Sets internal Vref for ADC[i] to const Value
  float vref = adc[nr].getVRef_V();
  Serial.print("VREF Set to: ");// Debug: Gives the measured internal Vref for ADC[i]
  Serial.println(vref,2);
  adc[nr].setNonBlockingMode(false);
  adc[nr].setCompareChannels(ADS1220_MUX_0_AVSS); 
}

void setupADCs(){
  for (int i = 0; i < 4; i++) {
    // setup for each ADC
    setupADC(i);
    Serial.println("ADC " + String(i) + " is set up.");    
  }  
}

//-------------------------------------------------------------------------------------------------------------------
void readoutADCs() {
  // for(int i = 0; i < NUM_ADCS; i++){    
  //   adc[i].start(); // ADC Ferro
  // }
  
  // for(int i = 0; i < NUM_ADCS; i++){    
  //   while(digitalRead(DRDY_Pins[i])){
  //     // do nothing
  //   }
    // adc_data[i] = adc[i].getRawData();
    // adc_data[i] = adc[i].getVoltage_mV();
  // }
  for(int i=0; i < NUM_ADCS; i++){
    adc_data[i] = adc[i].getVoltage_mV();
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
int convertToDisplay(double value) {
  float ret = 128;
  if(display_charge) {
    // map value relative to maxCharge to the 128 possible values in positive or negative direction
    if(value > 0) {
      ret = value/maxChargePlus * 128 + 128;
    } else if(value < 0) {
      ret = 128 - (value/maxChargeMinus * 128);
    }
  }
  else {
    ret = value/(vRef_mV/1000.0) * 128 + 128;
  }
  if(ret > 255) ret = 255;
  if(ret < 0) ret = 0;
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