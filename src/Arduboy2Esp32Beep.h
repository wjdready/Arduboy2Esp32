#ifndef __ARDUBOY2ESP32_H
#define __ARDUBOY2ESP32_H
#include <stdint.h>

class BeepPin1
{
 public:
    static uint8_t duration;
    static void begin();
    static void tone(uint16_t count);
    static void tone(uint16_t count, uint8_t dur);
    static void timer();
    static void noTone();
    // TODO 待实现 争议
    // static constexpr uint16_t freq(const float hz)
    static constexpr uint16_t freq(const float hz)
    {
        // TODO 待实现
        // return (uint16_t) (((F_CPU / 8 / 2) + (hz / 2)) / hz) - 1;
        return 1;
    }
};


class BeepPin2
{
  public:
    static uint8_t duration;
    static void begin();
    static void tone(uint16_t count);
    static void tone(uint16_t count, uint8_t dur);
    static void timer();
    static void noTone();
    // static constexpr uint16_t freq(const float hz)
    static constexpr uint16_t freq(const float hz)
    {
        // TODO 待实现 争议
        //return (uint16_t) (((F_CPU / 128 / 2) + (hz / 2)) / hz) - 1;
        return 1;
    }
};

#endif