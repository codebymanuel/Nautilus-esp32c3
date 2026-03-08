/*
 * Nautilus - ESP32-C3 Environmental Monitor
 * Version: 1.0.0
 * Author: codebyleunam 
 * License: GNU GPLv3
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 */
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#include "arduino_secrets.h" 

//  Fill your credentials in arduino_secrets.h values below are placeholders.
const char* ssid = SECRET_SSID; 
const char* password = SECRET_PASS;
const char* botToken = SECRET_BOT_TOKEN;
const char* yourID = SECRET_YOUR_ID; 

#define DHTPIN 2     
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

void setup() {
  Serial.begin(115200);
  dht.begin(); 
  
  WiFi.begin(ssid, password);
  client.setInsecure(); // Required for ESP32 to skip SSL certificate validation

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // System Startup Notification
  bot.sendMessage(yourID, "⚓ Nautilus: Online!", "");
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if sensor is responding
  if (isnan(h) || isnan(t)) {
    Serial.println("Sensor Error!");
    return;
  }

  // --- NAUTILUS TRAFFIC LIGHT LOGIC ---
  // Thresholds: Green < 60%, Yellow 60-80%, Red > 80%
  String statusEmoji = (h < 60.0) ? "🟢" : (h <= 80.0 ? "🟡" : "🔴");
  String statusMsg = (h < 60.0) ? "Safe Navigation" : (h <= 80.0 ? "Sector Fog" : "Hull Pressure Alert!");

  // Message formatting
  String message = "📟 NAUTILUS MONITOR\n";
  message += "───────────────────\n";
  message += statusEmoji + " Status: " + statusMsg + "\n";
  message += "🌡️ Temp: " + String(t, 1) + "°C\n";
  message += "💧 Humid: " + String(h, 1) + "%\n";
  message += "───────────────────";

  // Dispatch to User ID
  bot.sendMessage(yourID, message, "");   
  
  delay(300000); // 5-minute telemetry interval
}
