/* 2004 Sports Ticker by Bill Jenkins
 * Rev 09/07/2018
 * Hardware: 2004A 20x4 character LCD Display with I2C backpack 
 * This sketch lists scores from yesterday's MLB games 
 * and current standings
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
  int dur=4000;

  while (1)
  {
    lcd.clear();
    writeLine(0,"MajorLeague Baseball");
    writeLine(1," Scores 09/06/2018  ");
    writeLine(2,"Padres             6");
    writeLine(3,"Reds               2");
    delay(dur);

    writeLine(2,"Cubs               6");
    writeLine(3,"Nationals          4");
    delay(dur);
 
    writeLine(2,"Braves             7");
    writeLine(3,"Diamondbacks       6");
    delay(dur);

    writeLine(1,"Standings 09/06/2018");
    writeLine(2," AL East Standings  ");    //start standings
    writeLine(3,"Team          W   L ");
    delay(dur);

    writeLine(1,"Red Sox       97  44");
    writeLine(2,"Yankees       87  53");
    writeLine(3,"Rays          75  64");
    delay(dur);

    writeLine(1,"Blue Jays     63  77");
    writeLine(2,"Orioles       41  99");  
    writeLine(3,"--------------------");
    delay(dur);
    
    writeLine(1,"Standings 09/06/2018");
    writeLine(2,"AL Central Standings");
    writeLine(3,"Team          W   L ");
    delay(dur);

    writeLine(1,"Indians       80  60");
    writeLine(2,"Twins         63  76");
    writeLine(3,"Tigers        57  83");
    delay(dur);

    writeLine(1,"White Sox     56  84");
    writeLine(2,"Royals        46  93");
    writeLine(3,"--------------------");
    delay(dur);

    writeLine(1,"Standings 09/06/2018");
    writeLine(2," AL West Standings  ");
    writeLine(3,"Team          W   L ");
    delay(dur);

    writeLine(1,"Astros        87  53");
    writeLine(2,"Athletics     84  57");
    writeLine(3,"Mariners      78  62");
    delay(dur);
    
    writeLine(1,"Angels        68  72");
    writeLine(2,"Rangers       61  79");
    writeLine(3,"--------------------");
    delay(dur);

    writeLine(1,"Standings 09/06/2018");
    writeLine(2," NL East Standings  ");
    writeLine(3,"Team          W   L ");
    delay(dur);

    writeLine(1,"Braves        77  63");
    writeLine(2,"Phillies      73  66");
    writeLine(3,"Nationals     69  72");
    delay(dur);
  
    writeLine(1,"Mets          63  76");
    writeLine(2,"Marlins       56  84");
    writeLine(3,"--------------------");
    delay(dur);
    
    writeLine(1,"Standings 09/06/2018");
    writeLine(2,"NL Central Standings");
    writeLine(3,"Team          W   L ");
    delay(dur);
    
    writeLine(1,"Cubs          83  57");
    writeLine(2,"Brewers       79  62");
    writeLine(3,"Cardinals     78  62");
    delay(dur);

    writeLine(1,"Pirates       69  71");
    writeLine(2,"Reds          59  82");
    writeLine(3,"--------------------");
    delay(dur);

    writeLine(1,"Standings 09/06/2018");
    writeLine(2," NL West Standings  ");
    writeLine(3,"Team          W   L ");
    delay(dur);
    
    writeLine(1,"Rockies       77  62");
    writeLine(2,"Dodgers       76  64");
    writeLine(3,"Diamondbacks  75  65");
    delay(dur);
    
    writeLine(1,"Giants        68  73");
    writeLine(2,"Padres        56  86");
    writeLine(3,"--------------------");
    delay(dur);
  }
}
