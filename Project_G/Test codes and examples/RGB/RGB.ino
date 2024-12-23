#include <Adafruit_NeoPixel.h>

#define PIN            6  // Data Pin connected to WS2812B
#define NUMPIXELS      1  // Number of WS2812B LEDs

Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // Correct color order (GRB)

void setup() {
  // Initialize the LED strip
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'

  strip.setBrightness(50);  // Set the brightness (0 - 255), 50 is a lower brightness
}

void loop() {
  // Smooth color transitions between Red, Green, and Blue
  smoothColorTransition(strip.Color(255, 0, 0), strip.Color(0, 255, 0), 1000); // Red to Green
  smoothColorTransition(strip.Color(0, 255, 0), strip.Color(0, 0, 255), 1000); // Green to Blue
  smoothColorTransition(strip.Color(0, 0, 255), strip.Color(255, 0, 0), 1000); // Blue to Red
}

// Function to smoothly transition from one color to another
void smoothColorTransition(uint32_t startColor, uint32_t endColor, int duration) {
  int startRed = (startColor >> 16) & 0xFF;
  int startGreen = (startColor >> 8) & 0xFF;
  int startBlue = startColor & 0xFF;

  int endRed = (endColor >> 16) & 0xFF;
  int endGreen = (endColor >> 8) & 0xFF;
  int endBlue = endColor & 0xFF;

  for (int i = 0; i <= duration; i++) {
    // Calculate the current step's color by linear interpolation
    int red = map(i, 0, duration, startRed, endRed);
    int green = map(i, 0, duration, startGreen, endGreen);
    int blue = map(i, 0, duration, startBlue, endBlue);

    strip.setPixelColor(0, red, green, blue);  // Set the interpolated color
    strip.show();  // Update the strip
    delay(5);  // Small delay to control transition speed
  }
}
