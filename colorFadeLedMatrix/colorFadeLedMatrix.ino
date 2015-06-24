#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  Serial.begin(9600);
  matrix.begin();
}

void loop() {
  fadeInFill();
}

void fadeInFill(){
  int randomRed = random(1,4);
  int randomGreen = random(1,4);
  int randomBlue = random(1,4);
  int fadeDelay = 80;
  int pauseDelay = 120;
  
  for(int i = 0; i <= 7; i++){
    if(i == 7){
      for (int j = 7; j > -1; j--){
        matrix.fillRect(0, 0, 32, 16, matrix.Color333(randomRed, j, randomBlue));
        if(j == 4){
          delay(pauseDelay);
        } else if (j == 0){
          matrix.fillRect(0, 0, 32, 16, matrix.Color333(1, 1, 1));
          delay(pauseDelay); 
        } else {
          delay(fadeDelay); 
        }
      } 
      break;
    } else {
      matrix.fillRect(0, 0, 32, 16, matrix.Color333(randomRed, i, randomBlue));
      if(i == 4){
        delay(pauseDelay);
      } else{
        delay(fadeDelay);
      } 
    }
  }
}
