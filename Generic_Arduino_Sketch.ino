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
int ledPin4 = 4; //pin 4
int buttonPin = 3; //define pin 3 for the button 
int buttonstate; //storing button info

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPin2, OUTPUT); //ledPin2 output
    pinMode(ledPin4, OUTPUT); //ledPin4 output
    pinMode(buttonPin, INPUT); //buttonpin input
}

void loop() {
    buttonstate = digitalRead(buttonPin); // do a button reading

    if (buttonstate == HIGH) {
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin4, LOW});
    else { 
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin4, HIGH);
    }
}
