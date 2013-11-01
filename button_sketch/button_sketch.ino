//Turn a light on when BUTTON_ONE is pressed. 
//Turn a light off when same BUTTON_ONE is pressed again. 

#define LIGHT 13
#define BUTTON 2
#define STARTINGSPEED 500
#define BUTTON_TWO 3
#define BUTTON_THREE 4
#define SLOW_LIMIT 1000
#define FAST_LIMIT 20

int currentState = LOW;
int prevState = LOW;
int buttonPressed = LOW; // Was there a low/high switch transition?
int lightState = LOW; // Is the light on?
int blinkSpeed = STARTINGSPEED; //sets blink speed to starting speed
int SPEEDCHANGE = 50; //declares speedchange (interval)

void setup(){
  Serial.begin(9600);
  pinMode(LIGHT, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON_TWO, INPUT);
  pinMode(BUTTON_THREE, INPUT);
}

void loop(){  
  currentState=digitalRead(BUTTON); //read on or off of BUTTON_ONE

  if((currentState == HIGH) && (prevState) == LOW){ //Logic for BUTTON_ONEPressed
    buttonPressed = HIGH;
  }
  else{
    buttonPressed = LOW;
  }

  prevState = currentState; //set current state to be the val of prevState

  /* IF BUTTON TWO IS PRESSED, SPEED BLINK UP */
  if(digitalRead(BUTTON_TWO) == HIGH){
    SPEEDCHANGE -= 5;
  }

  /* IF BUTTON THREE IS PRESSED, SLOW BLINK DOWN */
  if(digitalRead(BUTTON_THREE) == HIGH){
    SPEEDCHANGE += 5;
  }

  /* IF THE BLINK SPEED REACHES THE FAST LIMIT, KEEP IT THERE */
  if(blinkSpeed <= FAST_LIMIT){
    blinkSpeed = FAST_LIMIT;
  }

  /* IF THE BLINK SPEED REACHES THE SLOW LIMIT, KEEP IT THERE */
  if(blinkSpeed >= SLOW_LIMIT){
    blinkSpeed = SLOW_LIMIT;
  }


  /* IF ON/OFF BUTTON IS PRESSED, SET THE LIGHTSTATE TO THE OPPOSITE */
  if(buttonPressed == HIGH){
    if(lightState == HIGH){
      lightState = LOW;
    }

    else{
      lightState = HIGH;
    }
  }

  /* IF BUTTON IS PRESSED AND LIGHT IS ON, BLINK THE LIGHT */
  if(lightState==HIGH){        //if button is pressed, turn LED on and blink
    digitalWrite(LIGHT, HIGH);
    delay(blinkSpeed+=SPEEDCHANGE);
    digitalWrite(LIGHT, LOW);
    delay(blinkSpeed+=SPEEDCHANGE);
  }

  Serial.println(blinkSpeed);

}






