#include <Wire.h>
#include <DFRobot_GP8XXX.h>

// I2C address for GP8413 (0x58)
DFRobot_GP8413 GP8413(/*deviceAddr=*/0x58);

void setup() {
  // Initialize the GP8413 device
  while (GP8413.begin() != 0) {
    delay(1000); // Retry if initialization fails
  }

  // Set DAC output range to 0-10V
  GP8413.setDACOutRange(GP8413.eOutputRange10V);

  delay(500); // Wait for DAC initialization
}

void loop() {
  const int maxValue = 32767; // Maximum DAC value for 10V
  const int stepSize = 128;   // Smaller steps for smooth transitions

  // Gradually increase voltage from 0V to 10V on Channel 0
  for (int value = 0; value <= maxValue; value += stepSize) {
    int currentDelay = map(value, 0, maxValue, 5, 50); // Longer delay as voltage nears 10V
    GP8413.setDACOutVoltage(value, 0);  // Set Channel 0 voltage
    GP8413.setDACOutVoltage(value, 1);  // Set Channel 0 voltage
    delay(currentDelay);
  }

  delay(500); // Hold the voltage at 10V for 0.5 seconds

  // Gradually decrease voltage from 10V to 0V on Channel 0
  for (int value = maxValue; value >= 0; value -= stepSize) {
    int currentDelay = map(value, 0, maxValue, 50, 5); // Shorter delay at higher voltage
    GP8413.setDACOutVoltage(value, 0);  // Set Channel 0 voltage
    GP8413.setDACOutVoltage(value, 1);  // Set Channel 0 voltage
    delay(currentDelay);
  }

  delay(500); // Hold the voltage at 0V for 0.5 seconds
}
