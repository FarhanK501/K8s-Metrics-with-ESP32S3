#include "NetworkManager.h"
#include "NeoPixelManager.h"
#include "OLEDManager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define PIN_NEOPIXEL 48
#define NUMPIXELS 1
#define BRIGHTNESS 64

NetworkManager networkManager;
NeoPixelManager neoPixelManager(PIN_NEOPIXEL, NUMPIXELS, BRIGHTNESS);
OLEDManager oledManager;

void setup()
{
    networkManager.setupWiFi();
    Serial.begin(115200);
    oledManager.initializeDisplay();
    Serial.println("Hello, ESP32-S3!");
    oledManager.displayStaticText();
}
int i = 1;
void loop()
{
    i++;
    // Fetch Kubernetes metrics
    MetricsData metricsJson = networkManager.fetchK8sMetrics();
    metricsJson.numberOfTimesInformationFetched = i;
    metricsJson.status = "Warn";
    // Update OLED Display with fetched metrics
    oledManager.displayMetrics(metricsJson);

    neoPixelManager.updateStatus("Warning");

    delay(5000);
}
