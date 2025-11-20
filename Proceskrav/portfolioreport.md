# Work Portfolio – IoT Project assignment, Smiley feedback panel 

# Project Overview 

The goal of this project is to create an IoT-enabled button system that triggers LED lights and publishes messages over MQTT when buttons are pressed. The project uses an ESP32 microcontroller, WiFi connectivity, NTP for time synchronization, and MQTT for communication.

## Key Features:

- Four buttons (Red, Blue, Green, Yellow)
- Corresponding LED activation
- MQTT Json message publication, over TSL, with button name and timestamp
- WiFi and NTP time synchronization
- Deep sleep mode for power saving and wakeup on buttonclick.

## 1. Ideas & Initial Concept 

**Objective:** Make a system that logs button presses to a remote MQTT broker and visually indicates activity using LEDs.

**Considerations:**

- Power efficiency → implement deep sleep
- Reliability → reconnect WiFi and MQTT if disconnected
- Timestamp accuracy → use NTP to set local time

**Sketch / diagram idea:**
- SmileyOpgave.jpg

## 2. System Design 

**Hardware Setup:** 
- ESP32 board (Bread board)
- 4 LEDs (Red, Blue, Green, Yellow)
- 4 Buttons

**Connections:**
- Buttons wired to digital pins with pull-up resistors
- LEDs connected to digital pins

**Software Modules:**
- Buttons – Handle button press events
- LED Control – Turn on LEDs for a fixed duration(7 second)
- MQTT Communication – Publish messages with timestamp
- Time Setup – NTP synchronization
- WiFi Connection – Connect and reconnect as needed
- Power Management – Deep sleep after inactivity
- Json message Generator

## 3. Implementation##
**3.1 Liberaries**
- Used OneButton library for simple button press handling
- Used ArduinoJson for JSon
- Used PubSubClien for MQTT client

**3.2 Buttons & LED Handling**
- ledOn() function turns on the corresponding LED and records the timestamp
- loop() monitors LED timers to turn off LEDs after LED_ON_TIME

**3.3 MQTT Publishing**
Created CreateJson() to generate a JSON payload:

{
  "Button": "Red",
  "Time": "2025-11-20 12:00:00"
}

- Published via mqtt_publish() over TLS
- Automatic reconnect handled in mqtt_loop()

**3.4 Time & WiFi**
- SetupTime() uses NTP to synchronize
- TrySetupWifi() ensures connection
- Setup-wifi, Time and MQTT in that order

**3.4 Power Management**

- setupDeepSleep() configures wakeup pins
- checkIdleAndSleep() puts ESP32 into deep sleep after sleepIdleTime seconds of inactivity

## 4. Testing & Results

- Verified each button triggers the correct LED
- Confirmed MQTT payload is correctly formatted and published
- Tested idle sleep and wakeup functionality
- WiFi reconnection tested by turning off and on router

**Visual ideas:**
- Serial monitor log showing MQTT messages
- LEDs lighting up on button press

## 5. Reflections & Future Work
- What we learned: Handling asynchronous events in microcontrollers, integrating NTP, WiFi, MQTT, and deep sleep effectively
-

## 6. Tools
To complete this project we have used:
- Example sketches from Arduino IDE for a basic understanding of the concepts.
- ChatGPT to ask for explanations of how specific things work.
- ChatGPT, to search for bugs.
- Copilot to generate repeated lines of code and implement methods we've written.
- Copilot to generate comments.
- Draw.io for drawing the Diagram.