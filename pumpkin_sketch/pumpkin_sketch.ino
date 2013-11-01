#include <Servo.h>

Servo servoMotor;

int servoPin = 7;

//motor A connected between A01 and A02
//motor B connected between B01 and B02

int STBY = 10; //standby

//Motor A
int PWMA = 3; //Speed control 
int AIN1 = 13; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

// PIR

int PIR = 2;

// LED

int BLUE = 6;
int GREEN = 9;

//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 30;        

//the time when the sensor outputs a low impulse
long unsigned int lowIn;         

//the amount of milliseconds the sensor has to be low 
//before we assume all motion has stopped
long unsigned int pause = 5000;  

boolean lockLow = true;
boolean takeLowTime;  

void setup(){
  servoMotor.attach(servoPin);
  Serial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  pinMode(PIR, INPUT);
  digitalWrite(PIR, LOW);
  
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  
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

void loop(){
  
  if(digitalRead(PIR) == HIGH){
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    move(1, 255, 1); //motor 1, full speed, left
    move(2, 255, 1); //motor 2, full speed, left
  
    delay(1000); //go for 1 second
    stop(); //stop
    delay(250); //hold for 250ms until move again
  
    move(1, 128, 0); //motor 1, half speed, right
    move(2, 128, 0); //motor 2, half speed, right
  
    delay(1000);
    stop();
    delay(250);
    
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);servoMotor.write(0);
    delay(100);
    servoMotor.write(180);
    delay(100);
    
  } else {
   stop(); 
   digitalWrite(GREEN, LOW);
   digitalWrite(BLUE, LOW);
  }
 
}


void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
}
