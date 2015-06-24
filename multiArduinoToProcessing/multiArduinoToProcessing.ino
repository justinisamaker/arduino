const int pot1 = A0;
const int pot2 = A1;
const int pot3 = A2;
const int pot4 = A3;
const int pot5 = A4;
const int pot6 = A5;

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.print(analogRead(pot1));
  Serial.print(",");
  Serial.print(analogRead(pot2));
  Serial.print(",");
  Serial.print(analogRead(pot3));
  Serial.print(",");
  Serial.print(analogRead(pot4));
  Serial.print(",");
  Serial.print(analogRead(pot5));
  Serial.print(",");
  Serial.println(analogRead(pot6));
}

