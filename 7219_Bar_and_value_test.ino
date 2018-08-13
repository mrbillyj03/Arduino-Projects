/*
 * 7219 3-input Status Monitor v 1.0 by Bill Jenkins
 * Rev. 08/13/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch is a 3-input status monitor, showing a "fuel tank" and digital readout for each.
 * The values displayed range from 0-8. 
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

// set pin and matrix parameters

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);



int x,y,wid;           // for (col,row) addressing of pixels, wid is number of columns apart for bars - do not change, 
float pix[32];         // variables for determining whether a pixel is filled in or not

void credit_screen(String tape)      // Scroll Title, Author
{
  int spacer = 1;
  int width = 5 + spacer; // The font width is 5 pixels

  String tape_sac="Arduino";
 
    
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

void test_screen()
{
  matrix.fillScreen(HIGH);
  matrix.drawChar(4,1,'T',LOW,HIGH,1);
  matrix.drawChar(10,1,'E',LOW,HIGH,1);
  matrix.drawChar(16,1,'S',LOW,HIGH,1);
  matrix.drawChar(22,1,'T',LOW,HIGH,1);
  matrix.write();
  delay(500);
  matrix.fillScreen(HIGH);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  matrix.drawChar(4,0,'P',HIGH,LOW,1);
  matrix.drawChar(10,0,'A',HIGH,LOW,1);
  matrix.drawChar(16,0,'S',HIGH,LOW,1);
  matrix.drawChar(22,0,'S',HIGH,LOW,1);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  delay(500);
}

void setup() 
{

  matrix.setIntensity(5); // Use a value between 0 and 15 for brightness

  // Adjust to your own needs
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 0, 1);
  matrix.setPosition(2, 0, 2);
  matrix.setPosition(3, 0, 3);

  matrix.setRotation(0, 1);    // rotate 90 deg clockwise
  matrix.setRotation(1, 1);    // rotate 90 deg clockwise
  matrix.setRotation(2, 1);    // rotate 90 deg clockwise
  matrix.setRotation(3, 1);    // rotate 90 deg clockwise

// Boot Screen 
  test_screen();
  credit_screen("3-input Status Monitor v 1.0 by Bill Jenkins");

  randomSeed(analogRead(0));      // set random seed for random display, or you can feed data values to each instance of pix[]
  
   for (x=0;x<32;x++)  // set height of all bands = 4 pixels initially 
  {
    pix[x]=4.0;
  }
}

void loop() 
{

  matrix.fillScreen(LOW);         // clear screen
 
  for (x=0; x<matrix.width(); x+=11)       // column level stuff goes here
  {                                          
    // calculate increment of bar for band, it will be [-1, 0 or 1]
    pix[x]=pix[x]+((random(0,32)-15.5)/16.0);    // calculate new bar height
    if (pix[x]<0) pix[x]=0;                 // correct bar height if it's too short
    if (pix[x]>matrix.height()) pix[x]=matrix.height();       // correct bar height if it's too tall

    for (y=0;y<matrix.height();y++)             // pixel level stuff goes here
    {
      if (int(pix[x])>y)               // if true, set pixel HIGH
      {
        matrix.drawPixel(x,7-y,HIGH);     // bars are three pixls wide. y pixels start with y[0] at the top and y[7] at the bottom
        matrix.drawPixel(x+1,7-y,HIGH);   // flipping the write location keeps them in proper graph format
        matrix.drawPixel(x+2,7-y,HIGH);   // flipping the write location keeps them in proper graph format
      }
      matrix.drawChar(x+4,0,char(int('0')+int(pix[x])),HIGH,LOW,1);   // draw bar and print value of pix[x]. 
   }
 }  
 matrix.write();
 delay(300);
}
