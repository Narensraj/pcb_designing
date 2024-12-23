#include <ModbusMaster.h>

#define TX_PIN 15  // RS485 TX pin
#define RX_PIN 16  // RS485 RX pin

// Create ModbusMaster object
ModbusMaster node;

// Create an instance of HardwareSerial for RS485 communication
HardwareSerial mySerial(1);

// Previous values for temperature and humidity
float prevTemperature = -9999.0;  // Initialize with an impossible value
float prevHumidity = -9999.0;     // Initialize with an impossible value

void setup() {
  Serial.begin(115200);  // Initialize serial communication for debugging
  while (!Serial);       // Wait for Serial to initialize

  // Initialize RS485 communication
  mySerial.begin(4800, SERIAL_8N1, RX_PIN, TX_PIN);  // 4800 baud, 8N1 format
  node.begin(1, mySerial);                          // Modbus address 1

  Serial.println("Modbus communication initialized...");
}

void loop() {
  uint8_t result;
  float temperature = 0.0;
  float humidity = 0.0;

  // Request data from Modbus slave
  result = node.readHoldingRegisters(0x0000, 2);  // Reading 2 registers for temperature and humidity

  if (result == node.ku8MBSuccess) {
    // Process humidity
    uint16_t humidityRaw = node.getResponseBuffer(0);
    humidity = humidityRaw / 10.0;  // Convert to 0.1% units

    // Process temperature
    uint16_t tempRaw = node.getResponseBuffer(1);
    if (tempRaw & 0x8000) {
      // Handle negative temperature values (two's complement)
      tempRaw = ~tempRaw + 1;
      temperature = -tempRaw / 10.0;
    } else {
      temperature = tempRaw / 10.0;
    }

    // Update only if values have changed
    if (temperature != prevTemperature || humidity != prevHumidity) {
      printData(temperature, humidity);
      prevTemperature = temperature;  // Update previous temperature
      prevHumidity = humidity;        // Update previous humidity
    }
  } else {
    handleError(result);
  }

  delay(1000);  // Delay between Modbus requests
}

// Function to print temperature and humidity to Serial Plotter
void printData(float temperature, float humidity) {
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("\t");  // Tab-separated format for Serial Plotter
  Serial.print("Humidity: ");
  Serial.println(humidity);
}

// Function to handle and decode errors
void handleError(uint8_t errorCode) {
  Serial.print("Modbus read failed with error code: ");
  Serial.println(errorCode);

  switch (errorCode) {
    case 224:
      Serial.println("Error: Response Timed Out. Check connection or slave device.");
      break;
    case 225:
      Serial.println("Error: Invalid CRC. Verify wiring and ensure no data corruption.");
      break;
    case 226:
      Serial.println("Error: Invalid Function. Confirm the Modbus function code is supported.");
      break;
    default:
      Serial.println("Error: Unknown issue. Verify Modbus settings and slave device.");
      break;
  }
}
