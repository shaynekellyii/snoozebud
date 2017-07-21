// HC-06 passcode is 1234

#include <SoftwareSerial.h>
SoftwareSerial BT(8,9); 

int sensoroutput = 3; // the analog pin connected to the sensor
//int ledoutput = 5; // pin connected to LED
int buzzeroutput = 2; // pin connected to buzzer
//int vibePin = 5;
int motorPin = 11;
int PIEZO_THRESHOLD = 255;
int DELAY_MS = 5000;
//int ledCount = 0;
int vibrated = 0;

int btOutPin = 1;

void setup() {
  // Setup I/O pins
  pinMode(sensoroutput, OUTPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(buzzeroutput, OUTPUT);
  pinMode(btOutPin, OUTPUT);

  // set baud rate
  Serial.begin(38400);
  Serial.print("AT");
  delay(200);
  Serial.print("AT+BAUD8");
  delay(200);
  Serial.flush();
  //Serial.begin(115200);
  
//  BT.begin(115200);
//  delay(1000);
//  BT.print("AT+BAUD4");
//  Serial1.begin(9600);
//  BT.print("AT+BAUD4");
//  Serial1.print("BT init");
}

// Loop to read piezo vibration sensor
void loop() {
  char c = 'c';
//  Serial.println("serial Test");
  Serial.println("ALARM");
  delay(1000);
  if (Serial.available()) {
    char a = (Serial.read());
    Serial.println(a);
  }
//  digitalWrite(buzzeroutput, LOW);
//  if (movementDetected()) {
//    analogWrite(motorPin, 0);
//  } else {
//    // Countdown for the specified delay (10s) while waiting for movement
//    unsigned long countdownInit = millis();
//    while ((millis() - countdownInit) < DELAY_MS) {
//      if (movementDetected()) {
//        // Break out of countdown/loop and turn off LED
//        analogWrite(motorPin, 0);
//        return;
//      }
//    }
//
//    // Send vibration
//    if (vibrated < 2) {
//      analogWrite(motorPin, 255);
//      unsigned long countdown = millis();
//      while ((millis() - countdown) < DELAY_MS) {
//        if (movementDetected()) {
//          // Break out of countdown/loop and turn off LED
//          analogWrite(motorPin, 0);
//          digitalWrite(buzzeroutput, LOW);
//          return;
//        }
//      }
//      analogWrite(motorPin, 0);
//      vibrated++;
//    } else {
//      turnOnBuzzerIfNeeded();
//      vibrated = 0;
//    }
//  }
}

// Checks piezo analog input voltage reading for movement
boolean movementDetected() {
  return (analogRead(sensoroutput) >= PIEZO_THRESHOLD);
}

// Buzzer will turn on after LED turns on twice
void turnOnBuzzerIfNeeded() {
    digitalWrite(buzzeroutput, HIGH);
    delay(3000);
//    unsigned long countdownInit = millis();
//    while ((millis() - countdownInit) < 3000) {
//      if (movementDetected()) {
//        digitalWrite(buzzeroutput, LOW);
//        return;
//      }
    digitalWrite(buzzeroutput, LOW);
    return;
//  }
}

