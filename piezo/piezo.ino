int sensoroutput = 3; // the analog pin connected to the sensor
int ledoutput = 0; // pin connected to LED
int buzzeroutput = 2; // pin connected to buzzer
int PIEZO_THRESHOLD = 30;
int DELAY_MS = 10000;
int ledCount = 0;

void setup() {
  // Setup I/O pins
  pinMode(ledoutput, OUTPUT);
  pinMode(buzzeroutput, OUTPUT);
}

// Loop to read piezo vibration sensor
void loop() {
  digitalWrite(buzzeroutput, LOW);
  if (movementDetected()) {
    digitalWrite(ledoutput, LOW);
  } else {
    // Countdown for the specified delay (10s) while waiting for movement
    unsigned long countdownInit = millis();
    while ((millis() - countdownInit) < DELAY_MS) {
      if (movementDetected()) {
        // Break out of countdown/loop and turn off LED
        digitalWrite(ledoutput, LOW);
        return;
      }
    }
    // Turn on LED if no movement detected after 10s 
    digitalWrite(ledoutput, HIGH);
    ledCount++;
    turnOnBuzzerIfNeeded();
  } 
}

// Checks piezo analog input voltage reading for movement
boolean movementDetected() {
  return (analogRead(sensoroutput) >= PIEZO_THRESHOLD);
}

// Buzzer will turn on after LED turns on twice
void turnOnBuzzerIfNeeded() {
  if (ledCount >= 2) {
    digitalWrite(buzzeroutput, HIGH);
    unsigned long countdownInit = millis();
    while ((millis() - countdownInit) < 3000) {
      if (movementDetected()) {
        digitalWrite(buzzeroutput, LOW);
        ledCount = 0;
        return;
      }
    }
    digitalWrite(buzzeroutput, LOW);
    ledCount = 0;
    return;
  }
}

