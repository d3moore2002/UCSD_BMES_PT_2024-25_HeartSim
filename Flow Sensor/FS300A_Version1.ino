const int sensorPin = 2;
const int measureInterval = 2500;
volatile int pulseCounter;

// YF-S201
// const float factorK = 7.5;

// FS300A
const float factorK = 5.5;

// FS400A
//const float factorK = 3.5;

void ISRCountPulse()
{
  pulseCounter++;
}

float GetFrequency()
{
  pulseCounter = 0;

  interrupts();
  delay(measureInterval);
  noInterrupts();

  return (float)pulseCounter * 1000 / measureInterval; 
}

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensorPin), ISRCountPulse, RISING);
}

void loop()
{
  // obtain frequency in Hz
  float frequency = GetFrequency();

  // calculate flow rate L/min
  float flow_Lmin = frequency / factorK;

  Serial.print("Frequency: ");
  Serial.print(frequency, 0);
  Serial.print(" (Hz)\tFlow rate: ");
  Serial.print(flow_Lmin, 3);
  Serial.println(" (L/min)");
}
