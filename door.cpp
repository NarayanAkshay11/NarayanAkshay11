#include <Servo.h>
const int servoPin = 9; //servo connect
const int ldrPin = A0; //photo resistor connect
const int threshold = 500; //light threshols
const int servoOpenPosition = 90; //lifted door
const int servoClosePosition = 0; //closed door
const long stayOpenDuration = 20000; //lift duration - 20s

Servo liftingServo; //servo obj
bool isDoorOpen = false; //open variable
unsigned long doorOpenTime = 0; //open time

void setup(){
  liftingServo.attach(servoPin); //servo pin
  liftingServo.write(servoClosePosition); //start closed
  Serial.begin(9600); //serial com for debug
}

void loop(){
  int lightLevel = analogRead(ldrPin); //light read
  Serial.print("Light Level: ");
  Serial.println(lightLevel); //light lvl print for record

  if(lightLevel > threshold && !isDoorOpen){ //light + closed door
    liftingServo.write(servoOpenPosition);
    isDoorOpen = true;//door open 
    doorOpenTime = millis();//time record start
  }

  if(isDoorOpen && (millis() - doorOpenTime >= stayOpenDuration)){ //if open + time is greater
    liftingServo.write(servoClosePosition); //close door
    isDoorOpen = false;
  }
  delay(100); //miscelaneous
}
