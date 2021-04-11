/*
 * The ESP32 has 2 Tensilica LX6 cores, allowing us to run tasks in both CPUs. For using both core the application need to use tasks. 
 * This code sample will give a basic idea how to archieve this goal. The portTICK_PERIOD_MS const is the tick rate of the ESP32.
 * 
 * More information about multi tasking with an ESP32 on:
 * - https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html#_CPPv410vTaskDelayK10TickType_t
 * - https://techtutorialsx.com/2017/05/09/esp32-get-task-execution-core/
 * 
 * Open the serial monitor in Arduino IDE to see the serial messages with a baud rate of 115200 and see device for the blue LED activity.
 */

// Arduino pin number of the blue LED 
const byte ledPin = A12;

void setup() {
  // Set the baud rate for the serial connection
  Serial.begin(115200);
  
  // Set the LED pin to OUTPUT as we want to provide a signal to the
  // pin instead of reading from it (INPUT). If you do not set the mode
  // the LED may appear dim.
  pinMode(ledPin, OUTPUT);

  printCoreID("Setup");

  // Create and start the task for blinking the LED light
  xTaskCreate(
    toggleLedTask,     // Function that should be called
    "Toggle LED task", // Name of the task (for debugging)
    1000,              // Stack size (bytes)
    NULL,              // Parameter to pass
    1,                 // Task priority
    NULL               // Task handle
  );

  // Create and start the task for print a message to the serial output
  xTaskCreate(
    dummyTask,    // Function that should be called
    "Dummy task", // Name of the task (for debugging)
    1000,         // Stack size (bytes)
    NULL,         // Parameter to pass
    1,            // Task priority
    NULL          // Task handle
  );
}

void toggleLedTask(void * parameter) {
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  
  for(;;) { // infinite loop
    printCoreID("Toggle LED task");
    
    // Turn the LED on
    digitalWrite(ledPin, HIGH);

    // Pause the task for 500ms
    vTaskDelay(xDelay);

    // Turn the LED off
    digitalWrite(ledPin, LOW);

    // Pause the task again for 500ms
    vTaskDelay(xDelay);
  }
}

void dummyTask(void * parameter) {
  const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  
  for(;;) { // infinite loop
    printCoreID("Dummy task");
    
    // Pause the task for 500ms
    vTaskDelay(xDelay);
  }
}

void printCoreID(String activity) {
  Serial.print(activity + ": Executing on core ID: ");
  Serial.println(xPortGetCoreID());
}

void loop() {
  printCoreID("Main Loop");
  
  // Wait for a second before looping again
  delay(1000);
}
