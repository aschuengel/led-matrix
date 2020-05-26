#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <string.h>

// IP address for the ESP8266 is displayed on the scrolling display
// after startup initialisation and connected to the WiFi network.
//
// Connections for ESP8266 hardware SPI are:
// Vcc       3v3     LED matrices seem to work at 3.3V
// GND       GND     GND
// DIN        D8     HSPID or HMOSI
// CS or LD   D9     HSPICS or HCS
// CLK        D10    CLK or HCLK
//

// Cf. https://majicdesigns.github.io/MD_MAX72XX/index.html


#define MAX_DEVICES 4
#define CS_PIN 9
#define DATA_PIN 8
#define CLCK_PIN 10

int i = 0;

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::FC16_HW, DATA_PIN, CLCK_PIN, CS_PIN, MAX_DEVICES);

void setup()
{
  mx.begin();
  /*mx.control(0, MD_MAX72XX::INTENSITY, 2);
  mx.control(1, MD_MAX72XX::INTENSITY, 2);
  mx.control(2, MD_MAX72XX::INTENSITY, 2);
  mx.control(3, MD_MAX72XX::INTENSITY, 2);*/

  Serial.begin(9600);
}

void scrollText(const char *p);

void loop()
{
  scrollText("Testing 123");
}

void scrollText(const char *p)
{
  uint8_t charWidth;
  uint8_t cBuf[8]; // this should be ok for all built-in fonts
  int length;
  int k;
  char c;

  length = strlen(p);

  Serial.print("\nScrolling text");
  mx.clear();

  for (k = 0; k < length; k++)
  {
    c = p[k];
    charWidth = mx.getChar(c, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (uint8_t i = 0; i <= charWidth; i++) // allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      if (i < charWidth)
        mx.setColumn(0, cBuf[i]);
      delay(50);
    }
  }
}