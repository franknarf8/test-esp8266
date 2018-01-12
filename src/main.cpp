#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "wificreds.h"

void connect() {
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
}

void setup()
{
    Serial.begin(9600);
    pinMode(2, OUTPUT);
}

void loop() {
    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.println("Connected!");
        HTTPClient http;
        Serial.print("[HTTP] begin...\n");
        http.begin("http://jsonplaceholder.typicode.com/posts/1/comments");
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        http.GET();
        http.writeToStream(&Serial);
        http.end();
    }
    delay(1000);
    if(WiFi.status() != WL_CONNECTED) {
        Serial.println("Disconnected...");
        connect();
    }
    digitalWrite(2,!digitalRead(2));
}