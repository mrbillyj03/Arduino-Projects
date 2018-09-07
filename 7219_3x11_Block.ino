/*
 * 7219 3x11 Blocks by Bill Jenkins
 * Rev. 08/25/2018
 * Hardware - 8x32 LED array with MAX7219
 * This sketch diplays static on the 8x32 LED array to simulate a movie prop for space equipment monitoring
 * and refreshes the screen at an interval of 25 frames/sec.
 * 08/25/2018 - Added feature to set refresh rate with 10k pot
 * instead of from a variable
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//  Connection chart for 8x32 LED array
//  MAX7219[0]  UNO
//  ----------  ---
//  VCC         5V
//  GND         GND
//  DIN         D11 (MOSI)
//  CS          D10 
//  CLK         D13 (SCK)

//  Connection chart for 10k potentiometer for analogRead
//  from pin A2. D2 is set high to provide +5V to the pot. 
//  10k pot   UNO
//  -------   ---
//  (+)       D2
//  (Wiper)   A2
//  (-)       GND

// declare variables for I/O pins
const int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
const int pinVolt=2;  // set D2 high for +5V to pot
const int pinRead=2;  // read voltage from pot wiper at A2

// declare display parameters     
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;


// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

// Scrolls the text stored in the string tape. 
void credit_screen(String tape)      // Scroll Title, Author
{
  int spacer = 1;
  int width = 5 + spacer; // The font width is 5 pixels
  String tape_sac="Arduino";      // This puts Mr. Smiley and Ms. Heart in jail
  
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

  // sends +5V to (+) lead of pot
  pinMode(pinVolt,OUTPUT);
  digitalWrite(pinVolt,HIGH);
  randomSeed(analogRead(A0));
  // Boot screen
  credit_screen("3x11 Blocks");
}

void loop() 
{
  int x,y;            // for (col,row) addressing of pixels, frequency of screen updates (in milliseconds)
  int dur;            // dur determines refresh rate
  float frameswitch;  // % probability of a given pixel being HIGH
                      // in any given frame
  while (1)
  {
    dur=int(analogRead(pinRead)*2);       // set refresh rate
    matrix.fillScreen(LOW);               // clear screen
    frameswitch=float(random(0,101));
    for (y=0; y<matrix.height(); y+=3)    // row level stuff   
    {                                           
      for (x=0; x<matrix.width(); x+=3)   // pixel level stuff
      {
        if (float(random(0,101)<frameswitch))
        {
          matrix.drawPixel(x,y,HIGH);     
          matrix.drawPixel(x,y+1,HIGH);     
          matrix.drawPixel(x+1,y,HIGH);     
          matrix.drawPixel(x+1,y+1,HIGH);     
        }
      }
    }  
    matrix.write();
    delay(dur);
  }
}
