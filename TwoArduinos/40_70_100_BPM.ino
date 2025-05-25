#include <Servo.h>

// Motor Pins
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;

// Servo Pins
Servo mitralValve;
Servo aorticValve;
const int mitralOpenAngle = 10;
const int mitralClosedAngle = 25;
const int aorticOpenAngle = 10;
const int aorticClosedAngle = 25;

// BPM & Timing Setup
int BPM = 70;
unsigned long cycleLength = 857;  // in ms, default for 70 BPM
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
  // Get user input once
  if (Serial.available() > 0) {
    int choice = Serial.parseInt();
    if (choice == 1) BPM = 40;
    else if (choice == 2) BPM = 70;
    else if (choice == 3) BPM = 100;
    else BPM = 70; // Default fallback

    // Update cycle timing
    cycleLength = 60000UL / BPM;  // 60,000 ms per minute ÷ BPM = one cycle length
    stepIntervalMicros = (cycleLength * 1000UL) / motorStepsPerCycle;

    Serial.print("Selected BPM: ");
    Serial.println(BPM);
    delay(1000); // Let user see result
    cycleStartTime = millis();  // Start the first cycle
    lastMotorStepMicros = micros();
    motorStepCount = 0;
  }

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

  // Calculate valve times based on % of cycle length
  unsigned long mitralOpenTime = 0;
  unsigned long mitralCloseTime = cycleLength * 0.65;  // closes after 65%
  unsigned long aorticOpenTime = cycleLength * 0.35;   // opens at 35%
  unsigned long aorticCloseTime = cycleLength * 0.70;  // closes at 70%

  // Valve logic
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
