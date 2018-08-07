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

String tape_sacrifice="Arduino";
String tape="MLB Scores 08/05/2018     ATL 5, NYM 4     CWS 8, TB 7     LAA 3, CLE 4     CIN 1, WSH 2     MIA 3, PHI 5     STL 2, PIT 1     COL 5, MIL 4     KC 5, MIN 6     SD 10, CHC 6     BAL 9, TEX 6     DET 0, OAK 6      DET 0, OAK 6     HOU 2, LAD 3     SF 3, ARI 2    TOR 3, SEA 6     NYY 4, BOS 5     ";
int wait = 40; // In milliseconds

int spacer = 1;
int width = 5 + spacer; // The font width is 5 pixels

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
}

void loop() {


  for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {

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

    delay(wait);
  }
}

