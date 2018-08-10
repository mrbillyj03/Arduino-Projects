#include <LiquidCrystal.h>

//  This displays MLB Baseball scores for 08/09/2018
//  1602      Arduino     4 bit mode
//  1   VSS   Gnd
//  2   VDD   5v
//  3   V0    TO 1K RESISTOR, OTHER LEAD TO GND
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



// Common browsing,copying, saving and printing of code
int LCD1602_RS=12;   
int LCD1602_RW=11;   
int LCD1602_EN=10;   
int DB[] = { 6, 7, 8, 9};
int dur=3000;
 
 LiquidCrystal lcd(LCD1602_RS, LCD1602_EN,  9,  8,  7,  6);
 
 void LCD_Command_Write(int command)
 {
  int i,temp;
  digitalWrite( LCD1602_RS,LOW);
  digitalWrite( LCD1602_RW,LOW);
  digitalWrite( LCD1602_EN,LOW);
 
  temp=command & 0xf0;
  for (i=DB[0]; i <= 9; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
  
  digitalWrite( LCD1602_EN,HIGH);
  delayMicroseconds(1);
  digitalWrite( LCD1602_EN,LOW);
 
  temp=(command & 0x0f)<<4;
  for (i=DB[0]; i <= 10; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
 
  digitalWrite( LCD1602_EN,HIGH);
  delayMicroseconds(1); 
  digitalWrite( LCD1602_EN,LOW);
 }
 
 void LCD_Data_Write(int dat)
 {
  int i=0,temp;
  digitalWrite( LCD1602_RS,HIGH);
  digitalWrite( LCD1602_RW,LOW);
  digitalWrite( LCD1602_EN,LOW);
 
  temp=dat & 0xf0;
  for (i=DB[0]; i <= 9; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
 
  digitalWrite( LCD1602_EN,HIGH);
  delayMicroseconds(1);
  digitalWrite( LCD1602_EN,LOW);
 
  temp=(dat & 0x0f)<<4;
  for (i=DB[0]; i <= 10; i++)
  {
    digitalWrite(i,temp & 0x80);
    temp <<= 1;
  }
 
  digitalWrite( LCD1602_EN,HIGH);
  delayMicroseconds(1); 
  digitalWrite( LCD1602_EN,LOW);
 }
 
 void LCD_SET_XY( int x, int y )
 {
   int address;
   if (y ==0)    address = 0x80 + x;    // line 0 starts at address 0x80
   else          address = 0xC0 + x;    // line 1 starts at address 0xC0
   LCD_Command_Write(address); 
 }
 
 void LCD_Write_Char( int x,int y,int dat)
 {
   LCD_SET_XY( x, y );      //  go to position x, line y
   LCD_Data_Write(dat);     //  write one character
 }
 
 void LCD_Write_String(int y,char *s)
 {
     LCD_SET_XY( 0, y );    // address setup (char 0, line y)
     while (*s)             // write character string
     {
       LCD_Data_Write(*s);   
       s ++;
     }
 }
 
 void setup (void) 
 {
   int i = 0;
   for (i=6; i <= 12; i++) 
    {
      pinMode(i,OUTPUT);
    }
   delay(100);
   lcd.begin(16,2);         // INITIALIZE DISPLAY
   
   LCD_Command_Write(0x28); // 4 wires, 2 lines 5x7
   delay(50); 
   LCD_Command_Write(0x06);
   delay(50); 
   LCD_Command_Write(0x0c);
   delay(50); 
   LCD_Command_Write(0x80);
   delay(50); 
   LCD_Command_Write(0x01);
   delay(50); 
   LCD_Write_String(0,"Display v. 1.0.3");// line 1
   LCD_Write_String(1," by Bill Jenkins");// line 2
   delay(dur);
 
 }
 
 void loop (void)
 {
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"   MLB Scores   ");// line 1
    LCD_Write_String(1,"   08/09/2018   ");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Braves         3");// line 1
    LCD_Write_String(1,"Nationals      6");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Twins          4");// line 1
    LCD_Write_String(1,"Indians        5");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Padres         8");// line 1
    LCD_Write_String(1,"Brewers        4");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Rangers        3");// line 1
    LCD_Write_String(1,"Yankees        7");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Red Sox        5");// line 1
    LCD_Write_String(1,"Blue Jays      8");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Orioles        4");// line 1
    LCD_Write_String(1,"Rays           5");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Mariners       8");// line 1
    LCD_Write_String(1,"Astros         6");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Dodgers        8");// line 1
    LCD_Write_String(1,"Rockies        5");// line 2
    delay(dur);
    
    LCD_Command_Write(0x01);  // clear screen
    delay(50);
    LCD_Write_String(0,"Pirates       10");// line 1
    LCD_Write_String(1,"Giants         5");// line 2
    delay(dur);
}

