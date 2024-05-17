# RAT (Retrobright Appliance Tub)

This is a simple project for personal use in which I'm building a retrobright box to clean the plastics of my vintage computer and consoles collection. In this project, I'm sharing the code for the system that controls the UV light and temperature control of the retrobright solution, based on an ESP32 controller with a TFT screen.

## What is Retrobright?

Retrobright is a technique used to reverse the yellowing of ABS plastics, commonly found in old computer and gaming hardware. The yellowing is caused by a chemical reaction due to the exposure of bromine, which was used as a flame retardant in these plastics, to UV light and oxygen. The retrobright process typically involves applying a hydrogen peroxide solution to the plastic and exposing it to UV light. This project automates part of that process by maintaining the appropriate temperature and controlling the UV light exposure.

## The RAT (Retrobright Appliance Tub)

I've decided to call our retrobright box the RAT (Retrobright Appliance Tub). The RAT automates the retrobright process by controlling the temperature of the solution and the UV light exposure, ensuring optimal conditions for de-yellowing vintage plastics.

## Project Description

This project is based on an ESP32 microcontroller with a TFT screen. The system reads temperature data from a DS18B20 sensor and displays it on the screen. It also allows the user to adjust the target temperature and duration of the UV light exposure using buttons connected to the ESP32.

### Code Overview

- **main.cpp**: Sets up the environment, initializes the components, and calls the `Update` methods of the `TemperatureManager`, `UiManager`, and `InputManager` in the main loop.
- **temperature_manager.hpp / temperature_manager.cpp**: Manages the temperature readings from a DS18B20 sensor, providing methods to get the current temperature as a float or string.
- **input_manager.hpp / input_manager.cpp**: Handles input from three buttons, with debouncing logic, and triggers callbacks for left, right, and select button presses.
- **ui_manager.hpp / ui_manager.cpp**: Manages the UI, including a startup screen, a main menu, and screens for adjusting temperature and time. It uses double buffering to avoid flickering and displays the current temperature in the header.

### Dependencies

This project depends on the following external libraries:

- **OneWire**: Used for communication with the DS18B20 temperature sensor.
- **DallasTemperature**: A library specifically for reading from Dallas temperature sensors like the DS18B20.
- **TFT_eSPI**: A library for handling the TFT screen.

You can install these libraries via the Arduino Library Manager or using PlatformIO.

### How to Build

1. **Clone the repository**:
   ```sh
   git clone https://github.com/yourusername/your-repo-name.git
   cd your-repo-name

2. **Install dependencies** using Arduino Library Manager or PlatformIO:
 - OneWire
 - DallasTemperature
 - TFT_eSPI

3. **Open the project** in your preferred IDE (I'm using VS Code with PlatformIO).

4. **Configure your hardware settings** (e.g., the correct pin numbers for your buttons and DS18B20 sensor) in the source files if needed.

5. **Upload the code to your ESP32.**

## Usage

 - Startup: Upon powering up, the RAT displays a startup screen for 2 seconds.
 - Main Menu: Navigate through the options (GO, Adjust Temperature, Adjust Time) using the left and right buttons.
 - Adjust Temperature: Set your target temperature for the retrobright solution.
 - Adjust Time: Set the duration for the UV light exposure.

## Contributing
This project is primarily for personal use, but if you have suggestions or improvements, feel free to open an issue or submit a pull request.

## License
Feel free to do whatever you want with this :)
