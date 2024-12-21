#include <Wire.h>
#include <RTClib.h>

// Create an RTC object
RTC_DS3231 rtc;

// Define SDA and SCL pins
#define SDA_PIN 8
#define SCL_PIN 9

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for Serial Monitor to be ready
  }

  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  // Check if the RTC is connected
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Check if the RTC lost power and if so, set the time
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time...");
    // The following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Read the current time from the RTC
  DateTime now = rtc.now();

  // Print the current time
  Serial.print("Current time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}

void loop() {
  // Nothing to do here
}
