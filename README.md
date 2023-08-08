
# Sensor Data Interaction and Simulation

This project demonstrates an interactive simulation platform for embedded software systems, allowing the retrieval and manipulation of sensor data from a separate application. The project comprises two main components: a Sensors Application and a Memory Read/Write/Edit Application e.g our control panel application.

# Sensors Application

The Sensors Application emulates the behavior of various sensors, including temperature and humidity sensors. It provides a foundation for modeling sensor data collection and processing. The application is built in C++ and offers an extensible class hierarchy to represent different types of sensors. Features include:

    Abstract Sensor Class: A base class with common sensor attributes and methods.
    TemperatureSensor and HumiditySensor: Derived classes for specific sensor types, each with its own data collection method.
    Memory Address Utilities: Functions to retrieve memory addresses of member functions and the application's base address.

# Embedded Software Control Panel 

The Embedded Software Control Panel showcases how to interact with a running device(in this case an exe file that distributes sensors data). It uses memory read/write/edit operations with the help of Windows API to read sensor data directly from memory. Key aspects include:

    Process Identification: Obtaining the process ID of the Sensors Application by name.
    MemoryEditor Class: A template class handling memory read, write, and manipulation operations.
    Temperature and Humidity Values: Calculating memory offsets and reading temperature and humidity values from the Sensors Application.
    Console Output: Displaying the retrieved sensor values in the console.

# Usage

    Run the Sensors Application (e.g., sensors.exe).
    Execute the Embedded Software Control Panel to observe the retrieval and display of sensor data.

# Purpose

This project serves as an educational resource for understanding interaction between embedded software applications, as well as simulating sensor behavior within a controlled environment. 
