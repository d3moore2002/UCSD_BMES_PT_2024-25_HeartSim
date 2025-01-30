
int ledPin2 = 2; //define pin 2 (digital pin)
int ledPin4 = 4; //pin 4
int buttonPin = 3; //define pin 3 for the button 
int buttonstate; //storing button info

//void setup is for configurations on start up
void setup() { 
    Serial.begin(9600); //initialize serial communication
    pinMode(ledPin2, OUTPUT); //ledPin2 output
    pinMode(ledPin4, OUTPUT); //ledPin4 output
    pinMode(buttonPin, INPUT_PULLUP); //buttonpin input (INPUT_PULLUP stores the state of switches/buttons/sensors until updated)
}

void loop() {
    buttonstate = digitalRead(buttonPin); // do a button reading
    if (buttonstate == HIGH) {
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin4, LOW);
    }
    else { 
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin4, HIGH);
    }
}
