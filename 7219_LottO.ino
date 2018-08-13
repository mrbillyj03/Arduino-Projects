/*
 * 7219 LottO by Bill Jenkins
 * Rev. 08/10/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch simulated the output of 3 status monitors with a vertical fuel gauge and a digital readout for each
 * random data is generated and displayed every 2 seconds
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


// variables for drawing the graph. The value of wid determines the number of bands displayed.
// each bar is two pixels wide. 

int x,y,wid;                // for (col,row) addressing of pixels, wid is number of columns apart for bars - do not change this
float pix[32];                 // variable for determining whether a pixel is filled in or not

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
  credit_screen("LottO v 1.0 by Bill Jenkins");

  randomSeed(analogRead(0));      // set random seed for random display, or you can feed data values to each instance of pix[]
  wid=11;              // do not change
 }

void loop() 
{

  matrix.fillScreen(LOW);         // clear screen
 
  for (x=0; x<matrix.width(); x+=wid)     // column level stuff goes here
  {                                          
    pix[x]=random(0,9);                   // create bar
    for (y=0;y<matrix.height();y++)       // pixel level stuff goes here
    {
      if (int(pix[x])>y)                  // if true, set pixel HIGH
      {
        matrix.drawPixel(x,7-y,HIGH);     // bars are two pixls wide. y pixels start with y[0] at the top and y[7] at the bottom
        matrix.drawPixel(x+1,7-y,HIGH);   // flipping the write location keeps them in proper graph format
        matrix.drawPixel(x+2,7-y,HIGH);   // flipping the write location keeps them in proper graph format
      }
      matrix.drawChar(x+4,0,char(int('0')+int(pix[x])),HIGH,LOW,1);   // draw char for integer value corresponding to bar height in pixels
   }
 }  
 matrix.write();
 delay(2000);
}

