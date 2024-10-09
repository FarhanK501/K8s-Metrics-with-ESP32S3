#ifndef NEOPIXEL_MANAGER_H
#define NEOPIXEL_MANAGER_H

#include <Adafruit_NeoPixel.h>

class NeoPixelManager
{
public:
    NeoPixelManager(uint8_t pin, uint8_t numPixels, uint8_t brightness);
    void begin();
    void updateStatus(const char *status);

private:
    Adafruit_NeoPixel pixels;
    void fadeInOut(uint32_t color, int fadeTime);
};

#endif
