#include "Arduboy2Esp32Core.h"


static SPIClass spi;

const uint8_t lcdBootProgram[] = {
  // boot defaults are commented out but left here in case they
  // might prove useful for reference
  //
  // Further reading: https://www.adafruit.com/datasheets/SSD1306.pdf
  //
  // Display Off
  // 0xAE,

  // Set Display Clock Divisor v = 0xF0
  // default is 0x80
  0xD5, 0xF0,

  // Set Multiplex Ratio v = 0x3F
  // 0xA8, 0x3F,

  // Set Display Offset v = 0
  // 0xD3, 0x00,

  // Set Start Line (0)
  // 0x40,

  // Charge Pump Setting v = enable (0x14)
  // default is disabled
  0x8D, 0x14,

  // Set Segment Re-map (A0) | (b0001)
  // default is (b0000)
  0xA1,

  // Set COM Output Scan Direction
  0xC8,

  // Set COM Pins v
  // 0xDA, 0x12,

  // Set Contrast v = 0xCF
  0x81, 0xCF,

  // Set Precharge = 0xF1
  0xD9, 0xF1,

  // Set VCom Detect
  // 0xDB, 0x40,

  // Entire Display ON
  // 0xA4,

  // Set normal/inverse display
  // 0xA6,

  // Display On
  0xAF,

  // set display mode = horizontal addressing mode (0x00)
  0x20, 0x00,

  // set col address range
  // 0x21, 0x00, COLUMN_ADDRESS_END,

  // set page address range
  // 0x22, 0x00, PAGE_ADDRESS_END
};


Arduboy2Core::Arduboy2Core(){ }


/* Power Management */

void Arduboy2Core::idle()
{
    // nothing todo
}


void Arduboy2Core::boot()
{
  // Select the ADC input here so a delay isn't required in initRandomSeed()
  //ADMUX = RAND_SEED_IN_ADMUX;  // TODO ADC For RandomSeed
  bootSPI();
  bootPins();
  bootOLED();
  bootPowerSaving();    
}

void Arduboy2Core::safeMode()
{
  if (buttonsState() == UP_BUTTON)
  {
    digitalWriteRGB(RED_LED, RGB_ON);

  // TODO 未知功能，待解决
#ifndef ARDUBOY_CORE // for Arduboy core timer 0 should remain enabled
    // prevent the bootloader magic number from being overwritten by timer 0
    // when a timer variable overlaps the magic number location
    //power_timer0_disable();
#endif

    while (true) { }
  }
}

void Arduboy2Core::exitToBootloader()
{
  // TODO 重点，可能很有用的功能，待实现
  // cli();
  // // set bootloader magic key
  // // storing two uint8_t instead of one uint16_t saves an instruction
  // //  when high and low bytes of the magic key are the same
  // *(uint8_t *)MAGIC_KEY_POS = lowByte(MAGIC_KEY);
  // *(uint8_t *)(MAGIC_KEY_POS + 1) = highByte(MAGIC_KEY);
  // // enable watchdog timer reset, with 16ms timeout
  // wdt_reset();
  // WDTCSR = (_BV(WDCE) | _BV(WDE));
  // WDTCSR = _BV(WDE);
  // while (true) { }
}


void Arduboy2Core::bootPins()
{
    pinMode(OLED_DC_PIN, OUTPUT);
    pinMode(OLED_RES_PIN, OUTPUT);  

    pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
    pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

    pinMode(A_BUTTON_PIN, INPUT_PULLUP);
    pinMode(B_BUTTON_PIN, INPUT_PULLUP);

}

// Initialize the SPI interface for the display
void Arduboy2Core::bootSPI()
{
    spi.begin(OLED_D0_PIN,-1,OLED_D1_PIN,OLED_CS_PIN);
    spi.setFrequency(40000000);
}



// Write to the SPI bus (MOSI pin)
void Arduboy2Core::SPItransfer(uint8_t data)
{
  /*
   * The following NOP introduces a small delay that can prevent the wait
   * loop form iterating when running at the maximum speed. This gives
   * about 10% more speed, even if it seems counter-intuitive. At lower
   * speeds it is unnoticed.
   */
  spi.write(data);
}

// Shut down the display
void Arduboy2Core::displayOff()
{
  LCDCommandMode();
  SPItransfer(0xAE); // display off
  SPItransfer(0x8D); // charge pump:
  SPItransfer(0x10); //   disable
  delayShort(250);
  digitalWrite(OLED_RES_PIN, LOW);  
}

// Restart the display after a displayOff()
void Arduboy2Core::displayOn()
{
  bootOLED();
}

uint8_t Arduboy2Core::width() { return WIDTH; }

uint8_t Arduboy2Core::height() { return HEIGHT; }



