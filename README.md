# ESP32 MQTT String Client

Simple ESP32 MQTT client using **PubSubClient** library to **publish and subscribe** string messages (no JSON parsing). Ideal for IoT prototyping, remote control (ON/OFF), sensor data, or learning MQTT.

> **Author**: hyutrn
> **Location**: VN  
> **Date**: November 16, 2025 05:40 AM +07

---

## Features

- Connects to WiFi in **Station Mode (STA)**
- Uses **HiveMQ Public Broker** (free, no setup)
- **Publishes** a string message every 10 seconds
- **Subscribes** to a topic and prints incoming messages
- **No JSON** – lightweight, easy to debug
- Auto-reconnect for WiFi and MQTT

---

## Requirements

### 1. Libraries (Install via Arduino IDE)
| Library | Purpose |
|--------|--------|
| `WiFi.h` | Built-in (ESP32) |
| `PubSubClient` | MQTT communication |
| `ArduinoJson` | *(Not used in this version)* |

> **Install**: Open Arduino IDE → **Sketch > Include Library > Manage Libraries** → Search `PubSubClient` → Install

---

## MQTT Broker (Free & Public)

| Broker | Host | Port | TLS |
|-------|------|------|-----|
| **HiveMQ Public** | `broker.mqtt-dashboard.com` | 1883 | No |

> No registration needed. Data is **public** – use only for testing.

---

## Configuration (Edit in Code)

## Test 
- Open: https://www.hivemq.com/demos/websocket-client/
- Connect (default settings are correct)
- Subscribe to: "esp32/pub/topic" =>  ESP32's messages every 10 seconds
- Publish to: "esp32/sub/topic" => ESP32 will receive and print to Serial


