## Motion Module – Occupancy State Detection

Objective: Validate system-level occupancy logic driven by PIR sensor input.

### Idle State (No Motion)

![Idle State]

- PIR digital input: LOW
- Occupancy state: NO
- System status: Unoccupied

When no motion is detected, the system maintains an "Unoccupied" state.

---

### Motion Detected

![Motion Detected]

- PIR digital input: HIGH
- Occupancy state: YES
- System status: Occupied

When motion is detected, the system updates the occupancy state variable and transitions to "Occupied."
