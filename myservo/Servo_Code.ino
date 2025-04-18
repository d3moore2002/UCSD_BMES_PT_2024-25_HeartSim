#include <Servo.h>

// Adjustable Variable
int initialAngle = 10;    //starting angle
int scanDelay = 30;       //delay (time) between movements

Servo servo;
int angle = initialAngle;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  servo.attach(9);
  servo.write(initialAngle);
}

void loop() { 
  // Scan from initialAngle to 180 degrees
  for (angle = initialAngle; angle <= 180; angle++) {                                  
    servo.write(angle);               
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(scanDelay);                   
  } 

  // Now scan back from 180 to initialAngle
  for (angle = 180; angle >= initialAngle; angle--) {                                
    servo.write(angle);           
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(scanDelay);       
  } 
}
