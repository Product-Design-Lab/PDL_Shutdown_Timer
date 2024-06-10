#include <PDL_Shutdown_Timer.h>
#include <Adafruit_TinyUSB.h>

// Define the pin to control power and the duration for the shutdown timer
#define SHUTDOWN_PIN 6
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
    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, HIGH);
}

unsigned long time_passed = 0;
void loop()
{
    digitalWrite(LED_GREEN, HIGH);
    delay(500);
    digitalWrite(LED_GREEN, LOW);
    delay(500); // Delay for 1 second
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
