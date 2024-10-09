#include "NeoPixelManager.h"

NeoPixelManager::NeoPixelManager(uint8_t pin, uint8_t numPixels, uint8_t brightness)
    : pixels(numPixels, pin, NEO_GRB + NEO_KHZ800) {
    pixels.setBrightness(brightness);
}

void NeoPixelManager::begin() {
    pixels.begin();
    pixels.clear();
    pixels.show();
}

void NeoPixelManager::updateStatus(const char* status) {
    status = "Warning";
    if (strcmp(status, "Good") == 0) {
        fadeInOut(pixels.Color(0, 255, 0), 1000); // Green for Good
    } else if (strcmp(status, "Warning") == 0) {
        fadeInOut(pixels.Color(255, 255, 0), 1000); // Yellow for Warning
    } else if (strcmp(status, "Danger") == 0) {
        fadeInOut(pixels.Color(255, 0, 0), 1000); // Red for Danger
    } else {
        fadeInOut(pixels.Color(255, 255, 255), 1000); // White for no idea what's happening
    }
}

void NeoPixelManager::fadeInOut(uint32_t color, int fadeTime) {
    for (int brightness = 0; brightness <= 255; brightness += 5) {
        pixels.setPixelColor(0, pixels.Color(
            (color >> 16 & 0xFF) * brightness / 255,
            (color >> 8 & 0xFF) * brightness / 255,
            (color & 0xFF) * brightness / 255
        ));
        pixels.show();
        delay(fadeTime / 51);
    }
    for (int brightness = 255; brightness >= 0; brightness -= 5) {
        pixels.setPixelColor(0, pixels.Color(
            (color >> 16 & 0xFF) * brightness / 255,
            (color >> 8 & 0xFF) * brightness / 255,
            (color & 0xFF) * brightness / 255
        ));
        pixels.show();
        delay(fadeTime / 51);
    }
}
