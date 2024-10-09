#ifndef OLED_MANAGER_H
#define OLED_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "MetricsData.h"

class OLEDManager {
  private:
    Adafruit_SSD1306 display;

  public:
    OLEDManager();
    void initializeDisplay();
    void displayStaticText();
    void displayMetrics(MetricsData& metricsData);
    void clearDisplay();
    void displayBarGraph(MetricsData& metricsData);  // New method for displaying a bar
};

#endif
