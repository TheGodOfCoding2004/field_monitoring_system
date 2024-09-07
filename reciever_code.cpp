//Reciever code for ESP32 written in PlatformIO IDE
#include <Arduino.h>
#include <WiFi.h>
#include "ESPNowW.h"

#define SIM800L_RX_PIN 0
#define SIM800L_TX_PIN 4

unsigned long previousMillis = 0;
const long interval = 1000;

// Function declarations
typedef struct struct_msg {
  int id;
  float humidity;
  float temp_c;
  float temp_f;
  float moisture_level;
} struct_msg;

void sendSensorData(struct_msg data);
void test_module();
void updateSerial();

struct_msg plot1 = {1, 0.0, 0.0, 0.0, 0.0};
struct_msg plot2 = {2, 0.0, 0.0, 0.0, 0.0};
struct_msg plot3 = {3, 0.0, 0.0, 0.0, 0.0};

struct_msg plots[3] = {plot1, plot2, plot3};

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  struct_msg receivedData = *((struct_msg *)data);
  
  if(receivedData.id >= 1 && receivedData.id <= 3) {
    plots[receivedData.id - 1].humidity = receivedData.humidity;
    plots[receivedData.id - 1].temp_c = receivedData.temp_c;
    plots[receivedData.id - 1].temp_f = receivedData.temp_f;
    plots[receivedData.id - 1].moisture_level = receivedData.moisture_level;
  }  
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, SIM800L_RX_PIN, SIM800L_TX_PIN);
  delay(1000);
  
  WiFi.mode(WIFI_MODE_STA);
  WiFi.disconnect();
  ESPNow.init();
  ESPNow.reg_recv_cb(OnDataRecv);

  test_module();
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();

  for (int i = 0; i < 3; i++) {
    int plotNumber = i + 1;
    Serial.println();
    Serial.printf("PLOT %d DATA:\n", plotNumber);
    Serial.print("Humidity : "); Serial.println(plots[i].humidity);
    Serial.print("Temperature (C) : "); Serial.println(plots[i].temp_c);
    Serial.print("Temperature (F) : "); Serial.println(plots[i].temp_f);
    Serial.print("Soil Moisture : "); Serial.println(plots[i].moisture_level);
    
    if (plots[i].moisture_level < 500) {
      Serial.println("The soil is too wet");
    } else if (plots[i].moisture_level > 500 && plots[i].moisture_level <= 750) {
      Serial.println("The soil has ideal amount of moisture");
    } else {
      Serial.println("The soil is too dry");
    }
    sendSensorData(plots[i]);
  }
  Serial.println("_________________________________________________________________");
  delay(1000);
}

void test_module() {
  Serial2.println("AT");
  delay(1000);
  updateSerial();
  
  Serial2.println("AT+CSQ");
  delay(1000);
  updateSerial();
  
  Serial2.println("AT+CCID");
  delay(1000);
  updateSerial();
  
  Serial2.println("AT+CREG?");
  delay(1000);
  updateSerial();
  
  Serial2.println("AT+CBC");
  delay(1000);
  updateSerial();
}

void sendSensorData(struct_msg data) {
  String message = "PLOT " + String(data.id) + " Data:\n"
                    + "Humidity: " + String(data.humidity) + "\n"
                    + "Temperature (C): " + String(data.temp_c) + "\n"
                    + "Temperature (F): " + String(data.temp_f) + "\n"
                    + "Soil moisture: " + String(data.moisture_level);

  const char* msgToSend = message.c_str();

  Serial2.println("AT+CMGF=1");
  delay(500);
  updateSerial();
  Serial2.print("AT+CMGS=\"+917975337961\"\r"); // Replace with your recipient's number
  delay(500);
  updateSerial();
  Serial2.print(msgToSend);
  delay(500);
  updateSerial();
  Serial2.write(26); // Ctrl+Z to terminate the message
  delay(500);
  updateSerial();
}

void updateSerial() {
  delay(500);
  while (Serial2.available()) {
    Serial.write(Serial2.read());
  }
  while (Serial.available()) {
    Serial2.write(Serial.read());
  }
}
