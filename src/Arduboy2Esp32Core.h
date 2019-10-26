#ifndef _ARDUBOY2_ESP32CORE_H
#define _ARDUBOY2_ESP32CORE_H
#include <stdio.h>
#include <Arduino.h>
#include "Arduboy2Esp32Beep.h"
#include "ArduboyPlaytune.h"
#include "SPI.h"
#include "Sprites.h"
#include "SpritesB.h"
#include "ArduboyTones.h"

// OLED hardware (SSD1306)

#define OLED_PIXELS_INVERTED 0xA7 // All pixels inverted
#define OLED_PIXELS_NORMAL 0xA6 // All pixels normal

#define OLED_ALL_PIXELS_ON 0xA5 // all pixels on
#define OLED_PIXELS_FROM_RAM 0xA4 // pixels mapped to display RAM contents

#define OLED_VERTICAL_FLIPPED 0xC0 // reversed COM scan direction
#define OLED_VERTICAL_NORMAL 0xC8 // normal COM scan direction

#define OLED_HORIZ_FLIPPED 0xA0 // reversed segment re-map
#define OLED_HORIZ_NORMAL 0xA1 // normal segment re-map

#define WIDTH 128 
#define HEIGHT 64

#define COLUMN_ADDRESS_END (WIDTH - 1) & 127   // 128 pixels wide
#define PAGE_ADDRESS_END ((HEIGHT/8)-1) & 7    // 8 pages high

#define OLED_D0_PIN    32
#define OLED_D1_PIN    25
#define OLED_RES_PIN   27
#define OLED_DC_PIN    12
#define OLED_CS_PIN    13


#define RGB_ON LOW   /**< For digitially setting an RGB LED on using digitalWriteRGB() */
#define RGB_OFF HIGH /**< For digitially setting an RGB LED off using digitalWriteRGB() */

#define RED_LED 10   /**< The pin number for the red color in the RGB LED. */
#define GREEN_LED 11 /**< The pin number for the greem color in the RGB LED. */
#define BLUE_LED 9   /**< The pin number for the blue color in the RGB LED. */

#define PIN_SPEAKER_1 5  /**< The pin number of the first lead of the speaker */
#define PIN_SPEAKER_2 13 /**< The pin number of the second lead of the speaker */


// #define _BV(bit) (1 << (bit))

#define LEFT_BUTTON  0B01000000
#define RIGHT_BUTTON 0B00100000
#define UP_BUTTON    0B00010000
#define DOWN_BUTTON  0B00001000
#define A_BUTTON     0B00000100
#define B_BUTTON     0B00000010

#define UP_BUTTON_PIN     23
#define DOWN_BUTTON_PIN   22
#define LEFT_BUTTON_PIN   21
#define RIGHT_BUTTON_PIN  19
#define A_BUTTON_PIN      18
#define B_BUTTON_PIN      5

class Arduboy2Core
{
  friend class Arduboy2Ex;

  public:
    Arduboy2Core();

    void static idle();

    void static LCDDataMode();

    void static LCDCommandMode();

    void static SPItransfer(uint8_t data);

    void static displayOff();

    void static displayOn();

    uint8_t static width();
  
    uint8_t static height();

    uint8_t static buttonsState();

    void static paint8Pixels(uint8_t pixels);
   
    void static paintScreen(const uint8_t *image);

    void static paintScreen(uint8_t image[], bool clear = false);
    
    void static blank();

    void static invert(bool inverse);

    void static allPixelsOn(bool on);

    void static flipVertical(bool flipped);

    void static flipHorizontal(bool flipped);
   
    void static sendLCDCommand(uint8_t command);

    void static setRGBled(uint8_t red, uint8_t green, uint8_t blue);

    void static setRGBled(uint8_t color, uint8_t val);

    void static freeRGBled();
   
    void static digitalWriteRGB(uint8_t red, uint8_t green, uint8_t blue);
   
    void static digitalWriteRGB(uint8_t color, uint8_t val);

    void static boot();

    void static safeMode();

    void static delayShort(uint16_t ms) __attribute__ ((noinline));

    void static exitToBootloader();

    void static mainNoUSB();

  protected:
    void static setCPUSpeed8MHz();
    void static bootSPI();
    void static bootOLED();
    void static bootPins();
    void static bootPowerSaving();
};


#endif