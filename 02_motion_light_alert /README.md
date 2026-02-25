# Module 02 - Motion + Light Smart Alert

## Objective
Integrate PIR motion detection with ambient light sensing to create context-aware behavior:
- Motion triggers a buzzer alert
- LED turns on only when the room is dark AND motion/occupancy is detected

---

## Hardware
- Arduino Mega
- HC-SR501 PIR motion sensor (digital)
- Photoresistor + resistor (voltage divider -> A0)
- LED + resistor (output)
- Buzzer (output)

---

## Inputs / Outputs

### Inputs
- PIR (digital): HIGH when motion is detected
- Photoresistor (analog): `analogRead(A0)` returns 0-1023

### Outputs
- Buzzer: beeps on motion events
- LED: ON only if `(dark && occupied)`

---

## System Behavior
1. If PIR detects motion:
   - `occupied = true`
   - buzzer triggers (filtered to avoid rapid re-triggers)

2. If `(occupied == true)` AND `(dark == true)`:
   - LED turns ON

3. If no motion occurs for `holdTime`:
   - `occupied = false`
   - LED turns OFF

---

## Calibration Notes
Light readings depend on your room and wiring, so the threshold is tuned experimentally.
Record your observed values here:

- Bright room value: ____
- Dark / covered value: ____
- Threshold used: ____

---

## Video Demo

## Demo Videos

Bright Room – Motion Trigger (Buzzer Only):
[Watch Demo] [](https://youtu.be/4qPXHNmCPmI)

Dark Room – Motion Trigger (Buzzer + LED):
[Watch Demo] [](https://youtu.be/V-1aLgu4Uw4)

---

## What This Module Demonstrates
- Digital + analog sensor integration
- ADC sampling and threshold classification
- Non-blocking timing with `millis()`
- Occupancy state memory (hold timer)
- Edge-triggered / filtered alerts (reduces false double-triggers)
- Context-aware output logic
