#include <Servo.h>

// Adjustable Variable
int initAngleMitral = 180;    //starting angle for mitral valve (open)
int initAngleAortic = 0;  //starting angle for aortic valve (closed)
int scanDelay = 30;       //delay (time) between movements

Servo servoMitral;
Servo servoAortic;
int angleMitral = initAngleMitral;
int angleAortic = initAngleAortic;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  servoMitral.attach(9);
  servoAortic.attach(8);
  servoMitral.write(initialAngleMitral);
  servoAortic.write(initialAngleAortic);
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
