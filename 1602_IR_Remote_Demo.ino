/*
 * 1602 IR Remote Demo by Bill Jenkins
 * Released 09/22/2018
 * This prompts user for imput from the IR remote and prints 
 * the results of each key press on a 1602 16x2 character LCD 
 * display. Reading is disabled for two seconds while each 
 * keypress result is displayed. Sketch then prompts for 
 * another key press. Sketch assumes an NEC remote. 
 * The example sketch IRremoteInfo from the IRremote 
 * Library will give you info on your particular remote.
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
 * display the hex values for each key on your particular 
 * IR remote. These values are used to determine which key
 * was pressed, as well as the 'Long' code which indicates
 * the key has been pressed for an extended period. This is
 * recommended if your remote generates many error messages
 * while running this sketch
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
  lcd.print("NEC Remote Test");       // and display for four 
  lcd.setCursor(0, 1);                // seconds, then clear 
  lcd.print("by Bill Jenkins");       // the display
  delay(4000);
  lcd.clear();    
  irrecv.enableIRIn();                // Start the IR receiver 
  lcd.print(" Press any key");        // notify user the unit is
  lcd.setCursor(0,1);                 // ready to receive input
  lcd.print("  to continue.");
}
 
void loop() 
{ 
  if (irrecv.decode(&results))        // if any key is pressed
  { 
    lcd.clear();                      // clear display
    switch(results.value)             // print key press info
    {
      case 0xFFFFFFFF:                // 'Long' indicator,
        break;                        // do nothing
      case 0xFFA25D:                  // '1' pressed
        lcd.print("  Key Read - 1");
        break;
      case 0xFF629D:                  // '2' pressed
        lcd.print("  Key Read - 2");
        break;
      case 0xFFE21D:                  // '3' pressed
        lcd.print("  Key Read - 3");
        break;
      case 0xFF22DD:                  // '4' pressed
        lcd.print("  Key Read - 4");
        break;
      case 0xFF02FD:                  // '5' pressed
        lcd.print("  Key Read - 5");
        break;
      case 0xFFC23D:                  // '6' pressed
        lcd.print("  Key Read - 6");
        break;    
      case 0xFFE01F:                  // '7' pressed
        lcd.print("  Key Read - 7");
        break;
      case 0xFFA857:                  // '8' pressed
        lcd.print("  Key Read - 8");
        break;
      case 0xFF906F:                  // '9' pressed
        lcd.print("  Key Read - 9");
        break;
      case 0xFF6897:                  // '*' pressed
        lcd.print("  Key Read - *");
        break;
      case 0xFF9867:                  // '0' pressed
        lcd.print("  Key Read - 0");
        break;
      case 0xFFB04F:                  // '#' pressed
        lcd.print("  Key Read - #");
        break;
      case 0xFF18E7:                  // 'UP' pressed
        lcd.print(" Key Read - UP");
        break;
      case 0xFF10EF:                  // 'LEFT' pressed
        lcd.print("Key Read - LEFT");
        break;
      case 0xFF38C7:                  // 'OK' pressed
        lcd.print(" Key Read - OK");
        break;
      case 0xFF5AA5:                  // 'RIGHT' pressed
        lcd.print("Key Read - RIGHT");
        break;
      case 0xFF4AB5:                  // 'DOWN' pressed
        lcd.print("Key Read - DOWN");
        break;
      default:                        // print error msg
        lcd.print(" Error on Read");
        break;   
    }
    lcd.setCursor(0,1);               // notify user that read 
    lcd.print("Reading Disabled");    // function is disabled
    delay(2000);                      // display for two seconds
    irrecv.resume();                  // Prepare for key press
    lcd.clear();                      // notify user that the
    lcd.print(" Press any key");      // unit is ready to
    lcd.setCursor(0,1);               // receive input again
    lcd.print("  to continue.");
  } 
}
