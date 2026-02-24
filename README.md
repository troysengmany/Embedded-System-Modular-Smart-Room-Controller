# Embedded-System-Modular-Smart-Room-Controller
Project Status 
- In active development. This project is being build modulary, with full documentation of desgn descisions and testing.

Objective
- Motion detection (PIR Sensor)
- Ambiant light sensing (Photoresistor voltage divider)
- Occupancy state managment 
- Event driven buzzer alerts
- Smart ligting control logic
- Temperature sensing and fan control

System Atchitecture 

Inputs
- PIR Motion Sensor (Digital)
- Photoresistor (Analog)

Processing
- Motion detection trigger
- Occupancy hold-timer logic using millis()
- Threshhold-based light classiifcation
- Lockout filtering to prevent repeated buzzer triggers

Outputs
- LED
- Passive buzzer alerts

Core Embedded Concepts Demonstrated
- Digital vs Analog signal handling
- Voltage divider sensor design
- Event detection using previous state comparison
- Non-blocking timing with millis()
- State retention with boolean flags
- Basic embedded state management

Development Log

Phase 1 - Motion Detection 
- Validated PIR digital HIGH/LOW output
- Added lockout timer to prevent repeated triggers
- Investigated sebsir retrigger behavior

Phase 2 - Light Sensor Calibration 
- Designed voltage divider with breadboard
- Measured analog ranges under bright/dark conditions
- Implemented adjustable threshold detection 
