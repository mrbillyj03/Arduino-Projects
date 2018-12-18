/*
  Temperature / Humidity Display v 1.0 for Nano by Bill Jenkins
  Released 12/12/2018 
  This sketch is for a temperature and humidity display
  It uses a DHT22 temp./humudity to display this info on 
  a 1602 16x2 character LCD display with an attached I2C 
  backpack. Temperature is shown in ºF and ºC. Info is
  refreshed every 30 seconds
  
  Hardware: Arduino Nano or compatible
            DHT22 Temperature/Humidity Sensor
            1602 16x2 character LCD display 
            I2C backpack for 1602 
            (2x) 170 tie point mini breadboard

  Required Libraries:
  <Adafruit_Sensor.h>  // for DHT22
  <DHT.h>              // for DHT22
  <DHT_U.h>            // for DHT22
  <Wire.h>
  <LiquidCrystal_I2C.h>      // for 1602

  Connections for DHT22 Temperature / Humidity Sensor
  DHT22     Nano
  -------   ----
  DAT       D2     // Data is read from D2
  VCC       +5v 
  GND       Gnd

//  Connections for 1602 16x2 LCD module and I2C backpack
//            I2C     I2C     
//  1602      In      Out     Nano
//  -------   -----   ----    ----
//  1   VSS   Pin 1   GND     Gnd
//  2   VDD   Pin 2   VCC     +5v
//  3   V0    Pin 3   SDA     A4
//  4   RS    Pin 4   SCL     A5
//  5   RW    Pin 5
//  6   E     Pin 6
//  7   D0    Pin 7
//  8   D1    Pin 8
//  9   D2    Pin 9
//  10  D3    Pin 10
//  11  D4    Pin 11
//  12  D5    Pin 12
//  13  D6    Pin 13
//  14  D7    Pin 14
//  15  A     Pin 15
//  16  K     Pin 16
*/

// include required libraries
#include <Adafruit_Sensor.h>  // for DHT22
#include <DHT.h>              // for DHT22
#include <DHT_U.h>            // for DHT22
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // for 1602

#define DHTPIN            2         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT22     // DHT 22 (AM2302)

// Set the LCD address to 0x27 for a 20 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// initialize pins to DHT22. Data line is D2
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
sensors_event_t event;

void setup()
{
  // initialize the LCD
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  delay(100);

  // Initialize DHT22 sensor
  dht.begin();                  // create instance of dht
  sensor_t sensor;              
  dht.temperature().getSensor(&sensor);   // read temp
  dht.humidity().getSensor(&sensor);      // read humidity

  // Set delay time (20 sec.) between readings.
  // delay time (s) = (2000 / dividend)
  delayMS = sensor.min_delay / 66;

  // print opening screen, display for 3 sec.
  lcd.print("Temp/Humidity");
  lcd.setCursor(0, 1);
  lcd.print("Sensor for 1602");
  delay(3000);
}

void loop()
{
  lcd.clear();                          // clear display
  dht.temperature().getEvent(&event);   // read temperature
  lcd.print("Temp: ");                 // print temp in ºF
  lcd.print(int(event.temperature * 1.8 + 32.0));
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("F/");
  lcd.print(int(event.temperature));    // print temp. in ºC
  lcd.print(char(0xDF));                // degree symbol
  lcd.print("C");
  lcd.setCursor(0, 1);
  dht.humidity().getEvent(&event);      // read humidity
  lcd.print("Humidity: ");        // print humidity
  lcd.print(int(event.relative_humidity));
  lcd.print("%");
  delay(delayMS);                       // delay between readings
}
