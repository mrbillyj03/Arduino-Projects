// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Modified by Bill Jenkins to write to a 1602 LCD display
// instead of the serial monitor and print temp in ºF and ºC
// instead of just ºC. This includes the "º" symbol (0xDF)
// Temp and humidity readings are taken every ten seconds.
// NOTE: Requires Old Bootloader for ATmega328P processor
// Hardware: Arduino Nano or compatible
//           DHT22 Temp/Humidity Sensor
//           1602 LCD display
//           810 tie point breadboard
//           1k resistor

//  Connections for 1602 16x2 character LCD module
//  1602      Nano  (1602 LCD display in 4 bit mode)
//  -------   ----
//  1   VSS   Gnd
//  2   VDD   5v
//  3   V0    1K RESISTOR, OTHER LEAD TO GND
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

//  Connections for DHT22 Temperature / Humidity Sensor
//  DHT22   Nano
//  -----   ----
//  DAT     D2    // Data is read from D2
//  VCC     +5V   
//  GND     GND

#include <Adafruit_Sensor.h>  // For DHT22
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>    // For 1602

// DHT-22 stuff here
#define DHTPIN            2         // Data pin goes to D2
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

// 1602 stuff here
int LCD1602_RS = 12;
int LCD1602_RW = 11;
int LCD1602_EN = 10;
int DB[] = {6, 7, 8, 9};

LiquidCrystal lcd(LCD1602_RS, LCD1602_EN, 9, 8, 7, 6); // declare lcd

void LCD_Command_Write(int command)
{
  int i, temp;
  digitalWrite(LCD1602_RS, LOW);
  digitalWrite(LCD1602_RW, LOW);
  digitalWrite(LCD1602_EN, LOW);
  temp = command & 0xf0;
  for (i = DB[0]; i <= 9; i++)
  {
    digitalWrite(i, temp & 0x80);
    temp <<= 1;
  }
  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, LOW);
  temp = (command & 0x0f) << 4;
  for (i = DB[0]; i <= 10; i++)
  {
    digitalWrite(i, temp & 0x80);
    temp <<= 1;
  }
  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, LOW);
}

void setup()
{
  // Initialize DHT22 sensor
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);

  // Initialize 1602 display
  // set up the LCD's number of columns and rows:
  int i;
  for (i = 6; i <= 12; i++)
  {
    pinMode(i, OUTPUT);
  }
  lcd.begin(16, 2);        // INITIALIZE DISPLAY
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

  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 200;     // 4 sec. delay with 500, 2 sec. delay with 1000

  // print opening screen
  lcd.print("Temp/RH Sensor");
  lcd.setCursor(0, 1);
  lcd.print("by Bill Jenkins");
}

void loop()
{
  // Error chacking for temp and humidity out of range
  // values taken out because this is an indoor
  // station and to save storage space.
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(int(event.temperature * 1.8 + 32.0)); // print temp. in fahrenheit
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("F ");
  lcd.print(int(event.temperature));    // print temp. in celsius
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("C");

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  lcd.setCursor(0, 1);
  lcd.print(" Humidity: ");
  lcd.print(int(event.relative_humidity));
  lcd.print("%");
}
