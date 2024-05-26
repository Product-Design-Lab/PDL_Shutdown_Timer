#pragma once

#include <Arduino.h>
#include <stdint.h>

class PDL_Shutdown_Timer {
public:
    enum DebugLevel {
        DEBUG_OFF = 0,
        DEBUG_ON = 1,
        DEBUG_MAX,
    };

    // Constructor with default values for shutdown_time_sec and enable_gpio_state
    PDL_Shutdown_Timer(uint8_t en_pin, float shutdown_time_sec = 60.0, bool enable_gpio_state = HIGH);
    
    // Destructor to clean up resources
    ~PDL_Shutdown_Timer();

    // Starts the shutdown timer
    int start();
    // Stops the shutdown timer
    int stop();
    // Resets the shutdown timer
    void reset();

    // Sets the shutdown duration in seconds
    void setShutdownTimeSec(float shutdown_time_sec);

    // Sets the debug level for the timer module
    void setDebug(DebugLevel debug);

    // Shuts down the system
    void systemShutdown();

private:
    // Private Variables
    TimerHandle_t xTimer;
    const uint8_t en_pin;
    float shutdown_time_sec;
    const bool enable_gpio_state;
    DebugLevel debug = DEBUG_ON;

    // Private Function Prototypes
    static void vTimerCallback(TimerHandle_t xTimer);
    void initializeTimer();
    bool timerIsInitialized();
    void shutdown();
    void keepSystemAlive();

    // Debugging
    void debugPrintf(const char *format, ...);
    void debugInit();
};
