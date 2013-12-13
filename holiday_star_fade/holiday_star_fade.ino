/*
 Tri-Color LED Breakout - An example sketch for the Tri-Color LED Breakout
 By: Hilary Hoops
 SparkFun Electronics
 Date: 6/23/11
 License: CC-BY SA 3.0 - Creative commons share-alike 3.0
 use this code however you'd like, just keep this license and
 attribute. Let me know if you make hugely, awesome, great changes.
 */
 
 /*
 Code modified to run inside a tree topper and be Christmassy
 */
  
int RedLED = 3;     // LED connected to digital pin 9 (pwm pin)
int GrnLED = 5;    // LED connected to digital pin 10 (pwm pin)
int BluLED = 6;    // LED connected to digital pin 11 (pwm pin)
int LED[3]={RedLED, GrnLED,BluLED}; //an array to make it easier to cycle though the LED colors

void setup()  { 
  //Set pins as output pins
  pinMode(RedLED, OUTPUT);   
  pinMode(GrnLED, OUTPUT);   
  pinMode(BluLED, OUTPUT);   
} 

void loop()  {
  fadeIn(RedLED, 600);
  fadeOut(RedLED, 600);
  fadeIn(GrnLED, 600);
  fadeOut(GrnLED, 600);
  //Fade all the LEDs in and out 
  //Fade in
  for(int fade=0; fade<=255; fade+=5){
      analogWrite(RedLED, fade); 
      analogWrite(GrnLED, fade); 
      analogWrite(BluLED, fade); 
      delay(1000);
  }
  //Fade out
  for(int fade=255; fade>=0; fade-=5){
      analogWrite(RedLED, fade); 
      analogWrite(GrnLED, fade); 
      analogWrite(BluLED, fade); 
      delay(1000);
  }
}

int fadeIn(int color, int duration){
  for(int fade=0; fade<=255; fade+=5){
        analogWrite(color, fade); 
        delay(duration);
   }
}

int fadeOut(int color, int duration){
 for(int fade=255; fade>=0; fade-=5){
        analogWrite(color, fade); 
        delay(duration);
    }
}

