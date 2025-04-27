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
  // 0.67s Mitral Valve closes
  for (angle = initialAngle; angle <= 180; angle++) {                                  
    servo.write(angle);               
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(scanDelay);                   
  } 

  // 0.75s Aortic Valve opens
  for (angle = 180; angle >= initialAngle; angle--) {                                
    servo.write(angle);           
    Serial.print("Servo Angle: ");
    Serial.println(angle);  // Print the current angle to Serial Monitor
    delay(scanDelay);       
  } 

  // 1.1s Aortic Valve closes

  // 1.167s Mitral Valve opens

}
