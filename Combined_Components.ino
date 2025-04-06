// Combined code
/*
  Combined Code for SparkFun Qwiic MicroPressure Sensor & YF-S201 Flow Sensor
  - Reads pressure (in kPa) from the MicroPressure sensor (I2C communication)
  - Reads flow rate (in L/min) from the YF-S201 flow sensor (interrupt-based)
  - Displays both values on the Serial Monitor
*/

//myservo initialization
#include <Servo.h>
#include <Servo.h>

Servo servo;
int angle = 10;

// Include necessary libraries
#include <Wire.h>                      // Required for I2C communication
#include <SparkFun_MicroPressure.h>     // Library for SparkFun MicroPressure sensor

// Define the I2C address for the MicroPressure sensor (default: 0x18)
#define SENSOR_I2C_ADDRESS 0x18

// Define the kPa unit if not included in the library
#ifndef KPA
  #define KPA 1
#endif

// Create an instance of the MicroPressure sensor object
SparkFun_MicroPressure mpr;

// ------------------------- Flow Sensor Configuration -------------------------

const int sensorPin = 2; // Digital pin where the flow sensor is connected
const int measureInterval = 2500; // Measurement time interval in milliseconds (2.5 seconds)
volatile int pulseCounter = 0; // Keeps track of pulses from the flow sensor

// Calibration factor for the flow sensor
// Default for YF-S201 is 7.5, FS300A is 8.767, FS400A is 3.5
const float factorK = 8.767; 

// Interrupt Service Routine (ISR) - Triggered when a pulse is detected from the flow sensor
void ISRCountPulse() {
  pulseCounter++; // Increment pulse counter each time a pulse is detected
}

// Function to calculate the frequency (Hz) of pulses from the flow sensor
float GetFrequency() {
  pulseCounter = 0; // Reset pulse counter before measurement

  interrupts(); // Enable interrupts to count pulses
  delay(measureInterval); // Wait for the specified measurement interval
  noInterrupts(); // Disable interrupts to stop counting pulses

  return (float)pulseCounter * 1000 / measureInterval; // Convert pulses to frequency in Hz
}

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200); 

  //myservo
  servo.attach(9);
  servo.write(angle);

  // Initialize I2C communication
  Wire.begin();         

  // Attempt to connect to the MicroPressure sensor with retries
  int retries = 5;
  while (!mpr.begin(SENSOR_I2C_ADDRESS) && retries > 0) {
    Serial.println("Cannot connect to MicroPressure sensor. Retrying...");
    delay(1000); // Wait 1 second before retrying
    retries--;
  }

  // If connection fails after retries, halt the program
  if (retries == 0) {
    Serial.println("Sensor connection failed. Check wiring!");
    while (1); // Infinite loop to prevent further execution
  }

  Serial.println("MicroPressure sensor connected successfully!");

  // Set up the flow sensor pin as an input
  pinMode(sensorPin, INPUT);

  // Attach an interrupt to detect pulses from the flow sensor
  attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
}

void loop() {
  // ------------------------- Pressure Sensor Reading -------------------------
  float pressure_kPa = mpr.readPressure(KPA); // Read pressure in kilopascals

  // ------------------------- Flow Sensor Reading -------------------------
  float frequency = GetFrequency(); // Get frequency of pulses from the flow sensor
  float flow_Lmin = frequency / factorK; // Calculate flow rate in liters per minute (L/min)

  //---------------------------My Servo moves ------------------------------
    // Scan from 10 to 180 degrees
  for (angle = 10; angle < 180; angle++) {                                  
    servo.write(angle);               
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(30);                   
  } 

  // Now scan back from 180 to 10 degrees
  for (angle = 180; angle > 10; angle--) {                                
    servo.write(angle);           
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(30);       
  } 

  // ------------------------- Display Readings -------------------------
  Serial.print("Pressure: ");
  Serial.print(pressure_kPa, 4); // Print pressure with 4 decimal places
  Serial.println(" kPa");

  Serial.print("Flow Rate: ");
  Serial.print(flow_Lmin, 3); // Print flow rate with 3 decimal places
  Serial.println(" L/min");

  Serial.println("------------------------"); // Separator for readability
  delay(500); // Short delay before next measurement
}
