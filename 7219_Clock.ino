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

int pm, hr, minut, sec, dur;           // for (col,row) addressing of pixels, frequency of screen updates (in milliseconds)



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

  dur=1000;
  hr=6;
  minut=19;
  sec=0;
  pm=0;       // 0 for am, 1 for pm
  randomSeed(analogRead(0));
}

void loop() 
{
  // put your main code here, to run repeatedly:
  //Blink colon once a second
  
  matrix.fillScreen(LOW);
 
  matrix.drawChar(0,0,char((hr/10%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(6,0,char((hr%10)+'0'),HIGH,LOW,1);
  matrix.drawPixel(12,2,HIGH);
  matrix.drawPixel(12,4,HIGH);
  matrix.drawChar(14,0,char((minut/10%10)+'0'),HIGH,LOW,1);
  matrix.drawChar(20,0,char((minut%10)+'0'),HIGH,LOW,1);
  if (pm%2) 
    matrix.drawChar(26,0,'P',HIGH,LOW,1);
  else
    matrix.drawChar(26,0,'A',HIGH,LOW,1);  
  matrix.write();
  delay(950);
  matrix.drawPixel(12,2,LOW);
  matrix.drawPixel(12,4,LOW);
  matrix.write();
  delay(45);      // 995 ms "dur" to make the clock more accurate
                  // clock lost 01:20 min. / 4:15 hrs with dur=1000ms
  sec++;
  if (sec==60)
  {
    sec=0;
    minut++;
  }
  if (minut==60)
  {
    minut=0;
    hr++;
  }
  if (hr>12)
  {
    hr=1;
    pm++;
  }
}
