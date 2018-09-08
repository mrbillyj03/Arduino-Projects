/* 2004 Sports Ticker by Bill Jenkins
 * Rev 08/16/2018
 * Hardware: 2004A 20x4 character LCD Display with I2C backpack 
 * This sketch lists scores from yesterday's sports games 
 * for all sports currently in season
 * Order:
 * MLB Scores
 * NBA Scores
 * NFL Scores
 * NHL Scores
 * 
 */
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

  // Boot Screen
  writeLine(0,"   Sports Ticker    ");  // this is line 0
  writeLine(1,"   by Bill Jenkins  ");  // this is line 1
  writeLine(2," BJ+VJ Enterprises  ");  // this is line 2 
  writeLine(3," Revised 09/07/2018 ");  // this is line 3
  delay(2000);
}

void loop()
{
  String linetext[26];
// Text Strings for screen
//linetext[0]="12345678901234567890";
  linetext[0]="MajorLeague Baseball";
  linetext[1]=" Scores 09/06/2018  ";
  linetext[2]="Padres             6";
  linetext[3]="Reds               2";
  linetext[4]="Cubs               6";
  linetext[5]="Nationals          4";
  linetext[6]="Indians            9";
  linetext[7]="Blue Jays          4";
  linetext[8]="Braves             7";
  linetext[9]="Diamondbacks       6";

  linetext[10]=" AL East Standings  ";    //start standings
  linetext[11]="Team          W   L ";
  linetext[12]="Red Sox       97  44";
  linetext[13]="Yankees       87  53";
  linetext[14]="Rays          75  64";
  linetext[15]="Blue Jays     63  77";
  linetext[16]="Orioles       41  99";  
  linetext[17]="--------------------";

  linetext[18]="AL Central Standings";
  linetext[19]="Team          W   L ";
  linetext[20]="Indians       80  60";
  linetext[21]="Twins         63  76";
  linetext[22]="Tigers        57  83";
  linetext[23]="White Sox     56  84";
  linetext[24]="Royals        46  93";
  linetext[25]="--------------------";
/*
  linetext[26]=" AL West Standings  ";
  linetext[27]="Team          W   L ";
  linetext[28]="Astros        87  53";
  linetext[29]="Athletics     84  57";
  linetext[30]="Mariners      78  62";
  linetext[31]="Angels        68  72";
  linetext[32]="Rangers       61  79";
  linetext[33]="--------------------";

  linetext[34]=" NL East Standings  ";
  linetext[35]="Team          W   L ";
  linetext[36]="Braves        77  63";
  linetext[37]="Phillies      73  66";
  linetext[38]="Nationals     69  72";
  linetext[39]="Mets          63  76";
  linetext[40]="Marlins       56  84";
  linetext[41]="--------------------";

  linetext[42]="NL Central Standings";
  linetext[43]="Team          W   L ";
  linetext[44]="Cubs          83  57";
  linetext[45]="Brewers       79  62";
  linetext[46]="Cardinals     78  62";
  linetext[47]="Pirates       69  71";
  linetext[48]="Reds          59  82";
  linetext[49]="--------------------";

  linetext[50]=" NL West Standings  ";
  linetext[51]="Team          W   L ";
  linetext[52]="Rockies       77  62";
  linetext[53]="Dodgers       76  64";
  linetext[54]="Diamondbacks  75  65";
  linetext[55]="Giants        68  73";
  linetext[56]="Padres        56  86";
  linetext[57]="--------------------";
*/
  while (1)
  {
    
    for (int lineno=2; lineno<26; lineno+=2)  // last line with scores goes in 2nd position
    {
      lcd.clear();
      writeLine(0,linetext[0]); 
      writeLine(1,linetext[1]); 
      writeLine(2,linetext[lineno]); // Team name, inning, score
      writeLine(3,linetext[lineno+1]); // Team name, inning, score
      delay(4000);
    }
  }
}
