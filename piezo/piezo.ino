int sensoroutput = 3; // the analog pin connected to the sensor
int ledoutput = 0; // pin connected to LED
int PIEZO_THRESHOLD = 30;
int DELAY_MS = 10000;

void setup() {
  // Setup LED I/O pin
  pinMode(ledoutput, OUTPUT);
}

// Loop to read piezo vibration sensor
void loop() {
  if (movementDetected()) {
    digitalWrite(ledoutput, LOW);
  } else {
    // Countdown for the specified delay (10s) while waiting for movement
    unsigned long countdownInit = millis();
    while ((millis() - countdownInit()) < DELAY_MS) {
      if (movementDetected()) {
        // Break out of countdown/loop and turn off LED
        digitalWrite(ledoutput, LOW);
        return;
      }
    }
    // Turn on LED if no movement detected after 10s 
    digitalWrite(ledoutput, HIGH);
  } 
}

// Checks piezo analog input voltage reading for movement
boolean movementDetected() {
  return (analogRead(sensoroutput) >= PIEZO_THRESHOLD);
}

