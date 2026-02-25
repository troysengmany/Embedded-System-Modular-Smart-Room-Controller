// ============================================================
// SMART LIGHT + MOTION BEEP (Arduino Mega)
// - Motion sensor (PIR) detects movement
// - Photoresistor (light sensor) detects brightness
// - LED turns ON only when: (occupied AND dark)
// - Buzzer beeps ONCE per motion trigger (regardless of light)
// ============================================================


// ------------------------ WORD DEFINITIONS ------------------------
// PIN: a numbered input/output connection on the Arduino
// INPUT: a pin reads signals (HIGH/LOW)
// OUTPUT: a pin sends signals (HIGH/LOW)
// HIGH: 1 (about 5V). LOW: 0 (0V)
//
// analogRead(A0): reads a value from 0 to 1023 (brightness voltage)
// digitalRead(D2): reads either HIGH (1) or LOW (0)
//
// millis(): a clock that counts milliseconds since Arduino turned on
//
// occupied: our "memory" of whether someone is in the room recently
// holdTime: how long we keep occupied=true after last motion
//
// threshold: the cutoff number between bright vs dark
// dark: true/false based on comparing lightVal to threshold
//
// edge detection: detecting a change from LOW -> HIGH (one event)
// lockout: ignoring extra triggers for a short time to prevent double beeps
// -----------------------------------------------------------------


// ------------------------ PIN DEFINITIONS -------------------------
const int PIR = 2;        // PIR motion sensor signal wire goes to D2
const int LIGHT = A0;     // Light sensor middle node goes to A0
const int LED = 7;        // LED output pin goes to D7
const int BUZZ = 8;       // Buzzer output pin goes to D8 (you requested 8)
// -----------------------------------------------------------------


// -------------------- LIGHT THRESHOLD SETTING ---------------------
// threshold decides what "dark" means.
// You will tune this after you read real lightVal numbers.
int threshold = 500;

// This function decides if it's dark.
// IMPORTANT: If your sensor behaves opposite, flip > to <.
bool isDark(int lightVal) {
  // dark is TRUE when the number is bigger than threshold
  return (lightVal < threshold);
}
// -----------------------------------------------------------------


// ------------------- OCCUPANCY (MEMORY) SETTINGS ------------------
// occupied = our memory state: true means "someone was here recently"
bool occupied = false;

// lastMotionTime remembers the time when motion last happened
unsigned long lastMotionTime = 0;

// holdTime = how long we keep occupied=true after motion stops
const unsigned long holdTime = 5000;   // 10 seconds
// -----------------------------------------------------------------


// ------------------ BUZZER "ONE BEEP PER MOTION" ------------------
// prevMotion stores the last PIR reading so we can detect LOW->HIGH.
int prevMotion = LOW;

// lockUntil blocks extra beeps for a short time (filters double triggers)
unsigned long lockUntil = 0;
const unsigned long lockMs = 1500;      // 1.5 seconds lockout
// -----------------------------------------------------------------


// ---------------------- SERIAL PRINT CONTROL ----------------------
// Stops the Serial Monitor from spamming too fast.
unsigned long lastPrint = 0;
const unsigned long printInterval = 300; // print every 300ms
// -----------------------------------------------------------------


void setup() {

  // PIR is input because we are reading a signal from it
  pinMode(PIR, INPUT);

  // LED and buzzer are outputs because Arduino controls them
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  // Start serial monitor messages
  Serial.begin(9600);
}


void loop() {

  // now = current time in milliseconds since the board powered on
  unsigned long now = millis();


  // ------------------ 1) READ SENSOR VALUES ------------------

  // motion is HIGH when PIR detects motion, LOW when it does not
  int motion = digitalRead(PIR);

  // lightVal is a number 0..1023 based on brightness
  int lightVal = analogRead(LIGHT);

  // dark becomes true or false based on threshold comparison
  bool dark = isDark(lightVal);


  // ------------------ 2) UPDATE OCCUPANCY MEMORY ------------------
  // If PIR detects motion, we mark occupied and refresh the timer.

  if (motion == HIGH) {
    occupied = true;          // someone is here
    lastMotionTime = now;     // remember the time of last motion
  }

  // If occupied AND time since last motion is too long -> set empty
  if (occupied && (now - lastMotionTime >= holdTime)) {
    occupied = false;         // no one here anymore
  }


  // ------------------ 3) BUZZER: BEEP ON MOTION EVENT ------------------
  // We want ONE beep per motion trigger, not repeated beeps.
  // So we beep only when the PIR changes from LOW -> HIGH.
  // lockout prevents a second beep caused by the PIR pulsing again.

  if (now >= lockUntil) {  // only allow beep if lockout is over

    // LOW -> HIGH transition = new motion event
    if (motion == HIGH && prevMotion == LOW) {

      // Beep (tone works for passive buzzers)
      tone(BUZZ, 1000);   // 1000 Hz frequency
      delay(60);          // short beep length
      noTone(BUZZ);

      // Start lockout so it won't beep again immediately
      lockUntil = now + lockMs;
    }
  }

  // Save current motion to compare next loop
  prevMotion = motion;


  // ------------------ 4) SMART LIGHT RULE ------------------
  // LED turns ON only if:
  // - it's dark
  // - AND someone is occupied (recent motion)

  if (dark && occupied) {
    digitalWrite(LED, HIGH);  // ON
  } else {
    digitalWrite(LED, LOW);   // OFF
  }


  // ------------------ 5) DEBUG PRINT (NO SPAM) ------------------
  // Print only every printInterval milliseconds.

  if (now - lastPrint >= printInterval) {
    lastPrint = now;

    Serial.print("motion=");
    Serial.print(motion);

    Serial.print(" occ=");
    Serial.print(occupied ? 1 : 0);

    Serial.print(" lightVal=");
    Serial.print(lightVal);

    Serial.print(" dark=");
    Serial.print(dark ? 1 : 0);

    Serial.print(" LED=");
    Serial.println(digitalRead(LED));
  }
}
