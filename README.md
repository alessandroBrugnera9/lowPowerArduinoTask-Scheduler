# Ultra Low Power Arduino Task Scheduler

This repository demonstrates ultra power-efficient techniques for executing cyclic tasks on an Arduino Uno, inspired by considerations from [Nick Gammon](http://www.gammon.com.au/power). The goal is to leverage deep sleep modes to minimize power consumption while maintaining the ability to perform scheduled tasks.

## Overview

The core idea is to put the Arduino into **deep sleep** for controlled periods. The system uses defined sleep cycles to keep track of time and execute tasks after a certain number of cycles, before returning to sleep. This approach is ideal for applications where periodicity is not critical, as timing can deviate slightly due to Arduino tasks and oscillator variability. For applications requiring precise timing, a **Real-Time Clock (RTC)** module can be integrated.

### Example Use Case

The primary example in this repository illustrates a daily task of watering a garden using a solenoid valve. The implementation includes:

- **Deep sleep** with maximun sleep cycle time **8 seconds** to optimize power savings.
- A daily task that takes approximately **10 seconds** to execute.

This setup demonstrates how to balance power efficiency with the need to perform tasks periodically.

## Examples
- hidranteAutomatico.cpp
  - Implementation in portuguese for the watering system.
  - Uses relay and solenoid valve.
  - Executes every 48 hours, with 8 seconds sleep cycle.

## Important Notes

- This implementation relies solely on **Arduino libraries**, ensuring ease of use and compatibility.
- Periodicity of tasks is flexible; while tasks will execute after a set number of cycles, variations in sleep duration may affect the exact timing.

## Hardware Requirements

- **Arduino Uno**
- **Extra hardware for your task**

## Getting Started

1. Clone the repository to your local machine.
2. Open the Arduino IDE and load the provided example sketch.
3. Connect the necessary hardware according to the schematic included in the repository.
4. Upload the code to your Arduino Uno.
5. Monitor the system’s performance and adjust the sleep duration or task frequency as needed.

## Future Enhancements

- Consider adding an **RTC module** for precise timing.
- Explore alternative power sources for extended operation.
