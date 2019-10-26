#include <Arduino.h>
#include "Arduboy2Esp32Beep.h"


uint8_t BeepPin1::duration = 0;


void BeepPin1::begin()
{
    // TODO F
}

void BeepPin1::tone(uint16_t count)
{
    tone(count, 0);
}

void BeepPin1::tone(uint16_t count, uint8_t dur)
{
    // TODO F
}

void BeepPin1::timer()
{
    // TODO F
    if (duration && (--duration == 0)) {
        // set normal mode (which disconnects the pin)
    }
}

void BeepPin1::noTone()
{
    // TODO F
    // set normal mode (which disconnects the pin)
}


void BeepPin2::begin()
{
    // TODO F
}

void BeepPin2::tone(uint16_t count)
{
    // TODO F
    tone(count, 0);
}


void BeepPin2::tone(uint16_t count, uint8_t dur)
{
    // TODO F
}

void BeepPin2::timer()
{
    // TODO F
    if (duration && (--duration == 0)) {
        // set normal mode (which disconnects the pin)
    }
}

void BeepPin2::noTone()
{
    // TODO F
    duration = 0;
    // set normal mode (which disconnects the pin)
}

