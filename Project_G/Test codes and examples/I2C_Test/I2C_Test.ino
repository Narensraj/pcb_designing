#include <Wire.h>

#define SDA_PIN 8  
#define SCL_PIN 9  

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for the serial connection
  }

  // Initialize I2C with custom SDA and SCL pins
  Wire.begin(SDA_PIN, SCL_PIN);

  Serial.println("\n--- I2C Device Scan ---");

  // Start scanning for devices
  byte error, address;
  int nDevices = 0;

  // Scan from address 1 to 127
  for (address = 1; address < 128; address++) {
    // Start communication with the current address
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      // Device found at address
      Serial.print("I2C device found at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    } 
    else if (error == 4) {
      // If there is a different error
      Serial.print("Unknown error at address 0x");
      if (address < 16) {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }

  if (nDevices == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.print("Found ");
    Serial.print(nDevices);
    Serial.println(" I2C devices.");
  }
}

void loop() {
  // Nothing to do in the loop
}
