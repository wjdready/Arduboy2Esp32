#ifndef _ARDUBOY2ESP32_AUDIO_H
#define _ARDUBOY2ESP32_AUDIO_H

#include <Arduino.h>

class Arduboy2Audio
{
    //TODO 未知
    //  friend class Arduboy2Ex;

 public:
    void static begin();
    void static on();
    void static off();
    void static toggle();
    void static saveOnOff();
    bool static enabled();

 protected:
    bool static audio_enabled;
};

#endif