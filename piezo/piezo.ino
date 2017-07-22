/**
 * I/O pin definitions
 */
int btOutPin = 1;
int buzzerOutPin = 2;
int sensorOutPin = 3;
int motorOutPin = 11;

/**
 * Constants
 */
int PIEZO_THRESHOLD = 255;
int DELAY_MS = 10000;
int VIBRATE_MS = 3000;
int vibrated = 0;

void setup() {
  /* Setup I/O pins */
  pinMode(sensorOutPin, OUTPUT);
  pinMode(motorOutPin, OUTPUT);
  pinMode(buzzerOutPin, OUTPUT);
  pinMode(btOutPin, OUTPUT);

  /** 
   *  Setup bluetooth connection with HC-06.
   *  NOTE: Pulling up the key pin forces the baud rate to 38400.
   *  TODO: Change name of HC-06 module to SnoozeBud. 
   *        Change passcode (default 1234).
   */
  Serial.begin(38400);
  Serial.flush();
}

/**
 * Continuously check the piezo-electric sensor for movement.
 * Vibrate/alarm happens after a 10 second lapse in breathing.
 * Alarm occurs after 2 vibrations are issued.
 */
void loop() {
  /* If no movement detected, countdown for the specified delay (10s) waiting for movement */
  if (!movementDetected()) {
    unsigned long countdownInit = millis();
    while ((millis() - countdownInit) < DELAY_MS) {
      if (movementDetected()) {
        /* Movement detected, break out of the countdown loop and restart checking */
        return;
      }
    }

    /* No movement detected in 10s, send alert (vibration or alarm) */
    if (vibrated < 2) { /* Vibrate twice before sending alarm */
      /* Vibrate for 3s, but stop immediately if movement detected */
      analogWrite(motorPin, 255);
      unsigned long countdown = millis();
      while ((millis() - countdown) < VIBRATE_MS) {
        if (movementDetected()) {
          /* Break out of countdown loop to resume movement checking, turn off motor */
          analogWrite(motorPin, 0);
          return;
        }
      }
      /* No movement detected during vibration, turn off motor and increment vibration counter */
      analogWrite(motorPin, 0);
      vibrated++;
    } else {
      /* Already 2 vibrations sent, send Bluetooth alarm command to phone */
      sendAlarmCommand();
      vibrated = 0;
    }
  }
}

/* Checks piezo analog input voltage reading for movement */
boolean movementDetected() {
  return (analogRead(sensoroutput) >= PIEZO_THRESHOLD);
}

/* Send alarm command via Bluetooth to the paired phone */
void sendAlarmCommand() {
    Serial.println("ALARM:ON");
}

