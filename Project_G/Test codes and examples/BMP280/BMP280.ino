#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Create an object for the BMP280 sensor
Adafruit_BMP280 bmp;

// Define SDA and SCL pins
#define SDA_PIN 8
#define SCL_PIN 9

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for Serial Monitor to be ready
  }

  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the BMP280 sensor
  if (!bmp.begin(0x76)) {  // I2C address of BMP280 is 0x76
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);  // Halt the program if the sensor is not found
  }

  Serial.println("BMP280 sensor found!");

  // Set up the sensor for best performance (optional)
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating mode.
                  Adafruit_BMP280::SAMPLING_X16,   // Temp. sampling.
                  Adafruit_BMP280::SAMPLING_X16,   // Pressure sampling.
                  Adafruit_BMP280::FILTER_X16,     // Filtering.
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time.
}

void loop() {
  // Get temperature and pressure readings
  float temperature = bmp.readTemperature();  // Temperature in Celsius
  float pressure = bmp.readPressure();       // Pressure in Pa

  // Convert pressure to hPa
  pressure = pressure / 100.0;

  // Print the values to Serial Monitor
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  // Wait for a second before reading again
  delay(1000);
}
