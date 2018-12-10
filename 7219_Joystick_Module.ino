
/*
   8x32 MAX7219 / Joystick Station for UNO by Bill Jenkins
   V 1.0: Released 12/09/2018

   Hardware:
   Arduino UNO
   8x32 LED array with MAX7219
   Joystick module
   
   This sketch diplays a pixel in the center of the 8x32 array 
   and moves it around based on input from the joystick, 
   "Asteroids" style. 
 
*/

// Libraries for MAX7219
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//  Connection chart for 8x32 MAX7219 LED array
//  MAX7219[0]  UNO
//  ----------  ---
//  VCC         5V
//  GND         GND
//  DIN         D11
//  CS          D10
//  CLK         D13

// Stuff for 8x32 MAX7219 LED array
int pinCS = 10;     // CS line for 7219
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

//  Connections for Joystick module
//  Joystick    UNO
//  --------    ---
//  GND         Gnd
//  +5V         5v
//  VRx         A0
//  VRy         A1
//  SW          ---  // SW not used. Subject to revision. 

// Stuff for Joystick
int pinJoyXRead = 0; // Joystick x reading from A0
int pinJoyYRead = 1; // Joystick y reading from A1

// declare and set vars for I/O and delay time
int x = matrix.width()/2;   // Start position for x
int y = matrix.height()/2;  // Start position for y
int joyX, joyY;             // for X, Y readings from joystick
int dur = 100;              // screen refresh rate (in ms.)

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

void setup()
{
  // Configuration for MAX7219(s), with I/O pins at top left. 
  matrix.setIntensity(3); // Use a value between 0 and 15 for brightness
  matrix.setPosition(0, 0, 0); // The first display is at <0, 0>
  matrix.setPosition(1, 0, 1); 
  matrix.setPosition(2, 0, 2);
  matrix.setPosition(3, 0, 3);
  matrix.setRotation(0, 1);    // rotate 90 deg clockwise
  matrix.setRotation(1, 1);    // rotate 90 deg clockwise
  matrix.setRotation(2, 1);    // rotate 90 deg clockwise
  matrix.setRotation(3, 1);    // rotate 90 deg clockwise
  credit_screen("Move joystick to move dot.");
  delay(1000);
}

void loop()
{
  while (1)
  {
    //draw current pixel 
    matrix.drawPixel(x, y, HIGH);   
    matrix.write(); // Send bitmap to display
    delay(dur);

    // calculate new pixel position
    joyX = int(analogRead(pinJoyXRead)); // read joystick X
    joyY = int(analogRead(pinJoyYRead)); // read joystick Y
    if (joyX < 100) 
    {
      x--;
    }
    if (joyX > 900) 
    {
      x++;
    }
    if (joyY < 100) 
    {
      y++;
    }
    if (joyY > 900) 
    {
      y--;
    }
    
    // Adjust position of pixel on "Out of Bounds" condition.
    // Display wraps like the video game "Asteroids"
    if (y < 0)
    {
      y = matrix.height()-1;
    }
    if (y > matrix.height()-1) 
    {
      y = 0;
    }
    if (x < 0) 
    {
      x = matrix.width()-1;
    }
    if (x > matrix.width()-1) 
    {
      x = 0;
    }

    // Erase the screen
    matrix.fillScreen(LOW); 
    matrix.write();

  }
}
