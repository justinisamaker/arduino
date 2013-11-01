#define button 2
#define red 3
#define green 5
#define blue 9
#define potOne 0 

int redRead, greenRead, blueRead;
int redInc, greenInc, blueInc;


void setup(){
  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  redRead = 0;
  greenRead = 0;
  blueRead = 0;
  redInc = 1;
  greenInc = 8;
  blueInc = -2;
}

void loop(){
  redRead += redInc;
  greenRead += greenInc;
  blueRead += blueInc;
  
  if(redRead > 200){
    redRead = 0;
  }
  
  if(greenRead > 200){
    greenRead = 0;
  }
  
  if(blueRead > 200){
    blueRead = 0;
  }
  
    if(redRead < 0){
    redRead = 200;
  }
  
  if(greenRead < 0){
    greenRead = 200;
  }
  
  if(blueRead < 0){
    blueRead = 200;
  }
  
  rgbLed(redRead, greenRead, blueRead, red, green, blue);
  delay(50);
}


void rgbLed(int redVal, int greenVal, int blueVal, int ledOne, int ledTwo, int ledThree){
  int mappedPwm;

  mappedPwm = map(redVal, 0, 255, 0, 200);
  analogWrite(ledOne, mappedPwm);

  mappedPwm = map(greenVal, 0, 255, 0, 200);
  analogWrite(ledTwo, mappedPwm);

  mappedPwm = map(blueVal, 0, 255, 0, 200);
  analogWrite(ledThree, mappedPwm);
} 
