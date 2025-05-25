const int sensorPin = 2; // Arduino Sensor Pin
const int measureInterval = 2500; // How many seconds will we measure each interval
volatile int pulseCounter; // Keeps track of how many times the water flow sensor sends a pulse within
// the measureInterval

// Volatile int forces the Arduino to check the pulseCounter value constantly to see if it needs
// to be updated

// YF-S201
// const float factorK = 7.5;

// FS300A value updated after callibration, used to be 5
const float factorK = 8.767

// FS400A
//const float factorK = 3.5;

void ISRCountPulse() // A special function called interrupt service routine, it is called each time
// a pulse is detected from the flow sensor. You HAVE to use attachInterrupt function to trigger this 
// to happen

{
  pulseCounter++; // Same as pulseCounter = pulseCounter + 1, just summing up pulses within an interrupt
}

float GetFrequency() // Function that calcuates the frequency after each measured interval 
{
  pulseCounter = 0; // Initializes the pulse value everytime to reset to 0

  interrupts(); // Enables the Arduino to count pulses, without any interrupts this won't happen
  delay(measureInterval); // Tells the Arduino over what period of time to count pulses
  noInterrupts(); // Tells the Arduino to stop counting pulses by ending the interupt

  return (float)pulseCounter * 1000 / measureInterval; // Counts the amount of pulses per second
  // (we multiply by 1000 to convert from milliseconds to seconds)
  
}

void setup()
{
  Serial.begin(9600); // Initializes the Serial so we can print later
  attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING); // Tells what Arduino
  // Pin will be interrupted, which function will get called (ISRCountPulse) and when will the ISR
  // becomes triggered (either when a pulse starts or a pulse ends, in this case a pulse ends)
}

// digitalPin

void loop()
{
  // obtain frequency in Hz
  float frequency = GetFrequency(); // Gives us the frequency value from the GetFrequency Function

  // calculate flow rate L/min
  float flow_Lmin = frequency / factorK; // Calculates the flow rate from the frequency value and 
  // constant value K depending on what sensor we will be using

// Serial Prints the Frequency and Flow Rate to Check 
  Serial.print("Frequency: ");  
  Serial.print(frequency, 0); // Prints the frequency value to 0 decimal places (whole number)
  Serial.print(" (Hz)\tFlow rate: ");
  Serial.print(flow_Lmin, 3); // Prints the flowrate value to 3 decimal plances
  Serial.println(" (L/min)");
}
