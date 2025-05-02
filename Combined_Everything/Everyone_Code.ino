
/*
  Project: Pressure, Flow, Motor, and Valve Control
  Board: SparkFun Qwiic RedBoard
  Devices:
    - 3x SparkFun MicroPressure Sensors (via Qwiic Mux)
    - YF-S201 Flow Sensor
    - NEMA23 Motor with Microstep Driver
    - 2x Servos (Mitral and Aortic Valve Simulation)
*/

#include <Wire.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>
#include <SparkFun_MicroPressure.h>
#include <Servo.h>

// Constants
const float PSI_TO_MMHG = 51.7149; // 1 psi = 51.7149 mmHg

// Mux and Pressure Sensor setup
QWIICMUX myMux;
const uint8_t muxAddress = 0x70;
const int sensorChannels[3] = {0, 2, 3};
SparkFun_MicroPressure pressureSensor;

// Flow sensor setup
const int flowPin = 3;
volatile int flowPulseCount = 0;
float calibrationFactor = 7.5; 
unsigned long lastFlowCheck = 0;
const unsigned long flowInterval = 500;
float flowRate_mL_per_sec = 0;

// Stepper motor setup
const int stepPin = 5;
const int dirPin = 2;
const int enPin = 8;

// Stepper motor control variables defined
unsigned long lastMotorStepMicros = 0;
const int motorStepDelayMicros = 1071;
int motorStepCount = 0;
const int motorStepsPerCycle = 400;
bool motorRunning = true;

// Servo setup
Servo mitralValve;
Servo aorticValve;
const int mitralOpenAngle = 10;
const int mitralClosedAngle = 25;
const int aorticOpenAngle = 10;
const int aorticClosedAngle = 25;

// Valve timing
const unsigned long cycleLength = 857;
const unsigned long mitralCloseTime = 492;
const unsigned long aorticOpenTime = 551;
const unsigned long aorticCloseTime = 807;
const unsigned long mitralOpenTime = 857;
unsigned long cycleStartTime = 0;

// Interrupt Service Routine for flow sensor
void flowISR() {
  flowPulseCount++;
}

// Read pressure sensor on a mux channel
float readPressureSensor(int channel) {
  myMux.setPort(channel);
  
  if (!pressureSensor.begin()) {
    Serial.print("Sensor on channel ");
    Serial.print(channel);
    Serial.println(" not detected.");
    return -1.0;
  }

  float pressure_psi = pressureSensor.readPressure();
  return pressure_psi * PSI_TO_MMHG;
}

// Move stepper motor forward
void handleMotor() {
  if (!motorRunning) return;

  unsigned long nowMicros = micros();
  if (motorStepCount < motorStepsPerCycle) {
    if (nowMicros - lastMotorStepMicros >= motorStepDelayMicros * 2) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(1); // very short pulse
      digitalWrite(stepPin, LOW);
      lastMotorStepMicros = nowMicros;
      motorStepCount++;
      if (motorStepCount == motorStepsPerCycle) {
        motorStepCount = 0;
      } 
    }
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize Mux
  if (!myMux.begin(muxAddress)) {
    Serial.println("Mux not detected!");
    while (1);
  }

  // Setup flow sensor
  pinMode(flowPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(flowPin), flowISR, RISING);

  // Setup motor pins
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  // Setup servos
  mitralValve.attach(9);
  aorticValve.attach(10);
  mitralValve.write(mitralOpenAngle);
  aorticValve.write(aorticClosedAngle);

  cycleStartTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long cycleTime = (currentMillis - cycleStartTime) % cycleLength;

  // --- Flow Sensor ---
  if (currentMillis - lastFlowCheck >= flowInterval) {
    noInterrupts();
    int count = flowPulseCount;
    flowPulseCount = 0;
    interrupts();

    float flowRate_L_per_min = count / calibrationFactor;
    flowRate_mL_per_sec = (flowRate_L_per_min * 1000) / 60.0;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate_mL_per_sec);
    Serial.println(" mL/sec");

    lastFlowCheck = currentMillis;
  }

  // --- Motor ---
  handleMotor();

  // --- Valve (Servo) Control ---
  // Mitral Valve
  if (cycleTime < mitralCloseTime) {
    mitralValve.write(mitralOpenAngle);
      // --- Pressure Sensors ---
    for (int i = 0; i < 3; i++) {
    float pressure = readPressureSensor(sensorChannels[i]);
    Serial.print("Pressure Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pressure);
    Serial.println(" mmHg");
  }
  } else if (cycleTime < aorticOpenTime) {
    mitralValve.write(mitralClosedAngle);
  } else if (cycleTime >= mitralOpenTime) {
    mitralValve.write(mitralOpenAngle);
  }

  // Aortic Valve
  if (cycleTime < aorticOpenTime) {
    aorticValve.write(aorticClosedAngle);
  } else if (cycleTime < aorticCloseTime) {
    aorticValve.write(aorticOpenAngle);
  } else {
    aorticValve.write(aorticClosedAngle);
  }

  // Restart cycle if full cycle completed
  if (currentMillis - cycleStartTime >= cycleLength) {
    cycleStartTime = currentMillis;
  }
}
