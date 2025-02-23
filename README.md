Soil Moisture and Irrigation Control System 
This project is designed to calculate soil moisture based on weather data (temperature, humidity, and precipitation) and control an irrigation system (motor/valve) accordingly. The system fetches weather data from the OpenWeatherMap API, calculates soil moisture, and controls a relay module connected to a motor or valve based on the soil moisture levels.


Table of Contents
1. Project Overview
2. Prerequisites
3. Installation and Setup
4. Configuration
5. Usage
6. Running the Program
7.Future Improvements
8. License


Project Overview
This project uses NodeMCU (ESP8266) to:
    Fetch real-time weather data (temperature, humidity, precipitation) from the OpenWeatherMap API.
    Calculate soil moisture levels using a simple formula.
    Control a relay module to turn the irrigation system (motor/valve) on or off based on soil moisture.

Features:
    Fetch weather data using the OpenWeatherMap API.
    Calculate soil moisture based on environmental conditions.
    Control a relay module to manage the irrigation system.


Prerequisites
Hardware:
    NodeMCU (ESP8266)
    Relay module (for controlling motors/valves)
    Jumper wires
    Motor or irrigation valve
    Power supply for the motor

Software:
    Arduino IDE (for programming NodeMCU in C/C++)
    OpenWeatherMap API key (for fetching weather data)

Libraries:
    ESP8266WiFi.h (for Wi-Fi connectivity)
    ESP8266HTTPClient.h (for making HTTP requests)
    ArduinoJson.h (for parsing JSON data from the API)

Usage
1.Weather Data Retrieval:
    The NodeMCU fetches weather data (temperature, humidity, precipitation) from OpenWeatherMap.
    Soil Moisture Calculation:
    The system calculates soil moisture using a simple formula based on the fetched weather data.

2.Irrigation Control:
    If soil moisture is too low (<30%), the relay is activated to turn on the motor/valve.
    If soil moisture is too high (>60%), the relay is deactivated to turn off the motor/valve.



Future Improvements
1.Integrate Soil Moisture Sensors:
    Use actual soil moisture sensors for more accurate readings.

2.Multiple Zone Support:
    Extend the system to control irrigation for multiple zones or fields.
    
3.Weather Prediction:
    Use weather forecasts to optimize irrigation scheduling.

4.Web Interface:
    Build a web interface to monitor and control the system remotely.

5.Mobile App:
    Develop a mobile app for manual control and notifications.
