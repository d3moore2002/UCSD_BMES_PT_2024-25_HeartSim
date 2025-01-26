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

int sensorPin = 3; //define pin A1 (analog pin)
int ledPin2 = 2; //define pin 2 (digital pin)
int ledPin4 = 4; //define pin 4
int sensorValue; //create variable for storing readings

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPin2, OUTPUT); //define ledPin as an output
    pinMode(ledPin4, OUTPUT);  //define pin4 as an output
    pinMode(sensorPin, INPUT); //define pin3 as an input
}

void loop() {
    sensorValue = digitalRead(sensorPin); // do a sensor reading
    
    Serial.print("Sensor value is: "); //print a message to the serial monitor
    Serial.println(sensorValue); //print the value to the serial monitor
    
    //check if sensorValue is below 50
    if(sensorValue = HIGH) { 
        digitalWrite(ledPin2, HIGH); //if it is, turn on the LED on pin 2.
        digitalWrite(ledPin4, LOW);
    }
    //if sensorValue is above 50, turn off the LED
    else{ 
        digitalWrite(ledPin4, HIGH);
        digitalWrite(ledPin2, LOW);
    }
}
