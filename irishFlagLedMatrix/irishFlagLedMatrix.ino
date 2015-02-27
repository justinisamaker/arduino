// Draw an Irish flag line by line on a 32x16 LED matrix

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
  matrix.begin();
}

void loop() {
  scanLine();
  removeScan();
}

void scanLine(){
  int y = 0;
  while(y <= 16){
    for(int x = 0; x <= 32; x++){
//      int randomRed = random(0,3);
//      int randomGreen = random(0,3);
//      int randomBlue = random(0,3);
//      matrix.drawPixel(x, y, matrix.Color333(randomRed, randomGreen, randomBlue));
      if(x >= 0 && x <= 9){
        matrix.drawPixel(x, y, matrix.Color333(0,3,0));
      } else if (x >= 10 && x<= 20){
        matrix.drawPixel(x, y, matrix.Color333(1, 1, 1));
      } else {
        matrix.drawPixel(x, y, matrix.Color333(2, 1, 0));
      }
      delay(10);
    }
    y++;
  }
}

void removeScan(){
  int y = 16;
  while(y > -1){
    for(int x = 32; x > -1; x--){
      matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));
      delay(5);
    }
    y--;
  }
}
