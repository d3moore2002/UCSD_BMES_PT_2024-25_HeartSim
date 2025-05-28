#include <Servo.h>

// Motor Pins
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;

// Servo Pins
Servo mitralValve;
Servo aorticValve;
const int mitralOpenAngle = 10;
const int mitralClosedAngle = 45;
const int aorticOpenAngle = 10;
const int aorticClosedAngle = 45;

// BPM & Timing Setup
int BPM = 0;
unsigned long cycleLength = 0;  // in ms, default for 70 BPM
int motorStepsPerCycle = 400;
unsigned long stepIntervalMicros;

unsigned long cycleStartTime = 0;
unsigned long lastMotorStepMicros = 0;
int motorStepCount = 0;

void setup() {
  Serial.begin(9600);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);
  digitalWrite(dirPin, HIGH);

  mitralValve.attach(9);
  aorticValve.attach(10);

  mitralValve.write(mitralOpenAngle);
  aorticValve.write(aorticClosedAngle);

  Serial.println("Select a BPM to simulate:");
  Serial.println("1. 40 BPM");
  Serial.println("2. 70 BPM");
  Serial.println("3. 100 BPM");
}

void loop() {
  // Only process new input when available
  if (Serial.available() > 0) {
    int menuChoice = Serial.parseInt();
    switch (menuChoice) {
      case 1:
        BPM = 40;
        break;
      case 2:
        BPM = 70;
        break;
      case 3:
        BPM = 100;
        break;
    }

    cycleLength = 60000UL / BPM;
    stepIntervalMicros = (cycleLength * 1000UL) / motorStepsPerCycle;

    Serial.print("Selected BPM: ");
    Serial.println(BPM);

    cycleStartTime = millis();  // restart timing
    lastMotorStepMicros = micros();
    motorStepCount = 0;

    delay(1000);  // let user read serial message
  }

  // Run servo/motor logic every loop
  unsigned long currentMillis = millis();
  unsigned long cycleTime = (currentMillis - cycleStartTime) % cycleLength;
  unsigned long nowMicros = micros();

  // Stepper motor control
  if (motorStepCount < motorStepsPerCycle && (nowMicros - lastMotorStepMicros >= stepIntervalMicros)) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(stepPin, LOW);
    lastMotorStepMicros = nowMicros;
    motorStepCount++;
  }

  // Valve timing logic
  unsigned long mitralCloseTime = cycleLength * 0.65;
  unsigned long aorticOpenTime = cycleLength * 0.35;
  unsigned long aorticCloseTime = cycleLength * 0.70;

  // Valve control
  if (cycleTime < mitralCloseTime) {
    mitralValve.write(mitralOpenAngle);
  } else {
    mitralValve.write(mitralClosedAngle);
  }

  if (cycleTime >= aorticOpenTime && cycleTime < aorticCloseTime) {
    aorticValve.write(aorticOpenAngle);
  } else {
    aorticValve.write(aorticClosedAngle);
  }

  // Restart cycle
  if (currentMillis - cycleStartTime >= cycleLength) {
    cycleStartTime = currentMillis;
    motorStepCount = 0;
  }
}
