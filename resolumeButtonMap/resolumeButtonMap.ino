int buttonOne = 8;
int buttonTwo = 9;
int buttonThree = 10;
int power = 2;

int buttonOneState;
int buttonTwoState;
int buttonThreeState;
int powerState;

int shift = 129;
int left = 216;
int up = 218;
int right = 215;
int down = 217;
int enter = 176;

void setup(){
  Serial.begin(9600);

  pinMode(buttonOne, INPUT_PULLUP);
  pinMode(buttonTwo, INPUT_PULLUP);
  pinMode(buttonThree, INPUT_PULLUP);
  pinMode(power, INPUT_PULLUP);

  Keyboard.begin();
}

void loop(){
  buttonOneState = digitalRead(buttonOne);
  buttonTwoState = digitalRead(buttonTwo);
  buttonThreeState = digitalRead(buttonThree);
  powerState = digitalRead(power);

  if(powerState == HIGH){
    if(buttonOneState == LOW){
      keyboardCommand(left);
      Serial.println("button 1");
      delay(1000);
    } else if (buttonTwoState == LOW){
      keyboardCommand(right);
      Serial.println("button2");
      delay(1000);
    } else if (buttonThreeState == LOW){
      Keyboard.press(shift);
      Keyboard.press(up);
      Keyboard.releaseAll();
      Serial.println("button3"); 
      delay(1000);
    }
  }
  
}

void keyboardCommand(int dir){
  Keyboard.press(shift);
  Keyboard.press(dir);
  Keyboard.releaseAll();
  delay(100);
  Keyboard.write(enter);
}
