 /*
 
 Project 29 - 
Shawn Decker
  
Print out a series of words from an array of strings using an external LCD.
  
  
  The circuit:
  * LCD RS pin to digital pin 12
  * LCD Enable pin to digital pin 11
  * LCD D4 pin to digital pin 5
  * LCD D5 pin to digital pin 4
  * LCD D6 pin to digital pin 3
  * LCD D7 pin to digital pin 2
  * 10K resistor:
  * ends to +5V and ground
  * wiper to LCD VO pin (pin 3)
  

  */
  
 // include the library code:
 #include <LiquidCrystal.h>

 // initialize the library with the numbers of the interface pins
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
 //  initialize an array of strings - this array contains pointers to 
 //  each string (* is the C symbol for a pointer)
 //  this is a bit esoteric - and probably you wont complete get this, 
 //  but you should be able to copy the code and use it without fully getting 
 //  the details of the mechanics.....
 
// char*  FTW[] = { 
String lineOne = "There is only";
String lineTwo = "30 more days";  
String lineThree = "of this stuff!";
//    "Keep on going!",
//    "Do it now!", 
//    "22 if you",
//    "only count",
//    "weekdays!"
// };
 
 #define NUMLINES   7

 void setup(){
     
   lcd.begin(16, 2);     // set up the LCD's number of rows and columns:

 }

 void loop()
 {
String numberChars;
     int i;    //   var for looping
     
     // clear the screen
     lcd.clear();
     
     // loop through each string in array
//     
//     for (i=0;i<NUMLINES;i++) {
//       // clear the screen for each new line
       lcd.clear();
       delay(500);
       // display each line on the LCD
       lcd.print(lineOne + " " + lineTwo);
       delay(1000);   //wait 5 seconds.
       numberChars = lineOne.length();
       lcd.print(numberChars);
       lcd.clear();
       lcd.print(lineTwo);
       delay(1000);
       lcd.clear();
       lcd.print(lineThree);
       delay(1000);
       lcd.clear();
       
 //    }
     
     delay(5000);      //  after full text - wait an extra 5 seconds....
     
  
                         //  then repeat....
 }

