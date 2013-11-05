#include <Servo.h>

Servo eyeL;
Servo eyeR;

int posEye;
int posEyeDest;
int wait;
int rate = 2;

void setup(){
  eyeL.attach(3);
  eyeR.attach(2);
  
  posEyeDest = posEye = 70;
}

void loop(){
  if(wait==0){
     posEyeDest=random(60,91);
    wait=random(50,350); 
  }
  else{
    posEye=slew_servo(posEye, posEyeDest, rate);
   wait--; 
  }
  eyeL.write(posEye);
  eyeR.write(posEye);
  delay(10);
}

int slew_servo( int pos, int dest, int rate) 
{
    int diff = pos - dest;
    if( diff == 0 ) return pos;
    else if( diff > -rate ) pos++;
    else if( diff <  rate ) pos--;
    if(      diff > 0 ) pos -= rate;
    else if( diff < 0 ) pos += rate;
    return pos;
}
