/* HOLIDAY STAR SKETCH 
   Dec 2013 - Justin Smith
   Developed for Hack Yourself a Merry Little Xmas - Critical Mass, Chicago
   
   PARTS:
     Tri-Color Breakout Board - https://www.sparkfun.com/products/11588
     Arduino (any flavor)
   
   Hookup:
     Tri-color to 5v, Ground, and pins 3, 5, 6
*/

// Declare your variables that won't change
int redLed = 3; // Declare the pins that you're plugging the LED leads into
int greenLed = 5; // We use pins 3, 5, and 6 because they are Pulse Width Modulation (PWM) pins
int blueLed = 6; // PWM pins are denoted by a "~" on the board, and can send values between 0 and 255

// Run the setup loop
void setup()  { 
  pinMode(redLed, OUTPUT); // Tell the code what the pins that you described need to do (input or output) 
  pinMode(greenLed, OUTPUT);   
  pinMode(blueLed, OUTPUT);   
} 

// Run the code
void loop()  {
  // Call a custom function that we declare below to keep code concise
  fadeIn(redLed, 15); // This function call is saying "fade in the red led for 15 milliseconds
  fadeOut(redLed, 5);
  fadeIn(greenLed, 15);
  fadeOut(greenLed, 5);
  fadeInAll(15);
  fadeOutAll(5);
}

// Declare functions to fade LEDs in and out

int fadeIn(int color, int duration){ // declare the things that you want to change inside the parentheses 
  for(int fade=0; fade<=255; fade+=1){ // A for loop sets a variable and adds 1 to the number until it reaches the top limit
        analogWrite(color, fade); // write the value of fade to the specified pin 
        delay(duration); // wait a few milliseconds before incrementing the for loop
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

