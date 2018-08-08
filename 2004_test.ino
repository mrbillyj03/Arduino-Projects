#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


//  connections
//  2004    UNO
//  ----    ---
//  GND     Gnd
//  VCC     5v
//  SDA     A4
//  SCL     A5


// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

int timer=5000;

// user function to write a string (linetext)to line (linenum) of the display 
// Function expects a 20 character string. No error checking is performed.

void writeLine(int linenum, String linetext) 
{
  lcd.setCursor(0,linenum);   // go to column 0 of line (linenum)
  lcd.print(linetext);        // write all 20 characters of line
}

void setup()
{
	// initialize the LCD
	lcd.begin();
  lcd.clear();
	lcd.backlight();
  delay(100);
}

void loop()
{
  lcd.clear();
  writeLine(0,"ExoticAroma Products");  // this is line 0
  writeLine(1,"Waxes, Lamps, & more");  // this is line 1
  writeLine(2,"  Establsihed 2013  ");  // this is line 2 
  writeLine(3,"    773-377-5504    ");  // this is line 3
  delay(timer);

  lcd.clear();
  writeLine(0,"ExoticAroma Products");  // this is line 0
  writeLine(1,"Small Wax.....$ 3.00");  // this is line 1
  writeLine(2,"Medium Wax....$ 7.00");  // this is line 2 
  writeLine(3,"Large Wax.....$ 9.00");  // this is line 3
  delay(timer);

  lcd.clear();
  writeLine(0,"ExoticAroma Products");  // this is line 0
  writeLine(1,"Small Lamps...$14-up");  // this is line 1
  writeLine(2,"Large Lamps...$30-up");  // this is line 2 
  writeLine(3,"Opportunities Avail.");  // this is line 3
  delay(timer);
}
