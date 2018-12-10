/*
 * IRremote Notepad by Bill Jenkins
 * Released 09/24/2018
 * This prompts user for imput from the IR remote and 
 * updates the message on a 2004 display accordingly. 
 * Revised 09/30/2018
 * Eliminated bug that caused the opening screen to repeat
 * Revised 11/30/2018
 * Upgraded display to 2004
 * 
 * Key Menu for Arduino IR remote
 * '1' Key - Increment char by 2
 * '2' Key - Increment char by 4
 * '3' Key - Increment char by 8
 * '4' Key - Decrement current char
 * '5' Key - Clears screen and starts over
 * '6' Key - Increment current char
 * '7' Key - Decrement current char by 2
 * '8' Key - Decrement current char by 4
 * '9' Key - Decrement current char by 8
 * '*' Key - Add new alpha character
 * '0' Key - Add new numeric character
 * '#' Key - Add new punctuation character
 * UP Key - Decrement current char by 32 (a -> A)
 * DOWN Key - Increment current letter by 32 (A -> a)
 * RIGHT Key - Add new space character 
 * LEFT Key - clear current character, go back one character
 * OK Key - Locks message, requires reset to continue
 * 
 * Hardware: 
 * Arduino Uno or Compatible
 * Acrylic Case for Arduino Uno (optional)
 * Uno Prototype Shield v.5 (optional)
 * 170 tie point mini breadboard
 * IR Remote and IR Receiver module
 * 1602 16x2 character LCD display
 * 10k potentiomeer for brightness adjustment on 1602
 *           
 * Required Libraries: 
 * <boarddefs.h>
 * <IRremote.h>          
 * <IRremoteInt.h>
 * <ir_Lego_PF_BitStreamEncoder.h>
 * <LiquidCrystal_I2C.h>
 *            
 * The short sketch below can be copied to its own file to   
 * display the hex values received by the IR Receiver for 
 * each key on your particular IR remote. These values are 
 * stored in the variable results.value and displayed upon
 * decoding a valid IR signal for the key being pressed. 
 * This sketch also displays the 'Long' code which indicates
 * the key has been pressed for an extended period. 
 * 
 * This is recommended if your remote generates many error 
 * messages while running this sketch. Sketch is from a Weikids 
 * Starter Kit document and writes to the Serial Monitor at 
 * 9600 baud.
 */

/*
// IR Remote Code Finder
// This sketch prints the hex values from each key press 
// on the IR Remote and displays them on the Serial Monitor

#include <IRremote.h>
int RECV_PIN = 2; //define input pin on Arduino
IRrecv irrecv(RECV_PIN);
decode_results results;
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}
void loop() 
{
  if (irrecv.decode(&results)) 
  {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}
// End of IR Remote Code Finder
*/

// include required libraries
#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <LiquidCrystal_I2C.h>


// Connections for Infrared Receiver (IRR) module 
// IRR  UNO
// ---  ---
// S    D2
// VCC  +5v
// GND  Gnd

//  2004    UNO
//  ----    ---
//  GND     Gnd
//  VCC     5v
//  SDA     A4
//  SCL     A5


int RECV_PIN = 2; //define IR receiver input pin on Arduino 
IRrecv irrecv(RECV_PIN);  // declare instance of receive object
decode_results results;   // results of key press scan


// declare instance of LCD screen object
// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);


// blank string to capture Mr. Smiley and Ms. Heart
String sac="Arduino";
char thischar;                        // current character
char linetext[4][20];
int row, col;                         // row and column number 
void setup() 
{ 
  irrecv.enableIRIn();  // Start the IR receiver 
                        // get ready to process characters
                        
  // initialize the LCD
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  delay(100);

  lcd.clear();                            // print opening screen
  lcd.print("  IRremote Notepad  ");      // and display for three 
  lcd.setCursor(0, 1);                    // seconds, then clear 
  lcd.print("   by Bill Jenkins  ");           // the display
  lcd.setCursor(0, 2);                    
  lcd.print("  BJ+VJ Enterprises ");      
  lcd.setCursor(0, 3);                    
  lcd.print("  Chicago, IL 60617 ");      
  delay(3000);
  lcd.clear();    

  row=0;
  col=0;
  lcd.setCursor(0,0);
  linetext[0][0]='m';
  lcd.print(linetext[0][0]);
}
 
