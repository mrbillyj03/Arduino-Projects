/*
 * 7219 Static by Bill Jenkins
 * Rev. 08/25/2018
 * Hardware - MAX7219 8x32 LED array 
 *            10k potentiometer
 * This sketch uses random numbers to generate "static" 
 * on the 8x32 LED array to create a movie prop for 
 * a space equipment monitoring display and refreshes 
 * the screen at an interval of up tp 2 sec. set by 
 * reading from a 10k pot. 
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

//  Connection chart for 10k potentiometer for analogRead
//  10k pot UNO
//  ------- ---
//  (+)     D2
//  (Wiper) A2
//  (-)     GND

const int pinCS=10;   // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
const int pinVolt=2;  // D2 sends +5V to pot
const int pinRead=2;  // Wiper goes to A2                  

// set display parameters. this is for a 7219 8x32 LED matrix
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);


// Function to scroll the text in the string passed to it 
// across the screen from right to left one time.  

void credit_screen(String tape)      // Scroll Title, Author
{
  int spacer = 1;
  int width = 5 + spacer; // The font width is 5 pixels
  String tape_sac="Arduino";    // This puts Mr. Smiley and Ms. Heart in jail

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

void setup() {

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

  pinMode(pinVolt, OUTPUT);   // Set pin D2 high for +5V to pot
  digitalWrite(pinVolt, HIGH);
  credit_screen("Static");    // Boot screen
  randomSeed(analogRead(0));  // Set new random sequence each run
}

void loop() 
{
  int x,y;    // for (col,row) addressing of pixels 
  int dur;    // frequency of screen updates (in milliseconds)
  while (1)
  {
    dur=int(analogRead(pinRead)*2);     // read pot for frame rate
    matrix.fillScreen(LOW);             // clear screen
    for (y=0; y<matrix.height(); y++)   // row level stuff   
    {                                           
      for (x=0; x<matrix.width(); x++)  // pixel level stuff
      { 
        if (int(random(0,101))<50)      // we want approx. 50%
        matrix.drawPixel(x,y,HIGH);     // pixels each frame
      }
    }  
    matrix.write();
    delay(dur);
  }
}
