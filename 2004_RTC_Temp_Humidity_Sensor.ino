/*
  Temperature and Humidity Display v 1.0 by Bill Jenkins
  Released 09/20/2018 
  This sketch is for a temperature and humidity display
  which also shows the station location, the date and the time.
  It uses a DHT22 temp./humudity and a DS3231 Real Time Clock
  module to display this info on a 2004 20x4 character
  LCD display. Temperature is shown in ºF and ºC. Info is
  refreshed every ten seconds
  
  Hardware: Arduino Uno or compatible
            DHT22 Temperature/Humidity Sensor
            DS3231 Real Time Clock module
            2004A 20x4 character LCD display with I2C backpack
            Arduino Prototype Shield
            170 tie point mini breadboard

  Required Libraries:
  <Adafruit_Sensor.h>  // for DHT22
  <DHT.h>              // for DHT22
  <DHT_U.h>            // for DHT22
  <MD_DS3231.h>        // for DS3231
  <Wire.h>
  <LiquidCrystal_I2C.h>      // for 2004

  Connections for DHT22 Temperature / Humidity Sensor
  DHT22     UNO
  -------   ---
  DAT       D2    // Data is read from D2
  VCC       D3    // Set D3 HIGH for 5V to pot
  GND       GND

  Connections for DS3231 Real Time Clock (RTC) module
  DS3231  UNO
  ------  ---
  SCL     A5
  SDA     A4
  VCC     5v
  GND     Gnd

  Connections for 2004A LCD display with I2C backpack
  2004    UNO
  ----    ---
  GND     Gnd
  VCC     5v
  SDA     A4
  SCL     A5

*/

// include required libraries
#include <Adafruit_Sensor.h>  // for DHT22
#include <DHT.h>              // for DHT22
#include <DHT_U.h>            // for DHT22
#include <MD_DS3231.h>        // for DS3231
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // for 2004

#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

// initialize power pins to DHT22. D3 is set HIGH
// for power to the DHT22. Data line is D2
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
const int pinVolt = 3;  // D3 will be set HIGH for +5V to DHT22
sensors_event_t event;

// Function to format a 2 digit number to print leading zero
char *p2dig(uint8_t v, uint8_t mode)
{
  static char s[3];
  uint8_t i = 0;
  uint8_t n = 0;

  switch (mode)
  {
    case HEX: n = 16;  break;
    case DEC: n = 10;  break;
  }

  if (v < n) s[i++] = '0';
  itoa(v, &s[i], n);

  return (s);
}

// Function converts Day of week to string.
// DOW 1=Sunday, 0 is undefined
const char *dow2String(uint8_t code)
{
  static const char *str[] = {"---", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

  if (code > 7) code = 0;
  return (str[code]);
}

void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  delay(100);

  // Initialize DHT22 sensor
  pinMode(pinVolt, OUTPUT);     // set up pin D3 for +5
  digitalWrite(pinVolt, HIGH);  // set D3 HIGH for +5V to DHT22
  dht.begin();                  // create instance of dht
  sensor_t sensor;              
  dht.temperature().getSensor(&sensor);   // read temp
  dht.humidity().getSensor(&sensor);      // read humidity

  // Set delay time (10 sec.) between readings.
  // delay time (s) = (2000 / dividend)
  delayMS = sensor.min_delay / 200;

  // print opening screen, display for 3 sec.
  lcd.print(" Temp and Humidity");
  lcd.setCursor(0, 1);
  lcd.print("Sensor for 2004 LCD");
  lcd.setCursor(0, 2);
  lcd.print("  by Bill Jenkins");
  lcd.setCursor(0, 3);
  lcd.print("mrbillyj03 on GitHub");
  delay(3000);
}

void loop()
{
  RTC.readTime();                       // read time
  lcd.clear();                          // clear display
  lcd.print("East Side | ");            // print location part 1
  lcd.print(p2dig(RTC.mm, DEC));        // print month
  lcd.print("/");
  lcd.print(p2dig(RTC.dd, DEC));        // print date
  lcd.print("/");
  lcd.print(RTC.yyyy - 2000);           // print last 2 digits of year
  lcd.setCursor(0, 1);                  
  lcd.print("Chicago IL| ");            // print location part 2
  lcd.print(p2dig(RTC.h, DEC));         // print hours
  lcd.print(":");                       // print colon
  lcd.print(p2dig(RTC.m, DEC));         // print minutes
  //  PRINT(":", p2dig(RTC.s, DEC));    uncomment for seconds
  if (RTC.status(DS3231_12H) == DS3231_ON)
    lcd.print(RTC.pm ? " pm" : " am");  // print am or pm
  lcd.setCursor(0, 2);
  dht.temperature().getEvent(&event);   // read temperature
  lcd.print(" Temp: ");                 // print temp in ºF
  lcd.print(int(event.temperature * 1.8 + 32.0));
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("F / ");
  lcd.print(int(event.temperature));    // print temp. in ºC
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("C");
  lcd.setCursor(0, 3);
  dht.humidity().getEvent(&event);      // read humidity
  lcd.print(" Rel. Humidity: ");        // print humidity
  lcd.print(int(event.relative_humidity));
  lcd.print("%");
  delay(delayMS);                       // delay between readings
}
