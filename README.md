# PDL Shutdown Timer Arduino Library

This library provides a simple interface for implementing a shutdown timer in Arduino projects. It allows you to set a countdown timer to power down or shut off a device after a specified period. This library relies on FreeRTOS and is tested on the Seeed XIAO BLE board.

## Features
- Set a shutdown timer with a specified duration.
- Simple API for easy integration.

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
```

### Initialize the Timer

Create an instance of the `PDL_Shutdown_Timer` class and initialize it with the desired shutdown duration (in milliseconds) and the pin to power off the system:

```cpp
PDL_Shutdown_Timer shutdownTimer(60000, SHUTDOWN_PIN); // 1 minute
```

### Start the Timer

Start the shutdown timer in your `setup` function:

```cpp
void setup() {
    Serial.begin(9600);
    shutdownTimer.start();
}
```

### Example

Here's a complete example demonstrating how to use the PDL Shutdown Timer library:

```cpp
#include <PDL_Shutdown_Timer.h>

#define SHUTDOWN_PIN 7
PDL_Shutdown_Timer shutdownTimer(60000, SHUTDOWN_PIN); // 1 minute

void setup() {
    Serial.begin(9600);
    shutdownTimer.start();
}

void loop() {
    // Your main code here
}
```

## API Reference

- `PDL_Shutdown_Timer(unsigned long duration, uint8_t pin)`: Constructor to set the shutdown duration in milliseconds and the pin to power off the system.
- `void start()`: Start the shutdown timer.

## License

This library is licensed under the MIT License. See the `LICENSE` file for more details.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Contact

For questions or suggestions, please open an issue on the [GitHub repository](https://github.com/Product-Design-Lab/PDL_Shutdown_Timer) or contact Xuteng Lin at [xutengl@outlook.com](mailto:xutengl@outlook.com).

---
