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


int ledPin2 = 2; //define pin 2 (digital pin)

int buttVal; // button on or off variable
int buttPin = 3; // Pin button is connected to
int ledPin4 = 4; // define led pin 4

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPin2, OUTPUT); //define ledPin2 as an output
    pinMode(ledPin4, OUTPUT); //define ledPin4 as an output
    pinMode(buttPin, INPUT); // define button pin as an input

}

void loop() {
    
    buttVal = digitalRead(buttPin); // Sensor reading of button pin to see if button is on or off
    
         if(buttVal == HIGH) { // If the button is on...
        digitalWrite(ledPin2, HIGH); // Turn LED 2 on
      }
        else { // If the button is off...
        digitalWrite(ledPin2, LOW; // Turn LED 2 off
      }
        if(buttVal == LOW) { // If the button is off...
        digitalWrite(ledPin4, HIGH); // Turn LED 4 on
      }
        else { // If the button is on...
        digitalWrite(ledPin4, LOW; //Turn LED 4 off
      }
}
