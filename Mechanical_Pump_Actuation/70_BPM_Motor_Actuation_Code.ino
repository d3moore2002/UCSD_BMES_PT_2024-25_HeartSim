const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW); // Enable driver
}

void loop() {
  digitalWrite(dirPin, HIGH); // Move forward
  for (int x = 0; x < 800; x++) { // 2 revolutions
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1071); // Half period
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1071); // these delays gives us an estimated 1.08 rps
  }

  delay(1000); // 1 second pause

  digitalWrite(dirPin, LOW); // Reverse direction
  for (int x = 0; x < 800; x++) { // 2 revolutions
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2143);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2143);
  }

  delay(1000); // 1 second pause
}
