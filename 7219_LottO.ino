/* 7219 LottO by Bill Jenkins
 *  Rev. 08/15/2018
 *  Hardware: 8x32 LED array with MAX7219
 *  This sketch simulates the Pick3 and Pick4 drawings 
 *  with Fireball and displays the results
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

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

int x,y, dur;           // for (col,row) addressing of pixels, frequency of screen updates (in milliseconds)
int frameswitch;      // 
long dat;

void setup() 
{
  // put your setup code here, to run once:
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

  matrix.fillScreen(HIGH);
  matrix.write();
  delay(500);
  matrix.fillScreen(LOW);
  matrix.write();
  delay(500);

  dur=1000;

  randomSeed(analogRead(0));
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //Pick 3
  dat=long(random(0,100000));
  matrix.fillScreen(LOW);
  matrix.drawChar(0,0,'P',HIGH,LOW,1);
  matrix.drawChar(6,0,'i',HIGH,LOW,1);
  matrix.drawChar(12,0,'c',HIGH,LOW,1);
  matrix.drawChar(18,0,'k',HIGH,LOW,1);
  matrix.drawChar(26,0,'3',HIGH,LOW,1);
  matrix.write();
  delay(dur);
  matrix.fillScreen(LOW);
  matrix.drawChar(6,0,char((dat/1000%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(12,0,char((dat/100%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(18,0,char((dat/10%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(26,0,char((dat%10)+'0'),HIGH,LOW,1);
  for(y=0;y<matrix.height(); y++)
  {
    matrix.drawPixel(24,y,HIGH);
  }
  matrix.write();
  delay(2*dur);
  
  //Pick 4
  dat=long(random(0,100000));
  matrix.fillScreen(LOW);
  matrix.drawChar(0,0,'P',HIGH,LOW,1);
  matrix.drawChar(6,0,'i',HIGH,LOW,1);
  matrix.drawChar(12,0,'c',HIGH,LOW,1);
  matrix.drawChar(18,0,'k',HIGH,LOW,1);
  matrix.drawChar(26,0,'4',HIGH,LOW,1);
  matrix.write();
  delay(dur);
  matrix.fillScreen(LOW);
  matrix.drawChar(0,0,char((dat/10000%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(6,0,char((dat/1000%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(12,0,char((dat/100%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(18,0,char((dat/10%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(26,0,char((dat%10)+'0'),HIGH,LOW,1);
  for(y=0;y<matrix.height(); y++)
  {
    matrix.drawPixel(24,y,HIGH);
  }
  matrix.write();
  delay(2*dur);
  
}
