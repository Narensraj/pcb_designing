#include <Arduino.h>

// Task Handles
TaskHandle_t task1Handle = NULL;
TaskHandle_t task2Handle = NULL;
TaskHandle_t task3Handle = NULL;
TaskHandle_t task4Handle = NULL;
TaskHandle_t task5Handle = NULL;

// Task 1 - Print message every 1 second
void task1(void *pvParameters) {
  while (1) {
    Serial.print("Task 1 is running at ");
    Serial.println(millis());  // Print time since start
    vTaskDelay(500 / portTICK_PERIOD_MS);  // Delay for 1 second
  }
}

// Task 2 - Print message every 500ms
void task2(void *pvParameters) {
  while (1) {
    Serial.print("Task 2 is running at ");
    Serial.println(millis());  // Print time since start
    vTaskDelay(1000 / portTICK_PERIOD_MS);  // Delay for 500ms
  }
}

// Task 3 - Print message every 1.5 seconds
void task3(void *pvParameters) {
  while (1) {
    Serial.print("Task 3 is running at ");
    Serial.println(millis());  // Print time since start
    vTaskDelay(1500 / portTICK_PERIOD_MS);  // Delay for 1.5 seconds
  }
}

// Task 4 - Print message every 2 seconds
void task4(void *pvParameters) {
  while (1) {
    Serial.print("Task 4 is running at ");
    Serial.println(millis());  // Print time since start
    vTaskDelay(2000 / portTICK_PERIOD_MS);  // Delay for 2 seconds
  }
}

// Task 5 - Print message every 3 seconds
void task5(void *pvParameters) {
  while (1) {
    Serial.print("Task 5 is running at ");
    Serial.println(millis());  // Print time since start
    vTaskDelay(2500 / portTICK_PERIOD_MS);  // Delay for 3 seconds
  }
}

void setup() {
  // Start Serial communication
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // Wait for Serial Monitor to be ready
  }
  
  Serial.println("FreeRTOS Task Example");

  // Create tasks with different priorities
  xTaskCreate(task1, "Task 1", 2048, NULL, 1, &task1Handle);  // Priority 1
  xTaskCreate(task2, "Task 2", 2048, NULL, 2, &task2Handle);  // Priority 2
  xTaskCreate(task3, "Task 3", 2048, NULL, 3, &task3Handle);  // Priority 3
  xTaskCreate(task4, "Task 4", 2048, NULL, 4, &task4Handle);  // Priority 4
  xTaskCreate(task5, "Task 5", 2048, NULL, 5, &task5Handle);  // Priority 5
}

void loop() {
  // FreeRTOS scheduler takes control after setup
  // The main loop doesn't need to do anything
  // as tasks are handled by the RTOS
}
