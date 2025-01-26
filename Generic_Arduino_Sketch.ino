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
int ledPinOn = 2; //define pin 2 (digital pin)
int buttonPin = 3; //define pin 3 (digital button pin)
int ledPinOff = 4; //define pin 4 (digital pin)
int sensorValue; //create variable for storing sensor readings
int buttonValue; //create variable for storing button readings

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPinOn, OUTPUT); //define ledPinOn as an output
    pinMode(ledPinOff, OUTPUT); //define ledPinOff as an output
    pinMode(buttonPin, INPUT); //define buttonPin as an input
}

void loop() {
    sensorValue = analogRead(sensorPin); // do a sensor reading
    buttonValue = digitalRead(buttonPin); // do a button reading

    //check if button is off
    if(buttonValue == LOW) {
        digitalWrite(ledPinOff, HIGH) //if off, turn on pin 4 and turn off pin 2
        digitalWrite(ledPinOn, LOW)

    }
    //check if button is on
    else {
        digitalWrite(ledPinOn, HIGH) //if on, turn on pin 2 and turn off pin 4
        digitalWrite(ledPinOff, LOW)
    }
    
    Serial.print("Sensor value is: "); //print a message to the serial monitor
    Serial.println(sensorValue); //print the value to the serial monitor
    
    //check if sensorValue is below 50
    if(sensorValue < 50) { 
        digitalWrite(ledPin, HIGH); //if it is, turn on the LED on pin 2.
    }
    //if sensorValue is above 50, turn off the LED
    else{ 
        digitalWrite(ledPin, LOW);
    }
}
