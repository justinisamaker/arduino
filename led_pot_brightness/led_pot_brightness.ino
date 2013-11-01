#define potOneIn 0
#define led 13
#define pwmOut 9 

int potOneVal;
int blinkSpeed;
int brightness;

void setup(){
  pinMode(led, OUTPUT);
  pinMode(pwmOut, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  potOneVal = analogRead(potOneIn);
  Serial.print("Pot One Val: ");
  Serial.print(potOneVal);
  Serial.print("   ");
  //MAP REMAPS THE RANGE OF THE DEVICE
  //ARGUMENTS ARE (VALUE, FROMLOW, FROM HIGH, TO LOW, TO HIGH)
  blinkSpeed = map(potOneVal, 0, 1023, 100, 500);
  brightness = map(potOneVal, 0, 1023, 0, 255);
  Serial.print("Blink Speed: ");
  Serial.print(blinkSpeed);
  Serial.print("   ");
  Serial.print("Brightness: ");
  Serial.println(brightness); 
  analogWrite(pwmOut, brightness);
  blink(led, blinkSpeed); //CALLS THE BLINK FUNCTION INSIDE THE LOOP 
}

//DEFINES BLINK AS A FUNCTION
//DEFINES INTS FOR PIN NUMBER AND BLINK DURATION IN ARGUMENTS SECTION
void blink(int pinNum, int duration){
  digitalWrite(pinNum, HIGH);
  delay(duration);
  digitalWrite(pinNum, LOW);
  delay(duration);  
}
