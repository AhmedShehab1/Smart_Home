
# Smart Home Embedded Project

## Overview
This project is aimed at creating a smart home system using Atmega32 microcontroller. The system is designed to allow users to control various aspects of their home such as lights, security, and appliances through a smartphone application via Bluetooth communication. It incorporates features like user authentication, timer-based functions, and a security buzzer. Additionally, the system integrates servo motors, DC motors, LDR (Light Dependent Resistor) sensors, LM35 temperature sensors, and automatic light control using fast PWM.

## Team Members
- Ahmed Abdelghafer

## Features
- **User Authentication:** The system supports up to 10 different users with unique usernames and passwords. 
- **Bluetooth Control:** Utilizes UART communication protocol with HC-05 Bluetooth module to enable smartphone control.
- **Timer Functions:** Utilizes Timer 0, 1, and 2 for various timed operations within the system. Fast PWM mode is utilized for advanced functionalities.
- **Security Measures:** Includes a security buzzer that activates if the user enters the wrong password three times.
- **Servo Motor Integration:** Incorporates servo motors for controlling rotational motion in specific applications.
- **DC Motor Control:** Enables the control of DC motors for various purposes such as opening/closing doors or windows.
- **Sensor Integration:** Utilizes LDR sensors for automatic light control and LM35 temperature sensors for temperature monitoring.
- **Automatic Light Control:** Implements an automatic lighting system based on LDR sensor readings and fast PWM for adjusting light intensity.
- **Temperature-based Actions:** The system reacts differently based on temperature readings:
    - Below 20°C: Dc Motor **OFF**
    - Between 20°C and 25°C: Dc Motor At **Medium Speed**
    - Above 25°C: Dc Motor At **High Speed**

## Contributing
We welcome contributions from the community. If you have any ideas for improvement or would like to report an issue, please feel free to open an issue or submit a pull request.
