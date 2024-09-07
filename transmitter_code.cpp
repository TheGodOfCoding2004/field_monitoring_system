// Code for the ESP8266 Transmitter written in PlatformIO IDE
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHTesp.h>
#include "ESPNowW.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// put function declarations here:
uint8_t mac_address[] = {0xD4 , 0x8A , 0xFC , 0xCF , 0xED , 0x14};
DHTesp dht;
LiquidCrystal_I2C lcd(0x27 , 16 , 2);
int soilPin = A0;

typedef struct struct_msg {
  uint8_t id;
  float humidity;
  float temp_c;
  float temp_f;
  float moisture_level;
} struct_msg;
struct_msg myData;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(2 , 0);
  lcd.init();
  lcd.backlight();
  Serial.println();
  WiFi.mode(WIFI_STA);
  dht.setup(D5 , DHTesp::DHT22);
  WiFi.disconnect();
  ESPNow.init();
  ESPNow.add_peer(mac_address , ESP_NOW_ROLE_COMBO);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);
  myData.id = 2;
  myData.humidity = dht.getHumidity();
  myData.temp_c = dht.getTemperature();
  myData.temp_f = (1.8 * myData.temp_c)+32;
  myData.moisture_level = analogRead(soilPin);

  Serial.println();
  Serial.print("Humidity in % : "); Serial.println(myData.humidity);
  Serial.print("Temperature in C : "); Serial.println(myData.temp_c);
  Serial.print("Temperature in F : "); Serial.println(myData.temp_f);
  Serial.print("Moisture level : ") ; Serial.println(myData.moisture_level);
  if(myData.moisture_level < 500)
  {
    Serial.println("Soil is too wet");
    Serial.println();
    lcd.print("Soil is wet");
    delay(4000);
    lcd.clear();
  }
  else if (myData.moisture_level >= 500 && myData.moisture_level < 750)
  {
    Serial.println("Soil has the correct amount of moisture present in it");
    Serial.println();
    lcd.setCursor(0 , 0);
    lcd.print("Soil moisture");
    lcd.setCursor(0 , 1);
    lcd.print("level is ideal");
    delay(4000);
    lcd.clear();
  }
  else
  {
    Serial.println("Soil is too dry");
    Serial.println();
    lcd.print("Soil is too dry");
    delay(4000);
    lcd.clear();

  }

  ESPNow.send_message(mac_address , (uint8_t*)&myData , sizeof(myData));
  delay(1000);
}

// put function definitions here:
