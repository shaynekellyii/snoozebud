int motorPin = 11; 
int potentPin = 5;

void setup() {
  pinMode(potentPin, INPUT);
  pinMode(motorPin, OUTPUT); // Set pin for output to control TIP120 Base pin
  //analogWrite(motorPin, 255); // By changing values from 0 to 255 you can control motor speed
}

// Read potentiometer value directly to motor
void loop() {
  analogWrite(motorPin, 0);
  delay(1000);
  analogWrite(motorPin, 255);
  delay(5000);
  //analogWrite(motorPin, analogRead(potent)/4);
}
