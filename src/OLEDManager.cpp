#include "OLEDManager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

OLEDManager::OLEDManager() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET) {}

void OLEDManager::initializeDisplay()
{ // SDA, SCL
    Wire.begin(15, 37);

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Halt execution if display fails
    }

    // Clear the OLED display
    display.clearDisplay();
    display.display();
}

void OLEDManager::clearDisplay()
{
    display.clearDisplay();
    display.display();
}

void OLEDManager::displayStaticText()
{
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("K8s Status"));
    display.display();
}

void OLEDManager::displayMetrics(MetricsData &metricsData)
{
    // metricsData.status = "OK";
    display.clearDisplay();
    display.setCursor(1, 0);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("GKE Status"));

    display.setTextSize(1);
    display.printf("Pods: %d | ", metricsData.pods); display.printf("Nodes: %d\n", metricsData.nodes);
    // Draw Bar Graph for Memory and CPU usage
    displayBarGraph(metricsData);
    display.setCursor(0, 52);
    display.printf("State:%s, ", metricsData.status.c_str());
    display.printf("Count: %d\n", metricsData.numberOfTimesInformationFetched);
    display.display();
}

void OLEDManager::displayBarGraph(MetricsData& metricsData)
{
  // Clear the area for the bar graph
    display.fillRect(0, 24, SCREEN_WIDTH, 24, SSD1306_BLACK); // Clear previous bars

    // Draw Memory Usage Bar
    display.setCursor(0, 24);
    display.setTextSize(1);
    display.printf("Memory Usage: %s\n", metricsData.memoryUsage); // Show memory usage
    int memoryBarWidth = (872 / 1024.0) * SCREEN_WIDTH; 
    display.fillRect(0, 34, memoryBarWidth, 3, SSD1306_WHITE); // Memory bar

    // Draw CPU Usage Bar
    display.setCursor(0, 38);
    display.printf("CPU Usage: %s\n", metricsData.cpuUsage); // Show CPU usage
    int cpuBarWidth = (40 / 100.0) * SCREEN_WIDTH; 
    display.fillRect(0, 48, cpuBarWidth, 3, SSD1306_WHITE); // CPU bar
    
    display.display();
}
