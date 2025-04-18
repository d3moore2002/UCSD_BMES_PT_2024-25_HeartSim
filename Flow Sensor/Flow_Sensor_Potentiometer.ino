const int potPin = A0;  // Potentiometer to A0
int pot = 0;       // Potentiometer value
int LEDPin = 13;
float flowRate = 0.0;   // Flow rate initialized to 0

void setup() {
  Serial.begin(9600);  // Start serial 
  
}


void loop() {
  pot = analogRead(potPin);  // Read the potentiometer value (0 to 1023)
  // Map potentiometer value to a flow rate range, for example: 0 - 0.0 to 5000 mililiters per minute (mL/min)
  flowRate = map(pot, 0, 1023, 0, 5000);  // Maps to a range of 0 to 5000 mL/min

  // Output the flow rate
  Serial.print("Flow Rate: ");
  Serial.print(flowRate); 
  Serial.println(" mL/min");

 if (flowRate >= 2500) { // If flowRate above 2500 mL/min then turn LED on, else turn it off
    digitalWrite(LEDPin, HIGH);
  }
  else {
    digitalWrite(LEDPin, LOW);
  }

  delay(500);  // Delay to slow down the serial output
}
