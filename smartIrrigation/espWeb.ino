#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid = "HELL0"; 
const char* password = "gogetyours";         
const char* serverUrl = "https://smartirrigationbackend.onrender.com"; 
const char* serverURL = "https://9fx3gmg3-3000.inc1.devtunnels.ms/motor";

#define API_KEY "f8d681a7dd8c83f235fe52350a19bddb"
#define YOUR_LAT "29.9476"
#define YOUR_LON "76.8227"

int C = 14000;

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

int sensorValue[4] ={0,0,0,0};
int valveData[4] = {0,0,0,0};
int valveOutput[4]={0,0,0,0};
float P=10,H=35,T=22;

//weather forecast
void getRainForecast() {
  HTTPClient http;
  
  // Construct URL for the Open-Meteo API with precipitation, temperature, and humidity
  String url = "https://api.open-meteo.com/v1/forecast?latitude=" + String(YOUR_LAT) +"&longitude=" + String(YOUR_LON) + "&hourly=precipitation,temperature_2m,relative_humidity_2m";
  
  // Send HTTP GET request
  http.begin(url);
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    String response = http.getString();
    
    // Parse JSON response
    DynamicJsonDocument doc(2048);
    DeserializationError error = deserializeJson(doc, response);
    
    if (error) {
      Serial.println("JSON Parsing Failed!");
      return;
    }
    
    // Extract hourly data
    JsonArray precipitationArray = doc["hourly"]["precipitation"];
    JsonArray temperatureArray = doc["hourly"]["temperature_2m"];
    JsonArray humidityArray = doc["hourly"]["humidity_2m"];
    JsonArray timeArray = doc["hourly"]["time"];
    
    // Print the forecast data
    Serial.println("\n--- Weather Forecast ---");

    // Loop through the next 5 hours (you can adjust this based on your needs)
   
      float precipitation = precipitationArray[0].as<float>();
      float temperature = temperatureArray[0].as<float>();
      float humidity = humidityArray[0].as<float>();
      String time = timeArray[0].as<String>();

      //**  H = humidity;       //%
      //**  T = temperature;    //`c
      //**  P = precipitation;  //mm
      
      // Display the weather data
      Serial.print("Time: "); Serial.print(time);
      Serial.print(" | Precipitation (mm): "); Serial.print(precipitation);
      Serial.print(" | Temperature (°C): "); Serial.print(temperature);
      Serial.print(" | Humidity (%): "); Serial.println(humidity);
    
    Serial.println("------------------------");
  } else {
    Serial.println("Error in HTTP request");
  }

  // Close the HTTP connection
  http.end();
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
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

        for (int i = 0; i < 4; i++) {
            JsonObject sensor = sensors.createNestedObject();
            sensor["id"] = i + 1;
            sensor["moisture"] =  sensorValue[i];
            
        }

        String payload;
        serializeJson(doc, payload);
        int httpResponseCode = http.POST(payload);

        //. Serial.println("Data Sent: " + payload);
        //. Serial.println("Response Code: " + String(httpResponseCode));
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

void motor(){
 if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverURL);
        int httpResponseCode = http.GET();

        if (httpResponseCode == 200) {
            String response = http.getString();
            response.trim();  // Remove any unwanted spaces or newlines

            Serial.println("Server Response: " + response);

            // JSON Parsing
            StaticJsonDocument<200> doc;
            DeserializationError error = deserializeJson(doc, response);

            if (!error) {
                for (int i = 0; i < doc.size(); i++) {
                    String motorStatus = doc[i].as<String>();
                    bool isMotorOn = (motorStatus == "true");

                    if(isMotorOn){
                      valveOutput[i] = 90;
                    }else {
                    valveOutput[i] = 0;
                    }
                }
            } else {
                Serial.println("Error parsing JSON!");
            }
        } else {
            Serial.println("Error fetching data: " + String(httpResponseCode));
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected!");
    }
}

void loop() {
  getRainForecast();
  sendData();
  motor();
//reading sensor value
  sensorValue[0] =  map(analogRead(sensorPin[0]), 4095, 0, 0, 100);
  sensorValue[1] = map(analogRead(sensorPin[1]), 0, 4095, 0, 100);
  sensorValue[2] =  map(analogRead(sensorPin[2]), 4095, 0, 0, 100);
  sensorValue[3] = map(analogRead(sensorPin[3]), 0, 4095, 0, 100);

  for(int i=0;i<4;i++){
      valveData[i] = (100-(sensorValue[i]+P))(100-H)(T-10);
      Serial.println(sensorValue[i]);
      if (valveData[i]>0) {
        valveData[i] =  map(valveData[i],0,70000,0,100);
      }else {
      valveData[i]=0;
      }
    }
  for(int i=0;i<4;i++){
    if(valveData[i]<30){
      valveOutput[i] = 0;
    }else if (valveData[i]>85) {
    valveOutput[i] = 90;
    }
  }
  motor1.write(valveOutput[0]);
  motor2.write(valveOutput[1]);
  motor3.write(valveOutput[2]);
  motor4.write(valveOutput[3]);

   // getCommand();
}
