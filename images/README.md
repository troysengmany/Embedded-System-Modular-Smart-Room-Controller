## Motion Sensor Validation

### Test Condition
Objective: Verify PIR digital output transitions when motion is introduced.

### Baseline (No Motion Detected)

![Before Motion]

In the idle state, the PIR output remains LOW. The system does not trigger buzzer or occupancy state changes.

### After Motion Introduced

![After Motion]

Upon introducing motion within sensor range, the PIR output transitions to HIGH.  
Edge detection logic captures the LOW→HIGH transition and triggers a single buzzer event while updating occupancy state.
