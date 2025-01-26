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
int buttonPin = 3;
int ledPin4 = 4;
int sensorValue; //create variable for storing readings

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPin2, OUTPUT); //define ledPin as an output
    pinMode(ledPin4, OUTPUT);
    pinMode(buttonPin, INPUT);
}

void loop() {
    sensorValue = analogRead(sensorPin); // do a sensor reading
    
    Serial.print("Sensor value is: "); //print a message to the serial monitor
    Serial.println(sensorValue); //print the value to the serial monitor
    
    if digitalRead(buttonPin, HIGH)    // if the button at digitial pin 3 is on...
        digitalWrite(ledPin2, HIGH);     // then turn on led pin 2
        digitalWrite(ledPin4, LOW);       // keep led pin 4 off

    else                              // if the button at digitial pin 3 is off...
        digitalWrite(ledPin4, HIGH);    // then turn on led pin 4
        digitialWrite(ledPin2, LOW);    // keep led pin 2 off             
    }
}
