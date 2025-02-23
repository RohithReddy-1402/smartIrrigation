#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Wokwi-GUEST"; 
const char* password = "";         
const char* serverUrl = "https://9fx3gmg3-3000.inc1.devtunnels.ms"; 

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");
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
            sensor["temperature"] = random(20, 40); 
            sensor["humidity"] = random(30, 80);  
        }

        String payload;
        serializeJson(doc, payload);
        int httpResponseCode = http.POST(payload);

        Serial.println("Data Sent: " + payload);
        Serial.println("Response Code: " + String(httpResponseCode));
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
            Serial.println("Received Command: " + command);
        }

        http.end();
    }
}

void loop() {
    sendData();
    getCommand();
    delay(500); // Send data every 500ms
}
