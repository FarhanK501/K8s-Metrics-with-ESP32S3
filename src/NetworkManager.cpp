#include "NetworkManager.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char *ssid = "YOUR WIFI NAME/SSID";
const char *password = "YOUR WIFI PASSWORD";
const char *apiUrl = "https://mocki.io/v1/a7973e5c-e3ba-4407-9635-8e3ad08ac394"; // Update with your correct URL

void NetworkManager::setupWiFi()
{
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi..");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

MetricsData NetworkManager::fetchK8sMetrics()
{
    MetricsData metricsData; // Default initialized

    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(apiUrl); // Moved outside the loop for efficiency

        // Send HTTP GET request
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);

            StaticJsonDocument<1024> doc;

            // Deserialize the JSON response
            DeserializationError error = deserializeJson(doc, http.getString());
            if (error)
            {
                Serial.print("Failed to parse JSON: ");
                Serial.println(error.c_str());
            }
            else
            {
                // Extract data
                metricsData.pods = doc["pods"];
                metricsData.nodes = doc["nodes"];
                metricsData.cpuUsage = doc["cpu_usage"].as<String>();
                metricsData.memoryUsage = doc["memory_usage"].as<String>();
                metricsData.status = "Warn"; //hardcoding for now.
            }
            Serial.println(metricsData.nodes);
            Serial.println(metricsData.pods);
            Serial.println(metricsData.cpuUsage);
            Serial.println(metricsData.memoryUsage);
            Serial.println(metricsData.status);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    }
    else
    {
        Serial.println("WiFi Disconnected");
    }

    return metricsData;
}
