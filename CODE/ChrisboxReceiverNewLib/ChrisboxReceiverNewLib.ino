#include <esp_now.h>
#include <WiFi.h>

// Struktur für die Sensordaten
typedef struct {
  unsigned long long time_micros;
  float ferro1;
  float ferro2;
  float ferro3;
  float ferro4;
} four_ch_fsr_struct;

four_ch_fsr_struct myData;

// Neue ESP-NOW Callback-Signatur
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  // String direkt als Char-Array (schneller als String-Objekt)
  char out[128];  
  snprintf(out, sizeof(out), "%llu,%.6f,%.6f,%.6f,%.6f", 
           myData.time_micros, myData.ferro1, myData.ferro2, myData.ferro3, myData.ferro4);
  Serial.println(out);
}

void setup() {
  Serial.begin(921600);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Neue API erfordert die neue Signatur
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  yield(); // Nichts hier, da ESP-NOW über Interrupts läuft
}
