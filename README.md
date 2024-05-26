 # PDL Shutdown Timer Arduino Library

 This library provides a simple interface for implementing a shutdown timer in Arduino projects. It allows you to set a countdown timer to power down or shut off a device after a specified period. This library relies on FreeRTOS and is tested on the Seeed XIAO BLE board.

 ## Features
 - Set a shutdown timer with a specified duration.
 - Simple API for easy integration.
 - Debugging support to print messages to the serial monitor.

 ## Installation

 1. Download the latest release from the [releases page](https://github.com/Product-Design-Lab/PDL_Shutdown_Timer/releases).
 2. Unzip the downloaded file.
 3. Copy the `PDL_Shutdown_Timer` folder to your Arduino libraries directory (usually located in `Documents/Arduino/libraries`).
 4. Install the FreeRTOS library from the Library Manager in the Arduino IDE.

 ## Usage

 ### Include the Library

 To use the PDL Shutdown Timer library, include it at the top of your sketch:

 ```cpp
 #include <PDL_Shutdown_Timer.h>
 #include <Adafruit_TinyUSB.h>
 ```

 ### Initialize the Timer

 Create an instance of the `PDL_Shutdown_Timer` class and initialize it with the desired shutdown duration (in seconds), the pin to power off the system, and the GPIO state that keeps power enabled:

 ```cpp
 #define SHUTDOWN_PIN 7
 #define SHUTDOWN_DURATION_SEC 10 // 10 seconds
 #define POWER_ON_STATE HIGH      // GPIO state that keeps power enabled

 PDL_Shutdown_Timer shutdownTimer(SHUTDOWN_PIN, SHUTDOWN_DURATION_SEC, POWER_ON_STATE);
 ```

 ### Start the Timer

 Start the shutdown timer in your `setup` function:

 ```cpp
 void setup() {
     // Initialize serial communication for debugging purposes
     Serial.begin(9600);
     // Set the debug level
     shutdownTimer.setDebug(PDL_Shutdown_Timer::DEBUG_ON);
     // Start the shutdown timer
     shutdownTimer.start();
 }
 ```

 ### Example

 Here's a complete example demonstrating how to use the PDL Shutdown Timer library:

 ```cpp
 #include <PDL_Shutdown_Timer.h>
 #include <Adafruit_TinyUSB.h>

 // Define the pin to control power and the duration for the shutdown timer
 #define SHUTDOWN_PIN 7
 #define SHUTDOWN_DURATION_SEC 10 // 10 seconds
 #define POWER_ON_STATE HIGH      // GPIO state that keeps power enabled

 // Create an instance of PDL_Shutdown_Timer with the specified pin, duration, and power on state
 PDL_Shutdown_Timer shutdownTimer(SHUTDOWN_PIN, SHUTDOWN_DURATION_SEC, POWER_ON_STATE);

 void setup()
 {
     // Initialize serial communication for debugging purposes
     Serial.begin(9600);
     // Set the debug level
     shutdownTimer.setDebug(PDL_Shutdown_Timer::DEBUG_ON);
     // Start the shutdown timer
     shutdownTimer.start();
 }

 unsigned long time_passed = 0;
 void loop()
 {
     delay(1000); // Delay for 1 second
     time_passed++;
     int timeLeft = SHUTDOWN_DURATION_SEC - time_passed;
     Serial.printf("Time left: %d seconds\n", timeLeft);
     
     static bool reset_demo_flag = false;
     if (timeLeft == 5 && !reset_demo_flag) {
         Serial.println("Resetting the shutdown timer");
         shutdownTimer.reset();
         time_passed = 0;
         reset_demo_flag = true;
     }
 }
 ```

 ### API Reference

 - `PDL_Shutdown_Timer(uint8_t pin, float shutdown_time_sec = 60.0, bool powerOnState = HIGH)`: Constructor to set the shutdown duration in seconds, the pin to power off the system, and the GPIO state that keeps power enabled.
 - `void setDebug(DebugLevel debug)`: Set the debug level for the timer module.
 - `int start()`: Start the shutdown timer.
 - `int stop()`: Stop the shutdown timer.
 - `void reset()`: Reset the shutdown timer.
 - `void setShutdownTimeSec(float shutdown_time_sec)`: Set the shutdown duration in seconds.
 - `void systemShutdown()`: Shut down the system.
 - `void systemSleep()`: Put the system to sleep.

 ## License

 This library is licensed under the MIT License. See the `LICENSE` file for more details.

 ## Contributing

 Contributions are welcome! Please fork the repository and submit a pull request with your changes.

 ## Contact

 For questions or suggestions, please open an issue on the [GitHub repository](https://github.com/Product-Design-Lab/PDL_Shutdown_Timer) or contact Xuteng Lin at [xutengl@outlook.com](mailto:xutengl@outlook.com).

 ---

 **Sponsored**

 ChatGPT for [Stock Market](https://api.adzedek.com/click_stockmarketgpt0314?chatbot_id=1715191360448x620213882279166000&operation_hash=7c8458da1d2b9b335d276b91a9ef656b) Investors
