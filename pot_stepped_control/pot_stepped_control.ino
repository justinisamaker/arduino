//control position of stepper motor by potVal

#include <Stepper.h>

#define numSteps 48
#define pot 0
#define maxRot 40

int potVal;
int motorCur = 0; //motor_position in Shawn's code - the curPos of the mot 0->40
int motorNew; // new pos that the motor is going to
int motorMove; //steps to move in Shawn's code
//int dir;

 Stepper stepper(numSteps, 8,9,10,11);

void setup(){
 stepper.setSpeed(120);
}

void loop(){
  potVal = analogRead(pot);
  motorNew = map(potVal, 0, 1024, 0, maxRot);
  
  if(motorNew > motorCur){
   motorMove = (motorNew-motorCur);
   stepper.step(motorMove);
  }
  else{
   motorMove = (motorCur-motorNew);
   stepper.step(motorMove * -1);
  }
  
  motorCur = motorNew;
  
}
