#include <Wire.h>
#include <MCP23017.h>  // Include the MCP23017 library

// Create two MCP23017 objects with different I2C addresses
MCP23017 mcp1(0x20, Wire);  // MCP23017 at address 0x20
MCP23017 mcp2(0x21, Wire);  // MCP23017 at address 0x21

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  while (!Serial);  // Wait for serial monitor to be ready

  // Initialize I2C communication
  Wire.begin();

  // Initialize MCP23017 devices by using the constructor (no need for begin())
  Serial.println("MCP23017 devices initialized!");

  // Configure MCP23017 at address 0x20 (Set GPA0 to GPA7 and GPB0 to GPB7 as outputs)
  for (uint8_t pin = 0; pin < 16; pin++) {  // GPA0 to GPA7 and GPB0 to GPB7 (16 pins total)
    mcp1.pinMode(pin, OUTPUT);  // Set all pins as OUTPUT
  }

  // Configure MCP23017 at address 0x21 (Set GPA0 to GPA6 as outputs)
  for (uint8_t pin = 0; pin < 7; pin++) {  // GPA0 to GPA6
    mcp2.pinMode(pin, OUTPUT);  // Set GPA0 to GPA6 as OUTPUT
  }

  Serial.println("Pins configured as digital outputs.");
}

void loop() {
  // Sequentially turn on all output pins on MCP23017 at address 0x20 (GPA0 to GPA7 and GPB0 to GPB7)
  for (uint8_t pin = 0; pin < 16; pin++) {  // GPA0 to GPA7 and GPB0 to GPB7 (16 pins total)
    mcp1.digitalWrite(pin, HIGH);  // Turn each pin on
    Serial.print("MCP: 1 | I2C Address: 0x20 | Pin ");
    Serial.print(pin);
    Serial.println(" is HIGH");
    delay(100);  // Small delay (100ms) to see each pin turning on sequentially
  }

  // Sequentially turn on all output pins on MCP23017 at address 0x21 (GPA0 to GPA6)
  for (uint8_t pin = 0; pin < 7; pin++) {  // GPA0 to GPA6
    mcp2.digitalWrite(pin, HIGH);  // Turn each pin on
    Serial.print("MCP: 2 | I2C Address: 0x21 | Pin ");
    Serial.print(pin);
    Serial.println(" is HIGH");
    delay(100);  // Small delay (100ms) to see each pin turning on sequentially
  }

  delay(500);  // Delay before turning off pins

  // Sequentially turn off all output pins on MCP23017 at address 0x20 (GPA0 to GPA7 and GPB0 to GPB7)
  for (uint8_t pin = 0; pin < 16; pin++) {  // GPA0 to GPA7 and GPB0 to GPB7 (16 pins total)
    mcp1.digitalWrite(pin, LOW);  // Turn each pin off
    Serial.print("MCP: 1 | I2C Address: 0x20 | Pin ");
    Serial.print(pin);
    Serial.println(" is LOW");
    delay(100);  // Small delay (100ms) to see each pin turning off sequentially
  }

  // Sequentially turn off all output pins on MCP23017 at address 0x21 (GPA0 to GPA6)
  for (uint8_t pin = 0; pin < 7; pin++) {  // GPA0 to GPA6
    mcp2.digitalWrite(pin, LOW);  // Turn each pin off
    Serial.print("MCP: 2 | I2C Address: 0x21 | Pin ");
    Serial.print(pin);
    Serial.println(" is LOW");
    delay(100);  // Small delay (100ms) to see each pin turning off sequentially
  }

  delay(500);  // Delay before the next loop iteration
}
