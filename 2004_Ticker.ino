/* 
 * 2004 Ticker by Bill Jenkins
 * Rev 09/15/2018
 * Hardware: 2004A 20x4 character LCD Display with I2C backpack 
 *           SD Card Shield (Deek-Robot Data Loggong Shield V1.0)
 * This sketch reads from the file [datalog.txt] on the SD card
 * and displays four lines of text on the LCD display for four 
 * seconds, then repeats the process until the end of the file.
 * It repeats this action in a loop. Data file must be a 
 * multiple of 4 lines in length and no line xay exceed 
 * 20 chars. No error checking is done for these two parameters.
 * That's what you are for. :)
*/

#include <SPI.h>
#include <SD.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Deek-Robot Data Logging Shield v1.0
// SD card attached to SPI bus as follows:
// SD Card  UNO
// -------  ---
// MOSI     D11
// MISO     D12
// CLK      D13
// CS       D10 (for Deek-Robot SD Card Shield)

// 2004A LCD display with I2C backpack
//  2004    UNO
//  ----    ---
//  GND     Gnd
//  VCC     5v
//  SDA     A4
//  SCL     A5

File myFile;
int dur=4000;   // screen duration in milliseconds

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

// user function to write a string [linetext] to line 
// [linenum] of the display. Function expects a 
// <=20 character string. No error checking is performed.

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

  if (!SD.begin(10)) 
  {
    writeLine(0,"SD startup failed!");
    writeLine(1,"Make sure SD Card");
    writeLine(2,"is installed. ");
    while (1);
  }
  writeLine(0,"SD startup complete.");
  myFile = SD.open("datalog.txt",FILE_READ);
  if (myFile) 
  {
    writeLine(1,"datalog.txt opened");
    writeLine(2,"Starting ticker");
    delay(dur);
  }
  else 
  {
    // if the file didn't open, print an error:
    delay(dur);
    writeLine(0,"Error opening file  ");
    writeLine(1,"datalog.txt. Ensure ");
    writeLine(2,"SD Card is inserted ");
    writeLine(3,"& datalog.txt exists");
    while (1);      // loop forever
  }
}

void loop() 
{
  // clear LCD display
  lcd.clear();
  delay(50);
  int row,col;      // row and column for LCD display
  char thischar;    // current character  
  String linetext="                    ";  // current line text

  while (1)
  {
    row=0;
    col=0;
    linetext="                    ";
    while(myFile.available())
    {
      //read a character

      // if the character is not a newline character,
      // append the character to [linetext]
      thischar=myFile.read();
      if (isPrintable(thischar))  
      {
        linetext[col]=thischar;
        col++;
      }
      else
      {
        // print out current line, increment [row], 
        // set [col] back to zero
        // set [linetext] back to 20 spaces
        // if row==4, then display screen for [dur] milliseconds
        // set row=0, dump nonprintable character 
        // and continue
        writeLine(row, linetext);
        linetext="                    ";
        row++;
        col=0;
        if (row==4)
        {
          delay(dur);
          row=0;
        }
        thischar=myFile.read();   // dump extra character
      }
    }
    // close file and re-open it
    myFile.close();
    myFile = SD.open("datalog.txt",FILE_READ);
  }
}
