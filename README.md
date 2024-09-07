# Field Monitoring System

This project aims at making field maintenance easier for farmers. 
This field monitoring system (FMS) consists of the following components :
1. ESP32 Microcontroller board 
2. ESP8266 NodeMCU microcontroller board
3. DHT22 Temperature and Humidity Sensor
4. Resistive/Capacitive Soil Moiosture Sensor
5. 9V Water Pump
6. 5V Relay (To switch on and switch off the 9V pump)
7. Jumper Cables
8. SIM800L GSM Module

## Problem Statement
Farmers often face challenges in monitoring their fields consistently due to the physical distance between them and their crops. This lack of continuous supervision can lead to undetected issues such as water stress, pest attacks, and poor soil conditions, ultimately affecting crop health and yield. There is a need for a solution that enables farmers to remotely monitor and manage field conditions, ensuring timely intervention and better resource management without being physically present on-site.

## Aim of this project 
The project aims to develop a remote monitoring system that allows farmers to track critical field parameters, such as soil moisture, temperature, and environmental factors, through real-time data collection and analysis. This system will provide timely alerts and insights, helping farmers take necessary actions even when they are away from their fields.

### Project Overview

This project is designed to enable farmers to remotely monitor field conditions, providing real-time data on soil moisture and temperature. The system consists of two primary components:

1. **Transmitter (ESP8266 NodeMCU)**: The NodeMCU is responsible for collecting real-time data from the connected soil moisture and temperature sensors. It acts as the transmitter in this system, gathering sensor data and sending it wirelessly to the receiver using the [ESP-NOW](#esp-now) protocol.

2. **Receiver (ESP32)**: The ESP32 serves as the receiver, which communicates with the transmitter via ESP-NOW. It is connected to a SIM800L GSM module that enables the system to send the collected data as an SMS to the farmer's mobile phone every 100 seconds (configurable based on user requirements). This allows the farmer to monitor field conditions even when not physically present.

This solution ensures that farmers receive regular updates on critical field parameters, helping them make timely decisions and improve resource management.


## ESP-NOW 
Stating the Espressif website, ESP-NOW is a *“protocol developed by Espressif, which enables multiple devices to communicate with one another without using Wi-Fi. The protocol is similar to the low-power 2.4GHz wireless connectivity (…) . The pairing between devices is needed prior to their communication. After the pairing is done, the connection is safe and peer-to-peer, with no handshake being required.”*

ESP-NOW supports the following features:

1. Encrypted and unencrypted unicast communication;
2. Mixed encrypted and unencrypted peer devices;
3. Up to 250-byte payload can be carried;
4. Sending callback function that can be set to inform the application layer of transmission success or failure.

ESP-NOW is very versatile and you can have one-way or two-way communication in different setups.

## Softwares Used 
The firmware for both the ESP8266 NodeMCU (transmitter) and ESP32 (receiver) has been developed using the PlatformIO IDE, a professional open-source toolchain for embedded development. PlatformIO provides robust features such as cross-platform support, integrated debugging, and advanced library management, making it an ideal choice for efficiently writing, compiling, and deploying code to both microcontrollers. This environment ensures streamlined development and seamless code maintenance for the project.

The PlatformIO IDE has it's own wrapper for ESP-NOW protocol called ESPNowW. 
For more details ake a look at these blogs :
1. [ESPNowW Part-1](https://medium.com/@forgamesonly684/espnoww-the-esp-now-wrapper-library-for-platformio-part-1-downloading-and-installing-the-02df58b241e9)
2. [ESPNowW Part-2](https://medium.com/@forgamesonly684/espnoww-the-esp-now-wrapper-library-for-platformio-part-2-coding-the-esp-boards-using-6ccae4ee77cc)

These blogs also touch on the basics of using PlatformIO IDE. So for new users , these blogs will be helpful. 

