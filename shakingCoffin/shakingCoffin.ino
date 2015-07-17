#include <Servo.h>

Servo servoMotor; 

int calibrationTime = 10;

int servoPin = 3;
int motorPin = 4;
int ledPin = 5;
int pirPin = 6;

///////////// SETUP

void setup(){
  Serial.begin(9600);
  servoMotor.attach(servoPin);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
  }

///////////// LOOP

void loop(){
   if(digitalRead(pirPin) == HIGH){
     int randLoop = random(1, 5);    
     for(int randIter = randLoop; randIter <= 6; randIter++){
       int randDuration = random(100, 1000);
       int randServoDuration = random(100, 300);
       servoShudder(randServoDuration, 10, 60);
       otherShudder(motorPin, randDuration);
       otherShudder(ledPin, randDuration);
     }
   }   
}

///////////// FUNCTIONS

int servoShudder(int shudderDuration, int highRot, int lowRot){
   servoMotor.write(highRot);
   delay(shudderDuration);
   servoMotor.write(lowRot);
}

int otherShudder(int targetPin, int otherShudderDuration){
  digitalWrite(targetPin, HIGH);
  delay(otherShudderDuration);
  digitalWrite(targetPin, LOW);
}
