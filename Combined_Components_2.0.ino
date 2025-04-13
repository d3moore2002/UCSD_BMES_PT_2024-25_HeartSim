// Combined code
/*
  Combined Code for SparkFun Qwiic MicroPressure Sensor & YF-S201 Flow Sensor
  - Reads pressure (in kPa) from the MicroPressure sensor (I2C communication)
  - Reads flow rate (in L/min) from the YF-S201 flow sensor (interrupt-based)
  - Displays both values on the Serial Monitor
*/

#include <Servo.h>
#include <Wire.h>                     
#include <SparkFun_MicroPressure.h>     

Servo servo;
int angle = 10;
bool moveServo = true;

SparkFun_MicroPressure mpr;

// ------------------------- Flow Sensor Configuration -------------------------
const int flowPin = 2; 
const int servoPin1 = 9;
const int measureInterval = 1000; 
volatile int pulseCounter = 0; 

const float factorK = 8.767;

// Timers for non-blocking execution
unsigned long lastFlowCheck = 0;
unsigned long lastPressureCheck = 0;
unsigned long lastServoUpdate = 0;
unsigned long servoDelay = 10; 
int servoStep = 1; 

bool increasing = true; // Direction of servo movement

void ISRCountPulse() {
  pulseCounter++;
  Serial.println("Pulse is being detected");
}

// below is a difference approach to GetFrequency.. maybe there is a logic problem below
// float GetFrequency(){
//   pulseCounter = 0;
//   interrupts();
//   delay(measureInterval);
//   noInterrupts();
//   return(float)pulseCounter * 1000/ measureInterval;
// }
    

float GetFrequency() {
  static unsigned long lastFlowTime = 0;
  static int lastPulseCount = 0;
  
  unsigned long now = millis();
  if (now - lastFlowTime >= measureInterval) {
    noInterrupts();
    int pulseCount = pulseCounter;
    pulseCounter = 0;
    interrupts();

    lastFlowTime = now;
    lastPulseCount = pulseCount;
  }

  return (float)lastPulseCount * 1000 / measureInterval;
}

void setup() {
  Serial.begin(115200);
  Wire.begin();         

  servo.attach(servoPin1);
  servo.write(angle);

  if (!mpr.begin()) { 
    Serial.println("Cannot connect to MicroPressure sensor. Check wiring.");
    while (1);
  }

  pinMode(flowPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowPin), ISRCountPulse, RISING);
}

void loop() {
  unsigned long currentMillis = millis();

  // ------------------------- Pressure Sensor Reading -------------------------
  if (currentMillis - lastPressureCheck >= 500) { // Read every 500ms
    lastPressureCheck = currentMillis;

    float pressure_kPa = mpr.readPressure(KPA);
    if (pressure_kPa < -1000 || pressure_kPa > 1000) { 
      Serial.println("Pressure sensor error!");
    } else {
      Serial.print("Pressure: ");
      Serial.print(pressure_kPa, 4);
      Serial.println(" kPa");
    }
  }

  // ------------------------- Flow Sensor Reading -------------------------
  if (currentMillis - lastFlowCheck >= measureInterval) { 
    lastFlowCheck = currentMillis;

    float frequency = GetFrequency();
    float flow_Lmin = frequency / factorK;

    Serial.print("Flow Rate: ");
    Serial.print(flow_Lmin, 3);
    Serial.println(" L/min");
  }

  // ------------------------- Servo Movement -------------------------
  if (moveServo && currentMillis - lastServoUpdate >= servoDelay) { 
    lastServoUpdate = currentMillis;

    if (increasing) {
      angle += servoStep;
      if (angle >= 180) increasing = false;
    } else {
      angle -= servoStep;
      if (angle <= 10) increasing = true;
    }
    
    servo.write(angle);
    Serial.print("Servo Angle: ");
    Serial.println(angle);
  }
}
