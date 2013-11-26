// PRESSURE SENSOR ALARM / SANTA COOKIE SENSOR

int led = 13;
int buzzer = 2;
int pressureSensor = 0; 
int pot = 5;
byte val = 0;
int top;

void setup() {

  pinMode(led, OUTPUT); 
  pinMode(buzzer, OUTPUT);
  pinMode(pressureSensor, INPUT);
  pinMode(pot, INPUT);

  Serial.begin(9600);

}

void loop() {

  val = analogRead(pressureSensor);
  top = analogRead(pot);
  
  if (val <= top) {

    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);

  } else {
    digitalWrite(led, LOW); 
    digitalWrite(buzzer, LOW);
  }
  
  Serial.print(val);
  Serial.print("||");
  Serial.println(top);

  delay(100);

}

