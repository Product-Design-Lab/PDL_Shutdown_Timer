#include "PDL_Shutdown_Timer.h"
#include "FreeRTOS.h"
#include "timers.h"
#include <Arduino.h>
#include <Adafruit_TinyUSB.h>

PDL_Shutdown_Timer::PDL_Shutdown_Timer(uint8_t en_pin, float shutdown_time_sec, bool enable_gpio_state)
    : xTimer(NULL), en_pin(en_pin), shutdown_time_sec(shutdown_time_sec), enable_gpio_state(enable_gpio_state), debug(DEBUG_OFF) {
    debugInit();
    pinMode(en_pin, OUTPUT);
    keepSystemAlive();
    initializeTimer();
}

PDL_Shutdown_Timer::~PDL_Shutdown_Timer() {
    if (timerIsInitialized()) {
        xTimerDelete(xTimer, 0);
        xTimer = NULL;
        debugPrintf("Timer deleted\n");
    }
}

int PDL_Shutdown_Timer::start() {
    if (!timerIsInitialized()) return pdFAIL;
    int ret = xTimerStart(xTimer, 0);
    debugPrintf("Timer %s\n", ret == pdPASS ? "started" : "failed to start");
    return ret;
}

int PDL_Shutdown_Timer::stop() {
    if (!timerIsInitialized()) return pdFAIL;
    int ret = xTimerStop(xTimer, 0);
    debugPrintf("Timer %s\n", ret == pdPASS ? "stopped" : "failed to stop");
    return ret;
}

void PDL_Shutdown_Timer::reset() {
    if (!timerIsInitialized()) return;
    int ret = xTimerReset(xTimer, 0);
    debugPrintf("Timer %s\n", ret == pdPASS ? "reset" : "failed to reset");
}

void PDL_Shutdown_Timer::setShutdownTimeSec(float shutdown_time_sec_param) {
    if (shutdown_time_sec_param <= 0.0f) {
        debugPrintf("Invalid shutdown time (0 seconds) - Timer period not updated\n");
        return;
    }
    shutdown_time_sec = shutdown_time_sec_param;
    if (!timerIsInitialized()) return;
    if (xTimerChangePeriod(xTimer, pdMS_TO_TICKS(static_cast<uint32_t>(shutdown_time_sec * 1000)), 0) == pdPASS) {
        debugPrintf("Timer period changed to %.2f seconds\n", shutdown_time_sec_param);
    } else {
        debugPrintf("Failed to change timer period\n");
    }
}

void PDL_Shutdown_Timer::setDebug(DebugLevel debug_param) {
    if (debug_param >= DEBUG_MAX) {
        debugPrintf("Invalid debug level\n");
        return;
    }
    debug = debug_param;
}

void PDL_Shutdown_Timer::systemShutdown() {
    shutdown();
}

// Private Function Implementations

void PDL_Shutdown_Timer::debugInit() {
    Serial.begin(115200);
}

void PDL_Shutdown_Timer::debugPrintf(const char *format, ...) {
    if (debug != DEBUG_ON) return;
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void PDL_Shutdown_Timer::initializeTimer() {
    if (shutdown_time_sec <= 0.0f) {
        debugPrintf("Invalid shutdown time (0 seconds) - Timer not created\n");
        return;
    }
    xTimer = xTimerCreate("Shutdown Timer", pdMS_TO_TICKS(static_cast<uint32_t>(shutdown_time_sec * 1000)), pdFALSE, this, vTimerCallback);
    debugPrintf("Timer %s\n", xTimer != NULL ? "created" : "failed to create");
}

bool PDL_Shutdown_Timer::timerIsInitialized() {
    return xTimer != NULL;
}

void PDL_Shutdown_Timer::shutdown() {
    debugPrintf("System shutdown\n");
    digitalWrite(en_pin, !enable_gpio_state);
}

void PDL_Shutdown_Timer::keepSystemAlive() {
    digitalWrite(en_pin, enable_gpio_state);
}

void PDL_Shutdown_Timer::vTimerCallback(TimerHandle_t xTimer) {
    PDL_Shutdown_Timer *timer = static_cast<PDL_Shutdown_Timer*>(pvTimerGetTimerID(xTimer));
    if (timer) {
        timer->shutdown();
        xTimerDelete(xTimer, 0);
        timer->xTimer = NULL;
    }
}