void Arduboy2Core::bootOLED()
{
  // reset the display
  delayShort(200); 
  digitalWrite(OLED_RES_PIN, LOW);  
  delayShort(100); 
  digitalWrite(OLED_RES_PIN, HIGH); 

  // bitClear(CS_PORT, CS_BIT);

  LCDCommandMode();
  for (uint8_t i = 0; i < sizeof(lcdBootProgram); i++) {
    SPItransfer(*(lcdBootProgram + i));
  }
  LCDDataMode();
}

void Arduboy2Core::LCDDataMode()
{
    digitalWrite(OLED_DC_PIN, HIGH); 
}

void Arduboy2Core::LCDCommandMode()
{
    digitalWrite(OLED_DC_PIN, LOW); 
}


uint8_t Arduboy2Core::buttonsState()
{
  uint8_t buttons = 0;

  if (digitalRead(UP_BUTTON_PIN) == 0)    { buttons |= UP_BUTTON;   }
  if (digitalRead(DOWN_BUTTON_PIN) == 0)  { buttons |= DOWN_BUTTON; }
  if (digitalRead(LEFT_BUTTON_PIN) == 0)  { buttons |= LEFT_BUTTON; }
  if (digitalRead(RIGHT_BUTTON_PIN) == 0) { buttons |= RIGHT_BUTTON;}
  
  if (digitalRead(B_BUTTON_PIN) == 0) { buttons |= B_BUTTON; }
  if (digitalRead(A_BUTTON_PIN) == 0) { buttons |= A_BUTTON; }

  return buttons;
}


void Arduboy2Core::bootPowerSaving()
{
    // TODO F

}
// delay in ms with 16 bit duration
void Arduboy2Core::delayShort(uint16_t ms)
{
  delay((unsigned long) ms);
}

/* Drawing */

void Arduboy2Core::paint8Pixels(uint8_t pixels)
{
  SPItransfer(pixels);
}

void Arduboy2Core::paintScreen(const uint8_t *image)
{
  for (int i = 0; i < (HEIGHT*WIDTH)/8; i++)
  {
    SPItransfer(*(image + i));
  }
}

void Arduboy2Core::paintScreen(uint8_t image[], bool clear)
{
  uint8_t c;
  int i = 0;

  // the code to iterate the loop and get the next byte from the buffer is
  // executed while the previous byte is being sent out by the SPI controller
  while (i < (HEIGHT * WIDTH) / 8)
  {
    // get the next byte. It's put in a local variable so it can be sent as
    // as soon as possible after the sending of the previous byte has completed
    if (clear)
    {
      c = image[i];
      // clear the byte in the image buffer
      image[i++] = 0;
    }
    else
      c = image[i++];

    // put the next byte in the SPI data register. The SPI controller will
    // clock it out while the loop continues and gets the next byte ready
     spi.write(c);
  }

}

void Arduboy2Core::blank()
{
  for (int i = 0; i < (HEIGHT*WIDTH)/8; i++)
    SPItransfer(0x00);
}

// invert the display or set to normal
// when inverted, a pixel set to 0 will be on
void Arduboy2Core::invert(bool inverse)
{
  sendLCDCommand(inverse ? OLED_PIXELS_INVERTED : OLED_PIXELS_NORMAL);
}

// turn all display pixels on, ignoring buffer contents
// or set to normal buffer display
void Arduboy2Core::allPixelsOn(bool on)
{
  sendLCDCommand(on ? OLED_ALL_PIXELS_ON : OLED_PIXELS_FROM_RAM);
}

// flip the display vertically or set to normal
void Arduboy2Core::flipVertical(bool flipped)
{
  sendLCDCommand(flipped ? OLED_VERTICAL_FLIPPED : OLED_VERTICAL_NORMAL);
}

// flip the display horizontally or set to normal
void Arduboy2Core::flipHorizontal(bool flipped)
{
  sendLCDCommand(flipped ? OLED_HORIZ_FLIPPED : OLED_HORIZ_NORMAL);
}

void Arduboy2Core::sendLCDCommand(uint8_t command)
{
  LCDCommandMode();
  SPItransfer(command);
  LCDDataMode();
}

/* RGB LED */

void Arduboy2Core::setRGBled(uint8_t red, uint8_t green, uint8_t blue)
{
  // TODO F
}


void Arduboy2Core::setRGBled(uint8_t color, uint8_t val)
{
  // TODO F
}

void Arduboy2Core::freeRGBled()
{
  // TODO F
}

void Arduboy2Core::digitalWriteRGB(uint8_t red, uint8_t green, uint8_t blue)
{
  // TODO F
  // digitalWrite(RED_LED_PIN)
}



void Arduboy2Core::digitalWriteRGB(uint8_t color, uint8_t val)
{
  // TODO F
}


// Replacement main() that eliminates the USB stack code.
// Used by the ARDUBOY_NO_USB macro. This should not be called
// directly from a sketch.

void Arduboy2Core::mainNoUSB()
{
  // TODO F 重点，可能很有用的功能，待实现
}


void Arduboy2Core::setCPUSpeed8MHz()
{
  // No need to do
}