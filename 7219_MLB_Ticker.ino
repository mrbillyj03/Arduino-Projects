/* 7219 MLB Ticker v1.0 by Bill Jenkins
 *  Rev. 08/15/2018
 *  Hardware: 8x32 LED array with MAX7219
 *  This sketch scrolls the results of Major League Baseball games 
 *  played on 08/13/2018 in a loop
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


int wait = 40; // In milliseconds

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

void setup() {


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

// Boot Screen 
  test_screen();
  credit_screen("MLB Ticker v 1.0 by Bill Jenkins     ");
 }

void loop() 
{
   credit_screen("MLB Scores 08/13/2018     MIA 1, ATL 9     NYM 8, NYY 5     CWS 5, DET 9     CLE 10, CIN 3     MIA 1, ATL 6     ARI 3, TEX 5     WSH 6, STL 7     TOR 1, KC 3     SEA 6, OAK 7     LAA 6, SD 3     SF 5, LAD 2     ");
}

