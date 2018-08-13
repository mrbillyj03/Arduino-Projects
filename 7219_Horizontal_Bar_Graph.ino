/*
 * 7219 Horizontal Bar Graph by Bill Jenkins
 * Rev. 08/10/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch simulates the output of multiple status monitors
 * The number of bars is set by adjusting the value of the wid parameter - see below
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

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);



int x,y, wid;              // for (col,row) addressing of pixels, and distance between bars
float pix[8], adj;         // variables for determining whether a pixel is filled in or not



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

    while ( x + width - spacer >= 0 && letter >= 0 ) {
      if ( letter < tape.length() ) {
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

  matrix.setIntensity(7); // Use a value between 0 and 15 for brightness

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

// set number of bands by adjusting the value of wid
  // wid value  # bands
  //    2         4
  //    3         3
  //    4         2

  wid=3;
  randomSeed(analogRead(0));
  for (x=0;x<8;x++)
  {
    pix[x]=16.0;
  }

// Boot Screen 

  test_screen();
  credit_screen("Horizontal Bar Graph v 1.0 by Bill Jenkins");
}

void loop() 
{

  matrix.fillScreen(LOW);       // clear screen

// Pixel level operations happen here
 
//for (x=0; x<matrix.width(); x++)
//for (y=0; y<matrix.height(); y++)
 
  for (y=0; y<matrix.height(); y+=wid)
  // Pixel level stuff
  
  {                                           
    adj=(random(0,32)-15.5)/16.0;
    pix[y]+=adj;
    if (pix[y]<0) pix[y]=0;
    if (pix[y]>32) pix[y]=32;

    for (x=0;x<matrix.width();x++)
    {
      if (pix[y]>x)
      {
        matrix.drawPixel(x,y,HIGH);         //bars are two pixels wide
        matrix.drawPixel(x,y+1,HIGH);
      }
   }
 }  
 matrix.write();
 delay(80);
}

