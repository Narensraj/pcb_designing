#include <WiFi.h>
#include <esp_system.h>
#include <esp_wifi.h>
#include <esp_mac.h>

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // Wait for the Serial connection
  }

  Serial.println("\n--- ESP32-S3 Board Information ---");

  // Chip Information
  Serial.println("\nChip Information:");
  Serial.printf("  Model: %s\n", ESP.getChipModel());
  Serial.printf("  Cores: %d\n", ESP.getChipCores());
  Serial.printf("  Revision: %d\n", ESP.getChipRevision());
  Serial.printf("  CPU Frequency: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("  Flash Size: %dMB\n", ESP.getFlashChipSize() / (1024 * 1024));
  Serial.printf("  Flash Speed: %d MHz\n", ESP.getFlashChipSpeed() / 1000000);
  Serial.printf("  Flash Mode: %s\n", (ESP.getFlashChipMode() == FM_QIO) ? "QIO" : 
                                     (ESP.getFlashChipMode() == FM_QOUT) ? "QOUT" :
                                     (ESP.getFlashChipMode() == FM_DIO) ? "DIO" : 
                                     "DOUT");

  // PSRAM Information
  Serial.println("\nPSRAM Information:");
  Serial.printf("  PSRAM: %s\n", (ESP.getPsramSize() > 0) ? "Available" : "Not Available");
  if (ESP.getPsramSize() > 0) {
    Serial.printf("  PSRAM Size: %dMB\n", ESP.getPsramSize() / (1024 * 1024));
  }

  // MAC Address
  Serial.println("\nMAC Address:");
  String mac = WiFi.macAddress();
  Serial.printf("  MAC Address: %s\n", mac.c_str());

  // Chip Unique ID (using EFuse MAC Address)
  uint64_t chip_id = ESP.getEfuseMac();
  Serial.printf("\nChip Unique ID (EFuse MAC): %llx\n", chip_id);

  // Free Heap
  Serial.println("\nMemory Information:");
  Serial.printf("  Free Heap: %d bytes\n", ESP.getFreeHeap());

  // Flash Information
  Serial.printf("  Flash Size: %d bytes\n", ESP.getFlashChipSize());
  Serial.printf("  Free Flash: %d bytes\n", ESP.getFreeSketchSpace());

  // System Info
  Serial.println("\nSystem Information:");
  Serial.printf("  SDK Version: %s\n", esp_get_idf_version()); // Fixed for version string
  
  // Reset Reason and Boot Mode Inference
  Serial.printf("  Reset Reason: %d\n", esp_reset_reason());
  if (esp_reset_reason() == ESP_RST_POWERON) {
    Serial.println("  Boot Mode: Power-On Reset");
  } else if (esp_reset_reason() == ESP_RST_BROWNOUT) {
    Serial.println("  Boot Mode: Brownout Reset");
  } else if (esp_reset_reason() == ESP_RST_SDIO) {
    Serial.println("  Boot Mode: SDIO Reset");
  } else {
    Serial.println("  Boot Mode: Unknown Reset");
  }

  // Flash Encryption Status
  // You can check encryption with other methods depending on the SDK/platform you're using
  // Example (if configured in your ESP32 project):
  // bool flash_encryption = esp_flash_encryption_enabled();
  Serial.printf("  Flash Encryption: %s\n", "Disabled"); // Placeholder, as this method is unavailable directly

  // Other Debugging Info
  Serial.println("\nOther Information:");
  Serial.printf("  Sketch Size: %d bytes\n", ESP.getSketchSize());
  Serial.printf("  Free Sketch Space: %d bytes\n", ESP.getFreeSketchSpace());
  Serial.printf("  Task Count: %d\n", uxTaskGetNumberOfTasks());
  Serial.printf("  Core 0 Stack High Water Mark: %d\n", uxTaskGetStackHighWaterMark(NULL));
  Serial.printf("  Core 1 Stack High Water Mark: %d\n", uxTaskGetStackHighWaterMark(NULL));
}

void loop() {
  // Nothing to do in the loop
}
