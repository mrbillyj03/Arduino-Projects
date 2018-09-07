/* 
 * 7219 Clock by Bill Jenkins
 * Rev 08/15/2018
 * Hardware: 8x32 LED array with MAX7219
 * This sketch turns the MAX7219 array into a clock in 12-hour 
 * format with lowercase AM/PM indicator. Colon flashes at 1 Hz. 
 * Rev 08/16/2018
 * Fixed AM/PM bug, changed uppercase AM/PM indicator to 
 * lowercase. Improved accuracy by subtracting 5 msec 
 * from loop time. Clock is now accurate to within 
 * several seconds a day.
 * Rev. 09/07/2018
 * Eliminated leading '0' on hour display if hr<10
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

// Hardware specific parameters
int pinCS = 10; // Attach CS to this pin, DIN to MOSI and CLK to SCK (cf http://arduino.cc/en/Reference/SPI )
int numberOfHorizontalDisplays = 4;
int numberOfVerticalDisplays = 1;

// declare instance of screen
Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

void setup() 
{
  matrix.setIntensity(2); // Use a value between 0 and 15 for brightness

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

void loop() 
{
  int hr=3;       // initial time settings go here
  int minut=8;   
  int sec=0;
  int pm=1;       // even for am, odd for pm
 
  while (1)       // this part loops forever
  {
    // Blink colon once a second, update time every 60 seconds
    // clear screen
    matrix.fillScreen(LOW);     
    // draw hours
    if (hr>9) matrix.drawChar(0,0,char((hr/10%10)+'0'),HIGH,LOW,1); 
    matrix.drawChar(6,0,char((hr%10)+'0'),HIGH,LOW,1);
    // draw colon 
    matrix.drawPixel(12,2,HIGH);    
    matrix.drawPixel(12,4,HIGH);
    // draw minutes
    matrix.drawChar(14,0,char((minut/10%10)+'0'),HIGH,LOW,1); 
    matrix.drawChar(20,0,char((minut%10)+'0'),HIGH,LOW,1);
    // draw am/pm indicator
    if (pm%2) matrix.drawChar(27,0,'p',HIGH,LOW,1);
    else matrix.drawChar(27,0,'a',HIGH,LOW,1);  
    // draw screen
    matrix.write();
    delay(900);
    // turn colon off 
    matrix.drawPixel(12,2,LOW);   
    matrix.drawPixel(12,4,LOW);
    // draw screen
    matrix.write();
    delay(95);      // 995 ms "dur" to make the clock more accurate
    sec++;          // calls to write to the 7219 take about 5 msec.
    if (sec==60)    // set seconds back to zero, increment minute
    {
      sec=0;
      minut++;
    }
    if (minut==60)  // set minutes back to zero, increment hours
    {
      minut=0;
      hr++;
    }
    if (hr==12 && minut==0 && sec==0)pm++;    // at 12:00:00, toggle am/pm indicator
    if (hr==13)hr=1;                          // set hr back to 1
  }
}
