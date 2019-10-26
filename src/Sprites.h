#ifndef _Sprites_h
#define _Sprites_h
#include "SpritesCommon.h"
#include <stdint.h>

class Sprites
{
  public:
        static void drawExternalMask(int16_t x, int16_t y, const uint8_t *bitmap,
                                 const uint8_t *mask, uint8_t frame, uint8_t mask_frame);
        static void drawPlusMask(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
        static void drawOverwrite(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
        static void drawErase(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
        static void drawSelfMasked(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
        static void draw(int16_t x, int16_t y,
                     const uint8_t *bitmap, uint8_t frame,
                     const uint8_t *mask, uint8_t sprite_frame,
                     uint8_t drawMode);
        static void drawBitmap(int16_t x, int16_t y,
                           const uint8_t *bitmap, const uint8_t *mask,
                           uint8_t w, uint8_t h, uint8_t draw_mode);
};



#endif


