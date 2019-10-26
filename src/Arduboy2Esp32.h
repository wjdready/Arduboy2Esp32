#ifndef _ARDUBOY2ESP32_H
#define _ARDUBOY2ESP32_H


#include "Arduboy2Esp32Core.h"
#include "Arduboy2Esp32Audio.h"
#include <Arduino.h>
#include <Print.h>

#define  max(x,y)    ((x) > (y) ? (x) : (y))

// If defined, it is safe to draw outside of the screen boundaries.
// Pixels that would exceed the display limits will be ignored.
#define PIXEL_SAFE_MODE

// pixel colors
#define BLACK 0  /**< Color value for an unlit pixel for draw functions. */
#define WHITE 1  /**< Color value for a lit pixel for draw functions. */

#define INVERT 2

#define CLEAR_BUFFER true /**< Value to be passed to `display()` to clear the screen buffer. */


struct Rect
{
  int16_t x;      /**< The X coordinate of the top left corner */
  int16_t y;      /**< The Y coordinate of the top left corner */
  uint8_t width;  /**< The width of the rectangle */
  uint8_t height; /**< The height of the rectangle */

  Rect() = default;

  Rect(int16_t x, int16_t y, uint8_t width, uint8_t height);
};



struct Point
{
  int16_t x; /**< The X coordinate of the point */
  int16_t y; /**< The Y coordinate of the point */

  Point() = default;

  Point(int16_t x, int16_t y);
};



class Arduboy2Base : public Arduboy2Core
{
 friend class Arduboy2Ex;

 public:
  Arduboy2Base();

  Arduboy2Audio audio;

  void begin();

  void flashlight();

  void systemButtons();

  void bootLogo();

  void bootLogoCompressed();

  void bootLogoSpritesSelfMasked();

  void bootLogoSpritesOverwrite();

  void bootLogoSpritesBSelfMasked();

  void bootLogoSpritesBOverwrite();

  void bootLogoShell(void (*drawLogo)(int16_t));

  virtual void bootLogoExtra();

  void waitNoButtons();

  void clear();

  void display();

  void display(bool clear);

  static void drawPixel(int16_t x, int16_t y, uint8_t color = WHITE);

  uint8_t getPixel(uint8_t x, uint8_t y);

  void drawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color = WHITE);

  void drawCircleHelper(int16_t x0, int16_t y0, uint8_t r, uint8_t corners, uint8_t color = WHITE);

  void fillCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color = WHITE);

  void fillCircleHelper(int16_t x0, int16_t y0, uint8_t r, uint8_t sides, int16_t delta, uint8_t color = WHITE);

  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color = WHITE);

  void drawRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color = WHITE);

  void drawFastVLine(int16_t x, int16_t y, uint8_t h, uint8_t color = WHITE);

  void drawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color = WHITE);

  void fillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color = WHITE);

  void fillScreen(uint8_t color = WHITE);

  void drawRoundRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color = WHITE);

  void fillRoundRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t r, uint8_t color = WHITE);

  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color = WHITE);

  void fillTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color = WHITE);

  static void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color = WHITE);

  void drawSlowXYBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color = WHITE);

  static void drawCompressed(int16_t sx, int16_t sy, const uint8_t *bitmap, uint8_t color = WHITE);

  uint8_t* getBuffer();

  unsigned long generateRandomSeed();

  void initRandomSeed();

  // Swap the values of two int16_t variables passed by reference.
  void swap(int16_t& a, int16_t& b);

  void setFrameRate(uint8_t rate);

  void setFrameDuration(uint8_t duration);

  bool nextFrame();

  bool nextFrameDEV();

  bool everyXFrames(uint8_t frames);

  int cpuLoad();

  bool pressed(uint8_t buttons);

  bool notPressed(uint8_t buttons);

  void pollButtons();

  bool justPressed(uint8_t button);

  bool justReleased(uint8_t button);

  static bool collide(Point point, Rect rect);

  static bool collide(Rect rect1, Rect rect2);

  uint16_t readUnitID();

  void writeUnitID(uint16_t id);

  uint8_t readUnitName(char* name);

  void writeUnitName(char* name);

  bool readShowBootLogoFlag();

  void writeShowBootLogoFlag(bool val);

  bool readShowUnitNameFlag();

  void writeShowUnitNameFlag(bool val);

  bool readShowBootLogoLEDsFlag();

  void writeShowBootLogoLEDsFlag(bool val);

  uint16_t frameCount;

  static uint8_t sBuffer[(HEIGHT*WIDTH)/8];

 protected:
  // helper function for sound enable/disable system control
  void sysCtrlSound(uint8_t buttons, uint8_t led, uint8_t eeVal);

  // functions passed to bootLogoShell() to draw the logo
  static void drawLogoBitmap(int16_t y);
  static void drawLogoCompressed(int16_t y);
  static void drawLogoSpritesSelfMasked(int16_t y);
  static void drawLogoSpritesOverwrite(int16_t y);
  static void drawLogoSpritesBSelfMasked(int16_t y);
  static void drawLogoSpritesBOverwrite(int16_t y);

  // For button handling
  uint8_t currentButtonState;
  uint8_t previousButtonState;

  // For frame funcions
  uint8_t eachFrameMillis;
  uint8_t thisFrameStart;
  bool justRendered;
  uint8_t lastFrameDurationMs;
};

//
class Arduboy2 : public Print, public Arduboy2Base
{
 friend class Arduboy2Ex;

 public:
  Arduboy2();

  using Print::write;

  void bootLogoText();

  virtual void bootLogoExtra();

  virtual size_t write(uint8_t);

  void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);

  void setCursor(int16_t x, int16_t y);

  int16_t getCursorX();

  int16_t getCursorY();

  void setTextColor(uint8_t color);

  uint8_t getTextColor();

  void setTextBackground(uint8_t bg);

  uint8_t getTextBackground();

  void setTextSize(uint8_t s);

  uint8_t getTextSize();

  void setTextWrap(bool w);

  bool getTextWrap();

  void clear();

 protected:
  int16_t cursor_x;
  int16_t cursor_y;
  uint8_t textColor;
  uint8_t textBackground;
  uint8_t textSize;
  bool textWrap;
};


#endif