void loop() 
{ 
  if (irrecv.decode(&results))        // if any key is pressed
  { 
    switch(results.value)             // print key press info
    {
      case 0xFFFFFFFF:                // 'Long' indicator,
        break;                        // do nothing
      case 0xFFA25D:                  // '1' pressed
        // Decrement character by 2
        linetext[row][col]-=2;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF629D:                  // '2' pressed
        // Decrement character by 4
        linetext[row][col]-=4;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFFE21D:                  // '3' pressed
        // Decrement character by 8
        linetext[row][col]-=8;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF22DD:                  // '4' pressed
        // Decrement current char
        linetext[row][col]--;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print lowercase
        break;
      case 0xFF02FD:                  // '5' pressed
        // clear all, start from beginning
        for (row=0; row<4; row++)
        {
          for (col=0; col<20; col++)
            linetext[row][col]=' ';
        }
        row=0;
        col=0;
        lcd.clear();
        linetext[row][col]='m';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// new start screen
        break;
      case 0xFFC23D:                  // '6' pressed
        // Increment character 
        linetext[row][col]++;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print uppercase
        break;    
      case 0xFFE01F:                  // '7' pressed
        // Increment character by 2
        linetext[row][col]+=2;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFFA857:                  // '8' pressed
        // Increment character by 4
        linetext[row][col]+=4;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
       break;
      case 0xFF906F:                  // '9' pressed
        // Increment character by 8
        linetext[row][col]+=8;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF6897:                  // '*' pressed
      // Add an alpha character
        col++;                        // Increment column
        if (col>19)                   // check for overflow
        { 
          if (row==3)                 // on display overflow
            while (1);                // stop processing keys
          row++;
          col=0;
        }
        linetext[row][col]='m';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print lowercase M
        break;
      case 0xFF9867:                  // '0' pressed
        // Add a numeric character
        col++;                        // increment colunm
        if (col>19)                   // check for overflow
        { 
          if (row==3)                 // on display overflow
            while (1);                // stop processing keys
          row++;
          col=0;
        }
        linetext[row][col]='5';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print numeric 5
        break;
      case 0xFFB04F:                  // '#' pressed
        // Add punctation
        col++;                        // increment colunm
        if (col>19)                   // check for overflow
        { 
          if (row==3)                 // on display overflow
            while (1);                // stop processing keys
          row++;
          col=0;
        }
        linetext[row][col]='!';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print ! character
        break;
      case 0xFF18E7:                  // 'UP' pressed
        // Decrement character (lowercase to Uppercase)
        linetext[row][col]-=32;         
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF10EF:                  // 'LEFT' pressed
      // clear current character, edit previous character
        linetext[row][col]=' ';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print space
        col--;                        // Decrement column
        if (col<0)
        {
          row--;
          col=19;
        }
        if (row<0)
        {
          row=0;
          col=0;
          linetext[row][col]='m';
          lcd.setCursor(col,row);
          lcd.print(linetext[row][col]);// print m
        }
        break;
      case 0xFF38C7:                  // 'OK' pressed
        // Freeze screen, disable input 
        // requires system reset to continue.
        while (1);
        break;
      case 0xFF5AA5:                  // 'RIGHT' pressed
        // Add space character
        col++;                        // increment colunm
        if (col>19)                   // check for overflow
        { 
          if (row==3)                 // on display overflow
            while (1);                // stop processing keys
          row++;
          col=0;
        }
        linetext[row][col]=' ';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print space character
        break;
      case 0xFF4AB5:                  // 'DOWN' pressed
        // Increment character by 32 (Uppercase to lowercase)
        linetext[row][col]+=32;         
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      default:                        // do nothing
        break;   
    }
    irrecv.resume();                  // Prepare for key press
  } 
}
