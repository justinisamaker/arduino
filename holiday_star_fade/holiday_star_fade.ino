/* HOLIDAY STAR SKETCH 
   Dec 2013 - Justin Smith
   Developed for Hack Yourself a Merry Little Xmas - Critical Mass, Chicago
*/

// Declare your variables that won't change
int redLed = 3;
int greenLed = 5;
int blueLed = 6;

// Run the setup loop
void setup()  { 
  // Tell the code what the pins that you described need to do
  pinMode(redLed, OUTPUT);   
  pinMode(greenLed, OUTPUT);   
  pinMode(blueLed, OUTPUT);   
} 

// Run the code
void loop()  {
  // Call a function that we declare below
  fadeIn(redLed, 15);
  fadeOut(redLed, 5);
  fadeIn(greenLed, 15);
  fadeOut(greenLed, 5);
  fadeInAll(15);
  fadeOutAll(5);
}

// Declare functions to fade LEDs in and out

int fadeIn(int color, int duration){ // declare the things that you want to change inside the parentheses 
  for(int fade=0; fade<=255; fade+=1){
        analogWrite(color, fade); // reuse the variables that you declared in the function call 
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

