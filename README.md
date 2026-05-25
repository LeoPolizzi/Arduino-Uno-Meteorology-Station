# Arduino-Uno-Meteorology-Station

A simple yet functional meteorology station built on Arduino Uno that monitors environmental temperature and humidity in real-time. The project simulates a complete weather monitoring system with both digital and analog feedback.

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Wiring Connections](#wiring-connections)
- [Pin Configuration](#pin-configuration)
- [Libraries Used](#libraries-used)
- [How It Works](#how-it-works)
- [Temperature Thresholds](#temperature-thresholds)
- [Installation & Setup](#installation--setup)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Serial Output](#serial-output)

---

## Project Overview

This project implements a meteorology station using an Arduino Uno microcontroller. It continuously reads temperature and humidity data from a DHT22 sensor and displays the information on a 16x2 LCD screen. Additionally, status LEDs provide visual feedback about temperature conditions, and data is logged to the Serial Monitor.

**Platform:** Wokwi (Arduino Simulator)  
**Microcontroller:** Arduino Uno  
**Primary Purpose:** Environmental monitoring and weather data collection

---

## Features

- **Real-Time Monitoring:** Reads temperature and humidity every 2 seconds
- **LCD Display:** 16x2 I2C LCD shows live temperature (°C) and humidity (%)
- **Temperature Alerts:** LED indicators signal temperature conditions:
  - 🔴 Red LED: Temperature is HOT (≥28°C)
  - 🟢 Green LED: Temperature is NORMAL (18°C - 27°C)
  - ⚫ Both OFF: Temperature is COLD (≤18°C)
- **Serial Logging:** Console output for data logging and debugging
- **Power Efficient:** Updates at controlled intervals (2-second cycles)

---

## Hardware Components

| Component | Model | Purpose |
|-----------|-------|---------|
| Microcontroller | Arduino Uno | Main processor |
| Temperature/Humidity Sensor | DHT22 | Environmental data collection |
| LCD Display | LCD1602 with I2C Module | Visual output interface |
| Red LED | Standard LED | HOT temperature indicator |
| Green LED | Standard LED | NORMAL temperature indicator |
| Current Limiting Resistors | 2x 220Ω | LED protection |
| Power Supply | USB (5V via Arduino) | System power |

---

## Wiring Connections

### Power Connections
```
Arduino 5V  → DHT22 VCC
Arduino 5V  → LCD1602 VCC
Arduino GND → DHT22 GND
Arduino GND → LCD1602 GND
Arduino GND → Red LED Cathode (C)
Arduino GND → Green LED Cathode (C)
```

### I2C Bus (for LCD)
```
Arduino A4 (SDA) → LCD1602 SDA
Arduino A5 (SCL) → LCD1602 SCL
```

### Digital Sensors
```
Arduino D2 → DHT22 Data Pin (SDA)
```

### LED Indicators
```
Arduino D8  → [220Ω Resistor] → Red LED Anode (A)
Arduino D9  → [220Ω Resistor] → Green LED Anode (A)
```

**Note:** The DHT22 communicates via a single digital line (D2), while the LCD communicates via the I2C protocol on the Arduino's analog pins (A4 = SDA, A5 = SCL).

---

## Pin Configuration

| Arduino Pin | Device/Component | Connection Type | Purpose |
|------------|------------------|-----------------|---------|
| 5V | DHT22, LCD1602 | Power | +5V supply |
| GND | All components | Ground | Common ground |
| D2 | DHT22 | Digital I/O | Data signal |
| D8 | Red LED | Digital Output | Red LED control |
| D9 | Green LED | Digital Output | Green LED control |
| A4 (SDA) | LCD1602 | I2C Data | I2C communication |
| A5 (SCL) | LCD1602 | I2C Clock | I2C communication |

---

## Libraries Used

### 1. **Wire.h** (Built-in)
- Enables I2C (TWI) communication protocol
- Required for LCD1602 I2C module communication

### 2. **LiquidCrystal_I2C** (External)
- Simplifies control of 16x2 LCD displays using I2C
- Handles LCD initialization, cursor positioning, and text display
- LCD Address: `0x27` (16 columns, 2 rows)

### 3. **DHT.h** (External)
- Library for DHT temperature and humidity sensors
- Abstracts sensor communication and data reading
- Supports DHT11, DHT22, and DHT21 sensors

### 4. **Adafruit Unified Sensor** (External)
- Dependency for DHT library
- Provides unified sensor interface

---

## How It Works

### Initialization (setup)
1. **Serial Communication:** Initializes serial at 9600 baud for debugging
2. **LED Setup:** Configures D8 and D9 as digital output pins
3. **LCD Init:** Initializes LCD display, turns on backlight
4. **Boot Message:** Displays "Meteo Station" and "booting..." on LCD
5. **DHT Init:** Initializes the DHT22 sensor
6. **Delay:** Waits 1.5 seconds for sensor stabilization
7. **Clear Display:** Prepares for main operation

### Main Loop (runs continuously)
1. **Timing Check:** Only processes if 2000ms (2 seconds) have elapsed
2. **Read Sensors:** Gets temperature and humidity from DHT22
3. **Error Handling:** Sets values to 0 if sensor read fails
4. **Temperature Logic:** Evaluates temperature thresholds
5. **LED Control:** Updates red/green LEDs based on temperature
6. **Serial Output:** Logs data to Serial Monitor
7. **LCD Update:** Refreshes display with current readings
8. **Loop Back:** Waits for next 2-second interval

```cpp
Temperature Check → LED Update → Serial Log → LCD Display → Repeat
```

### Update Interval
- **Polling Period:** 2000 milliseconds (2 seconds)
- **Prevents Sensor Flooding:** Avoids excessive I2C and DHT communication
- **Readable Display:** Updates frequently enough for real-time monitoring

---

## Temperature Thresholds

| Temperature Range | LED State | Interpretation |
|------------------|-----------|-----------------|
| **≥ 28°C** | 🔴 Red ON | HOT condition |
| **18°C - 27°C** | 🟢 Green ON | NORMAL/COMFORTABLE |
| **≤ 18°C** | ⚫ Both OFF | COLD condition |

These thresholds are defined as constants:
```cpp
#define HOT  28.0   // Threshold for hot alert
#define COLD 18.0   // Threshold for cold alert
```

You can easily modify these values in the code to suit your requirements.

---

## Installation & Setup

### For Wokwi Simulation

1. **Access Wokwi:** Visit [wokwi.com](https://wokwi.com) or use the Wokwi extension in VS Code
2. **Open Project:** Load the project files (sketch.ino, diagram.json, library.txt)
3. **Upload:** Click "Play" or "Run" to start the simulation
4. **Monitor:** View serial output in the Serial Monitor and LCD display

### For Physical Arduino (if adapting)

1. **Install Arduino IDE:** Download from [arduino.cc](https://arduino.cc)
2. **Install Libraries:**
   - Search for "DHT sensor library" in Library Manager
   - Search for "LiquidCrystal I2C" in Library Manager
   - Install "Adafruit Unified Sensor"
3. **Connect Hardware:** Wire components according to pin configuration
4. **Upload Code:** Select Arduino Uno board and appropriate COM port
5. **Open Serial Monitor:** View output at 9600 baud

---

## File Structure

```
Arduino-Uno-Meteorology-Station/
├── sketch.ino           # Main Arduino sketch (code)
├── diagram.json         # Wokwi circuit diagram
├── library.txt          # Wokwi library dependencies
└── README.md            # This documentation file
```

### File Descriptions

- **sketch.ino:** Contains all Arduino code including setup() and loop() functions, sensor reading logic, LED control, and display management
- **diagram.json:** Wokwi circuit definition file; defines component placement, pin connections, and simulation parameters
- **library.txt:** List of required libraries for Wokwi simulator
- **README.md:** Comprehensive project documentation (this file)

---

## Usage

### Simulation Workflow

1. **Start Simulation:** Run the project in Wokwi
2. **Observe LCD:** Watch real-time temperature and humidity on the 16x2 display
3. **Check LEDs:** Verify LED color changes as simulated temperature varies
4. **Monitor Serial:** Open the Serial Monitor to see timestamped data logs
5. **Adjust Sensors:** In Wokwi, you can modify DHT22 simulated values to test different conditions

### Manual Testing

**To test cold condition:** Reduce DHT22 simulated temperature to ≤18°C (both LEDs off)

**To test normal condition:** Set temperature between 18°C-27°C (green LED on)

**To test hot condition:** Increase temperature to ≥28°C (red LED on)

---

## Serial Output

The sketch sends formatted data to the Serial Monitor every 2 seconds:

```
T=24.5C  H=65.3%
T=24.3C  H=65.1%
T=25.0C  H=64.8%
```

**Format:**
- `T=` Temperature value in Celsius with 1 decimal place
- `H=` Humidity value in percentage with 1 decimal place
- Updates occur every 2 seconds

**Serial Configuration:**
- **Baud Rate:** 9600
- **Data Bits:** 8
- **Stop Bits:** 1
- **Parity:** None

To view serial output:
- In Wokwi: Click the Serial Monitor button
- In Arduino IDE: Tools → Serial Monitor (Ctrl+Shift+M)

---

## Key Code Features

### Sensor Reading with Error Handling
```cpp
float temp     = dht.readTemperature();
float humidity = dht.readHumidity();

if (isnan(temp))     temp = 0;
if (isnan(humidity)) humidity = 0;
```
Handles sensor read failures by defaulting to 0 values.

### Non-Blocking Update Logic
```cpp
if (millis() - lastUpdate < UPDATE_MS) return;
lastUpdate = millis();
```
Uses `millis()` for precise timing without blocking other operations.

### LED Temperature Feedback
```cpp
if (temp >= HOT)       { digitalWrite(LED_RED, HIGH); digitalWrite(LED_GREEN, LOW);  }
else if (temp <= COLD) { digitalWrite(LED_RED, LOW);  digitalWrite(LED_GREEN, LOW);  }
else                   { digitalWrite(LED_RED, LOW);  digitalWrite(LED_GREEN, HIGH); }
```
Mutually exclusive LED states ensure clear temperature indication.

---

## Troubleshooting

| Issue | Possible Cause | Solution |
|-------|----------------|----------|
| LCD shows nothing | I2C address incorrect | Verify address is 0x27; use I2C scanner if unsure |
| DHT22 reading 0 | Sensor not initialized | Ensure 1.5s delay in setup() |
| LEDs not responding | Wrong pin numbers | Double-check D8 and D9 assignments |
| Serial data not updating | Baud rate mismatch | Ensure Serial.begin(9600) matches monitor speed |
| Inaccurate readings | DHT22 uncalibrated | Wait 2 minutes for sensor warm-up; check connections |

---

## Future Enhancement Ideas

- Add atmospheric pressure sensor (BMP280)
- Implement data logging to SD card
- Add WiFi connectivity (Arduino with WiFi module)
- Create mobile app to display remote data
- Add wind speed and direction sensors
- Implement historical data graphing
- Add configurable alerts and thresholds
- Support for multiple sensors in a network

---

## Project Notes

- **Simulation Only:** This project is optimized for the Wokwi simulator environment
- **Modular Code:** Each section (LCD, LEDs, DHT) can be adapted independently
- **Scalable:** Can be expanded to add more sensors or features
- **Educational:** Excellent for learning Arduino, I2C communication, and sensor integration

---

## License

This is an open-source educational project. Feel free to use, modify, and distribute for learning purposes.

---

## Author

**Project Creator:** LeoPolizzi  
**Platform:** Wokwi (Arduino Simulator)  
**Last Updated:** 2026
