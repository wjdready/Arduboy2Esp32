/**
 * @file Arduboy2Audio.cpp
 * \brief
 * The Arduboy2Audio class for speaker and sound control.
 */

#include "Arduboy2Esp32.h"
#include "Arduboy2Esp32Audio.h"

bool Arduboy2Audio::audio_enabled = false;

void Arduboy2Audio::on()
{
  // fire up audio pins by seting them as outputs
  // TODO F
  audio_enabled = true;
}

void Arduboy2Audio::off()
{
  audio_enabled = false;
  // TODO F
}

void Arduboy2Audio::toggle()
{
  if (audio_enabled)
    off();
  else
    on();
}

void Arduboy2Audio::saveOnOff()
{
  // TODO 待实现
  //EEPROM.update(EEPROM_AUDIO_ON_OFF, audio_enabled);
}

void Arduboy2Audio::begin()
{
  // TODO 待实现
  // if (EEPROM.read(EEPROM_AUDIO_ON_OFF))
  //   on();
  // else
  //   off();
}

bool Arduboy2Audio::enabled()
{
  return audio_enabled;
}
