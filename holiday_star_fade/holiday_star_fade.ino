int redLed = 3;
int greenLed = 5;
int blueLed = 6;

void setup()  { 
  pinMode(redLed, OUTPUT);   
  pinMode(greenLed, OUTPUT);   
  pinMode(blueLed, OUTPUT);   
} 

void loop()  {
  fadeIn(redLed, 15);
  fadeOut(redLed, 5);
  fadeIn(greenLed, 15);
  fadeOut(greenLed, 5);
  fadeInAll(15);
  fadeOutAll(5);
}

int fadeIn(int color, int duration){
  for(int fade=0; fade<=255; fade+=1){
        analogWrite(color, fade); 
        delay(duration);
   }
}

int fadeOut(int color, int duration){
 for(int fade=255; fade>=0; fade-=1){
        analogWrite(color, fade); 
        delay(duration);
    }
}

int fadeInAll(int duration){
  for(int fade=0; fade<=255; fade+=1){
        analogWrite(redLed, fade);
        analogWrite(greenLed, fade); 
        analogWrite(blueLed, fade);
        delay(duration);
   }
}

int fadeOutAll(int duration){
 for(int fade=255; fade>=0; fade-=1){
        analogWrite(redLed, fade);
        analogWrite(greenLed, fade); 
        analogWrite(blueLed, fade);
        delay(duration);
    }
}

