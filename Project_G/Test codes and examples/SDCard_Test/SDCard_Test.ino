#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <MCP23017.h>

// Create an MCP23017 object for the GPIO expander
MCP23017 mcp1(0x20);  // MCP23017 with I2C address 0x20

// SPI Pins
#define SCK 12
#define MISO 13
#define MOSI 11
#define CS_PIN_EXPANDER 4  // GPA4 pin as CS for SD card

File testFile;

void setup() {
  // Initialize Serial (optional, for debugging)
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for Serial to initialize
  }
  Serial.println("Serial initialized!");

  // Initialize I2C
  Wire.begin();
  Serial.println("I2C initialized!");

  // Set GPA4 (CS) as an output pin and make it HIGH (inactive)
  mcp1.pinMode(CS_PIN_EXPANDER, OUTPUT);
  mcp1.digitalWrite(CS_PIN_EXPANDER, HIGH);
  Serial.println("GPIO expander initialized!");

  // Initialize SPI manually
  SPI.begin(SCK, MISO, MOSI);
  Serial.println("SPI initialized!");

  // Initialize SD card
  setCS(false);  // Pull CS low
  if (!SD.begin(-1)) {  // No hardware CS pin; manual control
    Serial.println("SD card initialization failed!");
    setCS(true);  // Pull CS high
    while (1);  // Halt execution
  }
  setCS(true);  // Pull CS high
  Serial.println("SD card is ready to use.");

  // Write to SD card
  writeTestFile();

  // Read from SD card
  readTestFile();
}

void loop() {
  // Indicate that the loop is running
  delay(1000);
}

/**
 * @brief Set the CS pin state through the GPIO expander.
 * @param state CS state (false for active/LOW, true for inactive/HIGH).
 */
void setCS(bool state) {
  if (state) {
    mcp1.digitalWrite(CS_PIN_EXPANDER, HIGH);  // Set GPA4 high (inactive)
  } else {
    mcp1.digitalWrite(CS_PIN_EXPANDER, LOW);   // Set GPA4 low (active)
  }
}

/**
 * @brief Write test data to a file on the SD card.
 */
void writeTestFile() {
  setCS(false);  // Activate CS
  
  // Open the file for writing (create if it doesn't exist)
  testFile = SD.open("/testfile.txt", FILE_WRITE);
  if (testFile) {
    // Write some test data
    testFile.println("Hello, this is a test file on the SD card.");
    testFile.println("This is the second line of the file.");
    testFile.close();  // Close the file after writing
    Serial.println("Test file written to SD card.");
  } else {
    Serial.println("Failed to open test file for writing.");
  }
  
  setCS(true);  // Deactivate CS
}

/**
 * @brief Read and display the contents of the test file from the SD card.
 */
void readTestFile() {
  setCS(false);  // Activate CS
  
  // Open the file for reading
  testFile = SD.open("/testfile.txt");
  if (testFile) {
    Serial.println("Reading test file contents:");
    // Read and print each line from the file
    while (testFile.available()) {
      Serial.write(testFile.read());
    }
    testFile.close();  // Close the file after reading
  } else {
    Serial.println("Failed to open test file for reading.");
  }
  
  setCS(true);  // Deactivate CS
}
