#include <Wire.h>
#include <Adafruit_ADS1X15.h>

// Create an object for the ADS1115 sensor
Adafruit_ADS1115 ads;

// Define SDA and SCL pins
#define SDA_PIN 8
#define SCL_PIN 9

// Channel pins for ADS1115 (default channels 0, 1, 2, 3)
#define CHANNEL_0 0  // Temperature
#define CHANNEL_1 1  // Humidity
#define CHANNEL_2 2
#define CHANNEL_3 3

// Define the ADS multiplier (used to adjust the voltage calculation)
#define ADS_MULTIPLIER 1.86623

// Define the resistance for the 4-20 mA current loop (150 ohms)
#define RESISTOR 150.0

// Temperature (Channel 0) range (-20°C to 80°C)
#define TEMP_MIN -20
#define TEMP_MAX 80

// Humidity (Channel 1) range (0% to 100%)
#define HUM_MIN 0
#define HUM_MAX 100

// Calculate the voltage range for the 4-20 mA current loop across the 150-ohm resistor
// Using Ohm's Law: V = I * R
// For 4 mA (min current) -> V = 0.004 A * 150 ohms = 0.6 V
// For 20 mA (max current) -> V = 0.02 A * 150 ohms = 3.0 V
#define VOLTAGE_MIN 0.6  // Corresponding to 4mA
#define VOLTAGE_MAX 3.0  // Corresponding to 20mA
#define VOLTAGE_RANGE (VOLTAGE_MAX - VOLTAGE_MIN)  // This is 2.4V (3.0V - 0.6V)

// Calculate the scaling factor for converting voltage to the desired range (Temperature or Humidity)
#define VOLTAGE_SCALE (VOLTAGE_RANGE)  // 2.4V range for 4-20mA

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for Serial Monitor to be ready
  }

  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the ADS1115
  if (!ads.begin()) {
    Serial.println("Couldn't find ADS1115!");
    while (1);  // Halt the program if the sensor is not found
  }

  Serial.println("ADS1115 sensor found!");
}

void loop() {
  // Read and process each channel
  for (int channel = CHANNEL_0; channel <= CHANNEL_3; channel++) {
    // Read analog values from the selected channel
    int16_t raw_value = ads.readADC_SingleEnded(channel);  // Read from the channel

    // Convert raw value to voltage using the ADS multiplier
    float voltage = raw_value * (3.3 * ADS_MULTIPLIER) / 32768.0;  // Corrected voltage calculation

    // For Channels 0 (Temperature) and 1 (Humidity), map voltage to the respective range
    if (channel == CHANNEL_0) {
      // Calculate temperature for Channel 0 (Temperature range: -20°C to 80°C)
      float temperature = map_voltage_to_temperature(voltage);
      Serial.print("Channel 0 (Temperature) - Voltage: ");
      Serial.print(voltage, 4);
      Serial.print(" V  Temperature: ");
      Serial.print(temperature);
      Serial.println(" °C");
    } 
    else if (channel == CHANNEL_1) {
      // Calculate humidity for Channel 1 (Humidity range: 0% to 100%)
      float humidity = map_voltage_to_humidity(voltage);
      Serial.print("Channel 1 (Humidity) - Voltage: ");
      Serial.print(voltage, 4);
      Serial.print(" V  Humidity: ");
      Serial.print(humidity);
      Serial.println(" %");
    } 
    else {
      // For other channels, just print the voltage
      Serial.print("Channel ");
      Serial.print(channel);
      Serial.print(" - Voltage: ");
      Serial.print(voltage, 4);
      Serial.println(" V");
    }
  }

  // Wait for a second before reading again
  delay(1000);
}

// Refined map for temperature based on voltage (0.4V to 2.0V -> -20°C to 80°C)
float map_voltage_to_temperature(float voltage) {
  // Map voltage to temperature range (-20°C to 80°C)
  float temperature = (voltage - VOLTAGE_MIN) * (TEMP_MAX - TEMP_MIN) / VOLTAGE_RANGE + TEMP_MIN;
  return temperature;
}

// Map the voltage (4-20 mA range) to humidity (0% to 100%) for Channel 1
float map_voltage_to_humidity(float voltage) {
  // Map voltage to humidity range (0% to 100%)
  float humidity = (voltage - VOLTAGE_MIN) * (HUM_MAX - HUM_MIN) / VOLTAGE_RANGE + HUM_MIN;
  return humidity;
}
