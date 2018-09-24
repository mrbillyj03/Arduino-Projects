/*
 * IRremote Notepad by Bill Jenkins
 * Released 09/24/2018
 * This prompts user for imput from 
 * the IR remote and updates the message on a
 * 1602 display accordingly. 
 * 
 * Key Menu for Arduino IR remote
 * UP Key - Increments current letter
 * DOWN Key - Decrements current letter
 * RIGHT Key - move to next character, insert ' '
 * LEFT Key - go back one character
 * OK Key - Clears screen and starts over
 * '*' Key - Adds space character
 * '#' Key - Adds punctuation character
 * '1' Key - -4 to current char (medium down)
 * '3' Key - +4 from current char (medium up)
 * '4' Key - -8 to current char (large down)
 * '5' Key - Locks message, requires reset to continue
 * '6' Key - +8 from current char (large up)
 * '7' Key - +32 to current char (uppercase to lowercase)
 * '9' Key - -32 from current char (lowercase to uppercase)
 * 
 * Hardware: Arduino Uno or Compatible
 *           Acrylic Case for Arduino Uno (optional)
 *           Uno Prototype Shield v.5 (optional)
 *           170 tie point mini breadboard
 *           IR Remote and IR Receiver module
 *           1602 16x2 character LCD display
 *           10k potentiomeer for brightness adjustment on 1602
 *           
 * Required   
 * Libraries: <boarddefs.h>
 *            <IRremote.h>          
 *            <IRremoteInt.h>
 *            <ir_Lego_PF_BitStreamEncoder.h>
 *            <LiquidCrystal.h>
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
#include <LiquidCrystal.h>

//  Connections for 1602 16x2 character LCD module (4 bit mode)
//  1602      UNO     
//  -------   ---
//  1   VSS   Gnd
//  2   VDD   5v
//  3   V0    TO 10K POT WIPER, (-) LEAD TO GND
//  4   RS    D12
//  5   RW    D11
//  6   E     D10
//  7   D0    --
//  8   D1    --
//  9   D2    --
//  10  D3    --
//  11  D4    D9
//  12  D5    D8
//  13  D6    D7
//  14  D7    D6
//  15  A     3v
//  16  K     Gnd

//  Connections for 10k potentiometer for 1602 brightness
//  10k pot   to (device, pin)
//  -------   ---
//  (+)       UNO 5V    
//  (Wiper)   1602 (3)      
//  (-)       UNO GND

// Connections for Infrared Receiver (IRR) module 
// IRR  UNO
// ---  ---
// S    D2
// VCC  +5v
// GND  Gnd

int RECV_PIN = 2; //define IR receiver input pin on Arduino 
IRrecv irrecv(RECV_PIN);  // declare instance of receive object
decode_results results;   // results of key press scan

// Pin definitions for 1602 LCD display
int LCD1602_RS=12;   
int LCD1602_RW=11;   
int LCD1602_EN=10;   
int DB[] = {6,7,8,9};

// declare instance of LCD screen object
LiquidCrystal lcd(LCD1602_RS,LCD1602_EN,9,8,7,6);

// blank string to capture Mr. Smiley and Ms. Heart
String sac="Arduino";
char thischar;                        // current character
char linetext[2][16];
int row, col;                         // row and column number 


 
// function for sending initialization commands to 1602
void LCD_Command_Write(int command)
{
  int i,temp;
  digitalWrite(LCD1602_RS,LOW);
  digitalWrite(LCD1602_RW,LOW);
  digitalWrite(LCD1602_EN,LOW);
 
  temp=command & 0xf0;
  for (i=DB[0]; i<=9; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
  digitalWrite(LCD1602_EN,HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN,LOW);
 
  temp=(command & 0x0f)<<4;
  for (i=DB[0]; i<=10; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
  digitalWrite(LCD1602_EN,HIGH);
  delayMicroseconds(1); 
  digitalWrite(LCD1602_EN,LOW);
}
 
void setup() 
{ 
  // Set up output pins for 1602 display
  int i;
  for (i = 6; i <= 12; i++)
  {
    pinMode(i, OUTPUT);
  }
  lcd.begin(16, 2);        // Initialize 1602 display
  LCD_Command_Write(0x28); // 4 wire mode, 2 lines, 5x7 chars
  delay(50);
  LCD_Command_Write(0x06);
  delay(50);
  LCD_Command_Write(0x0c);
  delay(50);
  LCD_Command_Write(0x80);
  delay(50);
  LCD_Command_Write(0x01);
  delay(50);
  lcd.clear();                        // print opening screen
  lcd.print("IRremote Notepad");      // and display for three 
  lcd.setCursor(0, 1);                // seconds, then clear 
  lcd.print("by Bill Jenkins");       // the display
  delay(3000);
  lcd.clear();    

  row=0;
  col=0;
  linetext[0][0]='M';
  lcd.setCursor(0,0);
  lcd.print(linetext[0]);
  lcd.setCursor(0,0);
  
  irrecv.enableIRIn();  // Start the IR receiver 
                        // get ready to process characters
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
        // Decrement character by 4
        linetext[row][col]-=4;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF629D:                  // '2' pressed
        break;
      case 0xFFE21D:                  // '3' pressed
        // Increment character by 4
        linetext[row][col]+=4;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF22DD:                  // '4' pressed
        // Decrement character by 8
        linetext[row][col]-=8;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF02FD:                  // '5' pressed
        // Freeze screen, disable input 
        // requires system reset to continue.
        while (1);
        break;
      case 0xFFC23D:                  // '6' pressed
        // Increment character by 8
        linetext[row][col]+=8;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;    
      case 0xFFE01F:                  // '7' pressed
        // turn uppercase character to lowercase
        linetext[row][col]+=32;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print lowercase character
        break;
      case 0xFFA857:                  // '8' pressed
        break;
      case 0xFF906F:                  // '9' pressed
        // turn lowercase character to uppercase
        linetext[row][col]-=32;
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print uppercase character
        break;
      case 0xFF6897:                  // '*' pressed
      // Add an alpha character
        col++;                        // Increment column
        if (col>15)                   // check for overflow
        { 
          if (row==1)                 // on diaplay overflow
            while (1);                // stop processing keys
          col=0;
          row=1;
        }
        linetext[row][col]='M';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print uppercase M
        break;
      case 0xFF9867:                  // '0' pressed
        // Add a numeric character
        col++;                        // increment colunm
        if (col>15)                   // check for overflow
        { 
          if (row==1)                 // on diaplay overflow
            while (1);                // stop processing keys
          col=0;
          row=1;
        }
        linetext[row][col]='5';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print numeric 5
        break;
      case 0xFFB04F:                  // '#' pressed
        // Add punctation
        col++;                        // increment colunm
        if (col>15)                   // check for overflow
        { 
          if (row==1)                 // on diaplay overflow
            while (1);                // stop processing keys
          col=0;
          row=1;
        }
        linetext[row][col]='!';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print ! character
        break;
      case 0xFF18E7:                  // 'UP' pressed
        // increment character
        linetext[row][col]++;         // Increment character 
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF10EF:                  // 'LEFT' pressed
      // clear current character, edit previous character
        linetext[row][col]=' ';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print space
        col--;                        // Decrement column
        if (col<0 && row==1)          // check for underflow
        {
          row=0;
          col=15;
        }
        break;
      case 0xFF38C7:                  // 'OK' pressed
        // clear all, start from beginning
        for (row=0; row<2; row++)
        {
          for (col=0; col<16; col++)
            linetext[row][col]=' ';
        }
        row=0;
        col=0;
        lcd.clear();
        linetext[row][col]='M';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      case 0xFF5AA5:                  // 'RIGHT' pressed
        // Add space character
        col++;                        // increment colunm
        if (col>15)                   // check for overflow
        { 
          if (row==1)                 // on diaplay overflow
            while (1);                // stop processing keys
          col=0;
          row=1;
        }
        linetext[row][col]=' ';
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print space character
        break;
      case 0xFF4AB5:                  // 'DOWN' pressed
        // Decrement character
        linetext[row][col]--;         
        lcd.setCursor(col,row);
        lcd.print(linetext[row][col]);// print new character
        break;
      default:                        // do nothing
        break;   
    }
    irrecv.resume();                  // Prepare for key press
  } 
}
