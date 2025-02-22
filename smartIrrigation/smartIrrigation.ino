#define BLYNK_TEMPLATE_ID "TMPL3KFT4TlbP"
#define BLYNK_TEMPLATE_NAME "SmartIrrigation"
#define BLYNK_AUTH_TOKEN "9zvCsGMnJzrSsMSN81R3JGSKNCQMZlMc"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//weather
#define API_KEY "f8d681a7dd8c83f235fe52350a19bddb"
#define YOUR_LAT "29.9476"
#define YOUR_LON "76.8227"

float C = 1500;

#define LED_PIN 2  
int waterSupply = 0;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "HELL0"; 
char pass[] = "gogetyours";

float H,T,P;
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

      H = humidity;
      T = temperature;
      P = precipitation;
      
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

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  WiFi.begin(ssid, pass);
    
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected to WiFi!");

  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
}

void loop() {



  Blynk.run();
  int sensorValue1 =  map(analogRead(33), 4095, 0, 0, 100);
  int sensorValue2 = map(analogRead(32), 0, 4095, 0, 100);
  Blynk.virtualWrite(V1, sensorValue1);
  Blynk.virtualWrite(V2, sensorValue2);
  int MS = (sensorValue1+sensorValue2)/2;
 

  float waterDecision=(100-(MS+P))*(100-H)*(T-20);

  if(waterDecision>C){
    Blynk.virtualWrite(V0,1);
    waterSupply = 1;
    digitalWrite(LED_PIN, HIGH);
  }else {
    Blynk.virtualWrite(V0,0);
    waterSupply = 0;
    digitalWrite(LED_PIN, LOW);
  }


  Blynk.virtualWrite(V3, SM);

  getRainForecast();

}

BLYNK_WRITE(V0)
{
  
  waterSupply = param.asInt();
  

  if (waterSupply == 1) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("value =");
    Serial.println(waterSupply);
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("value = ");
    Serial.println(waterSupply);
  }
}


