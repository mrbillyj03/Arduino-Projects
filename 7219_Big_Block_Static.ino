/*
 * 7219 Big Block Static by Bill Jenkins
 * Rev. 08/10/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch diplays 4x4 blocks on the 8x32 LED array 
 * to simulate a movie prop for space equipment monitoring
 * and refreshes the screen at an interval of 1 sec.
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//  Connection chart for 8x32 LED array
//  MAX7219[0]  UNO
//  ----------  ---
//  VCC         5V
//  GND         GND
//  DIN         D11
//  CS          D10
//  CLK         D13

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void credit_screen()      // Scroll Title, Author
{
  int spacer = 1;
  int width = 5 + spacer; // The font width is 5 pixels

  String tape_sac="Arduino";    // This puts Mr. Smiley and Ms. Heart in jail
  String tape="Big Block Static"; 
     
  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) 
  {
    matrix.fillScreen(LOW);
    int letter = i / width;
    int x = (matrix.width() - 1) - i % width;
    int y = (matrix.height() - 8) / 2; // center the text vertically
    while ( x + width - spacer >= 0 && letter >= 0 ) 
    {
      if ( letter < tape.length() ) 
      {
        matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
      }
      letter--;
      x -= width;
    }
    matrix.write(); // Send bitmap to display
    delay(40);
  }
}

void setup() 
{
  matrix.setIntensity(3); // Use a value between 0 and 15 for brightness

  // Adjust to your own needs
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 0, 1);
  matrix.setPosition(2, 0, 2);
  matrix.setPosition(3, 0, 3);
  //  ...
  matrix.setRotation(0, 1);    // rotate 90 deg clockwise
  matrix.setRotation(1, 1);    // rotate 90 deg clockwise
  matrix.setRotation(2, 1);    // rotate 90 deg clockwise
  matrix.setRotation(3, 1);    // rotate 90 deg clockwise
  
  credit_screen();             // Boot Screen 

  randomSeed(analogRead(0));
}

void loop() 
{
  int x,y;            // for (col,row) addressing of pixels
  int dur=1000;       // frequency of screen updates (in milliseconds)
  float frameswitch;  // probability of a given block lighting in a given frame

  while (1)
  {
    matrix.fillScreen(LOW);               // clear screen
    frameswitch=float(random(0,101));

    for (y=0; y<matrix.height(); y+=4)     // row level stuff   
    {                                           
      for (x=0; x<matrix.width(); x+=4)    // pixel level stuff
      {
        if (float(random(0,101)<frameswitch))
        {
          matrix.drawPixel(x,y,HIGH);     
          matrix.drawPixel(x,y+1,HIGH);     
          matrix.drawPixel(x,y+2,HIGH);     
          matrix.drawPixel(x,y+3,HIGH);     
          matrix.drawPixel(x+1,y,HIGH);     
          matrix.drawPixel(x+1,y+1,HIGH);     
          matrix.drawPixel(x+1,y+2,HIGH);     
          matrix.drawPixel(x+1,y+3,HIGH);     
          matrix.drawPixel(x+2,y,HIGH);     
          matrix.drawPixel(x+2,y+1,HIGH);     
          matrix.drawPixel(x+2,y+2,HIGH);     
          matrix.drawPixel(x+2,y+3,HIGH);     
          matrix.drawPixel(x+3,y,HIGH);     
          matrix.drawPixel(x+3,y+1,HIGH);     
          matrix.drawPixel(x+3,y+2,HIGH);     
          matrix.drawPixel(x+3,y+3,HIGH);     
        }
      }
    }  
    matrix.write();
    delay(dur);
  }
}

