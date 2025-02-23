**Soil Moisture and Irrigation Control System**

This project is designed to calculate soil moisture based on weather data (**temperature, humidity, and precipitation**) and control an **irrigation system (motor/valve)** accordingly. The system fetches weather data from the **OpenWeatherMap API**, calculates soil moisture, and controls a **relay module** connected to a motor or valve based on soil moisture levels.

---
## 📌 **Table of Contents**
- [**Project Overview**](#project-overview)
- [**Prerequisites**](#prerequisites)
- [**Installation and Setup**](#installation-and-setup)
- [**Configuration**](#configuration)
- [**Usage**](#usage)
- [**Running the Program**](#running-the-program)
- [**Future Improvements**](#future-improvements)

---
## 🚀 **Project Overview**
This project utilizes an **ESP8266 (NodeMCU)** to:
- Fetch **real-time weather data** (temperature, humidity, precipitation) from the **OpenWeatherMap API**.
- Calculate **soil moisture levels** using a simple formula.
- Control a **relay module** to turn the irrigation system (**motor/valve**) **on** or **off** based on soil moisture levels.

### **🌟 Features:**
- ✅ Fetch weather data using the **OpenWeatherMap API**.  
- ✅ Calculate **soil moisture** based on environmental conditions.  
- ✅ Control a **relay module** to manage the irrigation system efficiently.  

---
## 🛠 **Prerequisites**

### **🔧 Hardware:**
- **NodeMCU (ESP32)**
- **Relay module or Servo Motor** (for controlling motors/valves)
- **Jumper wires**
- **Motor or irrigation valve**
- **Power supply** for the motor

### **💻 Software:**
- **Arduino IDE** (for programming NodeMCU in C/embeded C)
- **OpenWeatherMap API key** (for fetching weather data)

### **📦 Required Libraries:**
- `ESP32WiFi.h` (for Wi-Fi connectivity)
- `ESP32HTTPClient.h` (for making HTTP requests)
- `ArduinoJson.h` (for parsing JSON data from the API)

---
## ⚙️ **Usage**

### **1️⃣ Weather Data Retrieval:**
- The **NodeMCU** fetches weather data (**temperature, humidity, precipitation**) from **OpenWeatherMap**.
- The system calculates **soil moisture** using a formula based on the fetched weather data
- It make a Decision based on the sensor data and Weather Forecast.

### **2️⃣ Irrigation Control:**
- If **soil moisture is too low (<30%)**, the relay is **activated**, turning on the motor/valve.
- If **soil moisture is too high (>80%)**, the relay is **deactivated**, turning off the motor/valve.

---
## 🔮 **Future Improvements**
- ✅ **Integrate Soil Moisture Sensors:** Use actual **soil moisture sensors** for more accurate readings.  
- ✅ **Multiple Zone Support:** Extend the system to control **irrigation for multiple zones or fields**.  
- ✅ **Weather Prediction:** Use **weather forecasts** to optimize irrigation scheduling.  
- ✅ **Web Interface:** Build a **web interface** to monitor and control the system remotely.  
- ✅ **Mobile App:** Develop a **mobile app** for manual control and notifications.  

**PPT** : [https://9fx3gmg3-3000.inc1.devtunnels.ms/data](https://drive.google.com/file/d/1zIstZgxqgqrOJWSOMQLmJsqx-EQAWDii/view?usp=sharing)
