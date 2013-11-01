#include <SoftwareSerial.h>

int irLed = 5;
int irRec = 4;
int sensor = A5;
int sensorVal = 0;
int ledPin = 13;
int softwareTx = 8;
int softwareRx = 7;

SoftwareSerial s7s(softwareRx, softwareTx);
unsigned int counter = 0;
char tempString[10];

void setup(){
  pinMode(irLed, OUTPUT);
  pinMode(irRec, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  // Serial.println("START");
  // delay(100);
  s7s.begin(9600);
  
  clearDisplay();
  s7s.print("-HI-");
  setDecimals(0b111111);
  // Flash brightness values at the beginning
  setBrightness(0);  // Lowest brightness
  delay(1500);
  setBrightness(127);  // Medium brightness
  delay(1500);
  setBrightness(255);  // High brightness
  delay(1500);

  // Clear the display before jumping into loop
  clearDisplay();  
}

void loop(){
  digitalWrite(irLed, HIGH);
  sensorVal = analogRead(sensor);
  Serial.println(sensorVal);
  
  if(sensorVal >= 1020){
     digitalWrite(ledPin, HIGH);
     delay(100);
     digitalWrite(ledPin, LOW);
     sprintf(tempString, "%4d", counter);
     s7s.print(tempString);
     setDecimals(0b00000010);  // Sets digit 3 decimal on
     counter ++;
     // delay(100);
   }
}

void clearDisplay()
{
  s7s.write(0x76);  // Clear display command
}

// Set the displays brightness. Should receive byte with the value
//  to set the brightness to
//  dimmest------------->brightest
//     0--------127--------255
void setBrightness(byte value)
{
  s7s.write(0x7A);  // Set brightness command byte
  s7s.write(value);  // brightness data byte
}

// Turn on any, none, or all of the decimals.
//  The six lowest bits in the decimals parameter sets a decimal 
//  (or colon, or apostrophe) on or off. A 1 indicates on, 0 off.
//  [MSB] (X)(X)(Apos)(Colon)(Digit 4)(Digit 3)(Digit2)(Digit1)
void setDecimals(byte decimals)
{
  s7s.write(0x77);
  s7s.write(decimals);
}
