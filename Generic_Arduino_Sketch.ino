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
int ledPin2 = 2; //define pin 2 (digital pin)
int sensorValue; //create variable for storing readings
int buttonPin = 3; // create button variable
int ledPin4= 4;// define pin 4(digital pin)
int buttonValue;// defines button state as a variable

//void setup is for configurations on start up
void setup() { 
    pinMode(ledPin1, OUTPUT); //define ledPin1 as an output
    pinMode(ledPin2, OUTPUT); //define ledPin2 as an output
    pinMode(buttonPin, INPUT);// define buttonPin as an input
}

void loop() {
    buttonValue=digitalRead(buttonPin) //set buttonValue to 1 or 0 based on if button is on or off
    if(buttonValue=1){                 //if button is on turn on ledPin2 and turn off ledPin4
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin4, LOW);
    }
    if(buttonValue=0){                //if button is on turn on ledPin2 and turn off ledPin4
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin4, HIGH);
    }
}
