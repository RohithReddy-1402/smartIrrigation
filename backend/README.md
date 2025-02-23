# Soil Moisture and Irrigation Control System Backend



## Table of Contents
1. Project Overview
2. Prerequisites
3. Future Improvements
4. License

---

## Project Overview
This backend application is responsible for fetching weather data, calculating soil moisture levels, and controlling the irrigation system based on predefined thresholds. The system:
- Fetches real-time weather data (temperature, humidity, precipitation) from the OpenWeatherMap API.
- Calculates soil moisture using an estimation formula.
- Controls a relay module via NodeMCU (ESP8266) to turn the irrigation system (motor/valve) on or off.
- Exposes APIs to interact with the system.

### Features:
- Fetches real-time weather data using OpenWeatherMap API.
- Computes soil moisture levels based on weather conditions.
- Controls a relay module for automated irrigation.
- Provides API endpoints for monitoring and manual control.
---

## Prerequisites

### Hardware:
- NodeMCU (ESP8266)
- Relay module (for controlling motors/valves)
- Jumper wires
- Motor or irrigation valve
- Power supply for the motor

### Software:
- Node.js (Backend Server)
- Express.js (API Framework)
- Arduino IDE (for programming NodeMCU in C/C++)
- OpenWeatherMap API Key (for fetching weather data)

### Required Libraries:
- `express` (for API handling)
- `axios` (for HTTP requests to OpenWeatherMap API)
- `dotenv` (for managing environment variables)
- `nodemon` (for development server auto-restart)

---

## Installation and Setup

### 1. Clone the Repository
```sh
git clone https://github.com/RohithReddy-1402/smartIrrigation
cd soil-moisture-irrigation/backend
```


---

## Future Improvements
1. **Integrate Soil Moisture Sensors**: Use actual sensors for accurate readings.
2. **Multiple Zone Support**: Extend the system to handle multiple irrigation zones.
3. **Weather Prediction**: Implement forecast-based irrigation control.
4. **Web Interface**: Create a dashboard for real-time monitoring.
5. **Mobile App**: Develop an app for notifications and manual control.

---

## License
This project is licensed under the MIT License.

