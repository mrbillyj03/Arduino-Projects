
/*
 * 7219 Heart Monitor by Bill Jenkins
 * Rev. 08/12/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch simulates a heart monitor or oscilloscope using randomly generated data. 
 * Use a sensor to set Y value if you want to do some actual (imprecise) measurement
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//  Connection chart for 8x32 LED array
//  MAX7219[0]  UNO
//  ----------  ---
//  VCC         5V
//  GND         GND
//  DIN         D11   MOSI
//  CS          D10   pinCS
//  CLK         D13   SCK

int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int x,y;                // for (col,row) addressing of pixels
int dur=50;             // for frequency of screen updates (in milliseconds)
int pix_y=int(matrix.height()/2.0);          // light up column pix_x, row pix_y
int lastval=0;
int no_move=0;

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

  // heart beat
  matrix.drawChar(13,0,char(0x03), HIGH, LOW, 1);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  matrix.write();
  delay(500);
  matrix.drawChar(13,0,char(0x03), HIGH, LOW, 1);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  matrix.write();
  delay(500);
  matrix.drawChar(13,0,char(0x03), HIGH, LOW, 1);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  matrix.write();
  delay(500);
     
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

  matrix.fillScreen(LOW);

  test_screen();                // Boot Screen 
  credit_screen("Heart Monitor v 1.3 by Bill Jenkins");
  
  randomSeed(analogRead(0));
}

void loop() 
{
  matrix.fillScreen(LOW); 
  for (x=0; x<matrix.width(); x++)
  {
    pix_y+=int(random(0,5)-2.0);
    if (pix_y<0) pix_y=0;
    if (pix_y>=matrix.height()) pix_y=matrix.height()-1;
    if (int(lastval)==int(pix_y)) 
    {
      no_move++;
    }
    else
      no_move=0;
    if (no_move<5)    
    // no flatline condition, draw normal
    {
      matrix.drawPixel(x,7-pix_y,HIGH); 
      // draw pixel for this column
    }
    else              
    // flatline, draw data in dark on light background for column
    {
      for (y=0; y<matrix.height();y++)
      {
        matrix.drawPixel(x,y,HIGH);  
      }
      matrix.drawPixel(x,7-pix_y,LOW);
    }
    lastval=int(pix_y);
    
    matrix.write();                     // do not clear screen
    delay(dur);
  }
 }


