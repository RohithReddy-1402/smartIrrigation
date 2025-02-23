#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid = "HELL0"; 
const char* password = "gogetyours";         
const char* serverUrl = "https://smartirrigationbackend.onrender.com"; 

#define LED_PIN 2  
#define motorPin1 19
#define motorPin2 21
#define motorPin3 22
#define motorPin4 23

int sensorPin[4] ={ 32,33,34,35};

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

int pos1 =0;
int pos2 =0;
int pos3 =0;
int pos4 =0;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");

  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(sensorPin[0], INPUT);
  pinMode(sensorPin[1], INPUT);
  pinMode(sensorPin[2], INPUT);
  pinMode(sensorPin[3], INPUT);
  pinMode(LED_PIN, OUTPUT);

  motor1.attach(motorPin1);
  motor2.attach(motorPin2);
  motor3.attach(motorPin3);
  motor4.attach(motorPin4);
}

void sendData() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(String(serverUrl) + "/send-data");
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<500> doc;
        JsonArray sensors = doc.createNestedArray("sensors");

        for (int i = 0; i < 10; i++) {
            JsonObject sensor = sensors.createNestedObject();
            sensor["id"] = i + 1;
            sensor["temperature"] =  map(analogRead(sensorPin[0]), 4095, 0, 0, 100);
            sensor["humidity"] = map(analogRead(sensorPin[1]), 4095, 0, 0, 100);
        }

        String payload;
        serializeJson(doc, payload);
        int httpResponseCode = http.POST(payload);

        //**. Serial.println("Data Sent: " + payload);
        //**. Serial.println("Response Code: " + String(httpResponseCode));
        http.end();
    }
}

void getCommand() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(String(serverUrl) + "/get-command");
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String command = http.getString();
            //** Serial.println("Received Command: " + command);
        }

        http.end();
    }
}

void loop() {

  int sensorValue1 =  map(analogRead(sensorPin[0]), 4095, 0, 0, 100);
  int sensorValue2 = map(analogRead(sensorPin[1]), 0, 4095, 0, 100);
  int sensorValue3 =  map(analogRead(sensorPin[2]), 4095, 0, 0, 100);
  int sensorValue4 = map(analogRead(sensorPin[3]), 0, 4095, 0, 100);

  motor1.write(map(sensorValue1,0,100,0,90));
  motor2.write(map(sensorValue2,0,100,0,90));
  motor3.write(map(sensorValue3,0,100,0,90));
  motor4.write(map(sensorValue4,0,100,0,90));


    sendData();
    getCommand();
    delay(20); 
}
