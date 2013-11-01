// Control a motor's speed with a pot

#define motor 3
#define pot 0

void setup(){
  pinMode(motor, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop(){
  int changeAmount;
  int randomNumber;
  int motorSpeed = 128;

  randomNumber = random(1000);
  changeAmount = map(randomNumber, 0, 1000, -5, 5);
  motorSpeed = motorSpeed + changeAmount;
  delay(50);
//  motorSpeed = constrain(motorSpeed, 0, 255);

  analogWrite(motor, motorSpeed);
  Serial.print(changeAmount);
  Serial.print("::");
  Serial.println(motorSpeed);


}

void blink(int pin, int durationHigh, int durationLow){
  digitalWrite(pin, HIGH);
  delay(durationHigh);
  digitalWrite(pin, LOW);
  delay(durationLow);
}








