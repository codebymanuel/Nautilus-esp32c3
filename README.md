# Nautilus: ESP32-C3 Environmental Telemetry via Telegram Bot

---

## Technical Specifications and BOM
- MCU: ESP32-C3-Mini (3.3V Logic)
- Sensor: DHT22 / AM2302 (Red Module)
- Cables: 3x Female-Female Jumpers
- Power: USB-C (Regulated)

---

## Hardware Logic and Wiring
The Red Module version of the AM2302 was selected for its integrated pull-up resistor. This ensures signal stability on the 3.3V logic line of the ESP32-C3 without requiring external resistors.

Connection Mapping:
- VCC  -> 3.3V
- GND  -> GND
- DATA -> GPIO 2

## Electrical Safety Warning
- VOLTAGE LIMIT: 5.0V MAX. 
- CRITICAL: Do NOT connect a 9V battery directly to the pins. This will cause immediate thermal destruction of the ESP32-C3 and the sensor. 
- Always use the USB-C port or a regulated 3.3V/5V power source.

---

## Telegram Bot Configuration
To communicate with your ESP32-C3, you must retrieve two unique identifiers:

1. API Token (The Bot ID):
   - Open Telegram and search for @BotFather.
   - Send the command /newbot.
   - Follow the prompts to set a name and a username.
   - BotFather will provide an API Token (e.g., 123456789:ABCDEF...). Copy this.

2. Chat ID (Your Personal ID):
   - Search for @IDBot or @userinfobot on Telegram.
   - Send the command /start.
   - The bot will reply with your personal numeric ID (e.g., 987654321).
   - This ID ensures that the ESP32 sends data only to you and not to strangers.

---

## Software Requirements
Install these libraries via Arduino Library Manager:
1. UniversalTelegramBot by Brian Lough
2. ArduinoJson by Benoit Blanchon
3. DHT sensor library by Adafruit

---

## Deployment Flow
1. Hardware: Connect the DHT22 to GPIO 2 as per mapping.
2. Config: Rename arduino_secrets.h.example to arduino_secrets.h.
3. Credentials: Fill in SSID, PASSWORD, BOT_TOKEN, and CHAT_ID in the secrets file.
4. Compilation: Flash using 'ESP32C3 Dev Module' board settings.

---

## Data Logic (Humidity)
- Optimal: < 60%
- Warning: 60-80%
- Critical: > 80%

---
Version: 1.0.0 | Author: codebymanuel | License: GPLv3
