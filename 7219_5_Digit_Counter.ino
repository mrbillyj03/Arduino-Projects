/* 7219 5 Digit Counter by Bill Jenkins
 *  Rev. 09/08/2018
 *  Hardware: 8x32 LED array with MAX7219
 *            10k potentiometer
 *  This sketch counts from 0 to 99999 in a loop
 *  at a rate determined by reading from a 10k pot
*/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

//  Connection chart for MAX7219 8x8 or 8x32 LED array
//  MAX7219[0]  UNO
//  ----------  ---
//  VCC         5V
//  GND         GND
//  DIN         D11 (MOSI)
//  CS          D10 (SS)
//  CLK         D13 (SCK)

//  Connection chart for 10k potentiometer for analogRead
//  from pin A2. This determines the refresh rate. D2 is set
//  high to provide +5V to the pot. 
//  10k pot   UNO
//  -------   ---
//  (+)       D2      // set D2 HIGH for +5V to pot
//  (Wiper)   A2      // reading taken from A2
//  (-)       GND

int pin5V=2;        // set high, D2 delivers +5 to pot
int pinRead=2;      // pot wiper goes to A2, readings  
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void credit_screen()      // Scroll Title, Author
{
  int spacer = 1;
  int width = 5 + spacer; // The font width is 5 pixels

  String tape_sac="Arduino";
  String tape="5 Digit Counter";
     
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

  pinMode(pin5V,OUTPUT);      // D2 set HIGH, provides +5V to pot
  digitalWrite(pin5V,HIGH);

  randomSeed(analogRead(0));
  credit_screen();
}

void loop() 
{
  int dur;        // for screen refresh rate 
  long dat=0;     // counter value
  while (1)
  {
    dur=int(analogRead(pinRead));   // read pot for delay time
    matrix.fillScreen(LOW);         // clear display

// uncomment this section and delete other section for no leading zeros
//  if (dat>9999) matrix.drawChar(1,0,char((dat/10000%10)+'0'),HIGH,LOW,1);
//  if (dat>999) matrix.drawChar(7,0,char((dat/1000%10)+'0'),HIGH,LOW,1);
//  if (dat>99) matrix.drawChar(13,0,char((dat/100%10)+'0'),HIGH,LOW,1);
//  if (dat>9) matrix.drawChar(19,0,char((dat/10%10)+'0'),HIGH,LOW,1);

//  this section is for leading zeros
    matrix.drawChar(1,0,char((dat/10000%10)+'0'),HIGH,LOW,1);
    matrix.drawChar(7,0,char((dat/1000%10)+'0'),HIGH,LOW,1);
    matrix.drawChar(13,0,char((dat/100%10)+'0'),HIGH,LOW,1);
    matrix.drawChar(19,0,char((dat/10%10)+'0'),HIGH,LOW,1);
    matrix.drawChar(25,0,char((dat%10)+'0'),HIGH,LOW,1);
    matrix.write();
    
    delay(2*dur);
    dat++;
    if (dat==100000) dat=0;   // reset counter once it reaches 100000
   }
}
