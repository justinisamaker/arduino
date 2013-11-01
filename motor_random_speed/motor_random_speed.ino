// Random direction and speed for a motor

#define aInOne 5
#define aInTwo 4
#define pwmA 3
#define pot 0
#define highSpeed 230
#define lowSpeed 70
#define highDelay 200
#define lowDelay 10

void setup(){
  Serial.begin(9600);
  pinMode(aInOne, OUTPUT);
  pinMode(aInTwo, OUTPUT);
  pinMode(pwmA, OUTPUT);
}

void loop(){
  randomSpeed(lowSpeed, highSpeed);
  randomDirection();
  randomBrakes(lowDelay, highDelay);
  aBrakes();
  randomBrakes(lowDelay, highDelay);
}

void aClockwise(){
  digitalWrite(aInOne, HIGH);
  digitalWrite(aInTwo, LOW);
}

void aCounter(){
  digitalWrite(aInOne, LOW);
  digitalWrite(aInTwo, HIGH);
}

void aBrakes(){
  digitalWrite(aInOne, HIGH);
  digitalWrite(aInTwo, HIGH);
}

void aOff(){
  digitalWrite(aInOne, LOW);
  digitalWrite(aInTwo, LOW);
}

void randomSpeed(int lowVal, int highVal){
  int randomVal;  
  randomVal = random(lowVal, highVal);
  analogWrite(pwmA, randomVal);
  Serial.print("Random Speed: ");
  Serial.print(randomVal);
  Serial.print(" :::: ");
}

void randomDirection(){
  int randomVal;
  randomVal = random(0, 2);
  Serial.print("Random Direction: ");
  Serial.print(randomVal);
  Serial.print(" :::: ");
  if (randomVal == 0){
    aClockwise();
  }
  else {
    aCounter();
  }
}

void randomBrakes(int lowVal, int highVal){
  int randomVal;
  randomVal = random(lowVal, highVal);
  delay(randomVal); 
  Serial.print("Random Brakes: ");
  Serial.print(randomVal);
    Serial.println(" :::: ");
}





