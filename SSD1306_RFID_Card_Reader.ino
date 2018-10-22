/*
   RFID Reader for Nano by Bill Jenkins
   Released: [release date]
   This sketch reads RFID tags and displays info
   Hardware: Arduino Nano (requires old bootloder)
             RC522 RFID Module
             SSD1306 0.91" 128x32 I2C OLED display
   Required Libraries:
   Revision History:

*/

// Connections for DDS1306 0.91" 128x32 OLED module
// DDS1306    UNO
// -------    ---
// GND        GND
// VCC        5V
// SCL        A5
// SDA        A4


//  Connections for RC522 RFID module
//  RC522   UNO
//  -----   ---
//  3.3V    3.3V
//  RST     D9
//  GND     GND
//  IRQ     ---
//  MISO    D12
//  MOSI    D11
//  SCK     D13
//  SDA     D10


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

// stuff for OLED display
#define SS_PIN 10
#define RST_PIN 9
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

// Init array that will store new NUID
byte nuidPICC[4];

void setup()
{
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  for (byte i = 0; i < 6; i++) 
  {
    key.keyByte[i] = 0xFF;
  }

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Clear the buffer.
  display.clearDisplay();
}

void loop()
{
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("RF Reader");
  display.println("Scan Card"); 
  display.display();

  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been read
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) 
  {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }
  display.clearDisplay();  
  display.setCursor(0, 0);
  // identify all known tags
  if (nuidPICC[0]==0x60 && nuidPICC[1]==0x3C && 
  nuidPICC[2]==0xE2 && nuidPICC[3]==0xA4)
  {
    display.println("EEID:00001");
    display.println("William"); 
  }
  else if (nuidPICC[0]==0x26 && nuidPICC[1]==0x4C && 
  nuidPICC[2]==0x94 && nuidPICC[3]==0x12)
  {
    display.println("EEID:00002");
    display.println("Vivical"); 
  }
  else if (nuidPICC[0]==0xDE && nuidPICC[1]==0x97 && 
  nuidPICC[2]==0x22 && nuidPICC[3]==0xD9)
  {
    display.println("Key Fob 1");
    display.println("Not Issued"); 
  }
  else if (nuidPICC[0]==0xBD && nuidPICC[1]==0x34 && 
  nuidPICC[2]==0xAD && nuidPICC[3]==0x49)
  {
    display.println("Key Fob 2");
    display.println("Not Issued"); 
  }  
  else 
  {
    display.println("Invalid");
    display.println("Card Read");
  }
  display.display();
  delay(2500);
  
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}
