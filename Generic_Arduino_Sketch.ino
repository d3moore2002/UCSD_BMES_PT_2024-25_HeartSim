/*
This is a comment at the top of a program, 
it will not be recognized as code. Very good 
to add an explanation of what your code does 
here.

This sketch shows how to read a value from a
sensor connected to pin A1, print it out in 
the Serial Monitor, and turn on an LED connected
to pin number 2 if a conditional is met.
*/

int sensorPin = A1; //define pin A1 (analog pin)
int ledPintwo = 2; //define pin 2 (digital pin)
int ledPinfour = 4; // defined pin 3
int sensorValue; //create variable for storing readings
int sensorPinThree = 3; // defined pin 3


//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPintwo, INPUT); //define ledPin as an output
    pinMode(ledPinfour, INPUT); //define ledPin as an output
}

void loop() {
  int button = digitalRead(sensorPinThree); // reads if the button connected to pin 3 is on or off
    if(button, HIGH){
      digitalWrite(ledPintwo, HIGH); // turns led of pin 2 on
      digitalWrite(ledPinfour, LOW); // turns off led of pin 4

    }
    else{
      digitalWrite(ledPinfour, HIGH); // turns led of pin 4 on
      digitalWrite(ledPintwo, LOW); // turns led of pin 2 off

    }

}
