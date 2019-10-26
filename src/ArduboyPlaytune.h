#ifndef ARDUBOY_PLAYTUNE_H
#define ARDUBOY_PLAYTUNE_H

#include <Arduino.h>

#define AVAILABLE_TIMERS  2

// score commands
#define TUNE_OP_PLAYNOTE  0x90  /* play a note: low nibble is generator #, note is next byte */
#define TUNE_OP_STOPNOTE  0x80  /* stop a note: low nibble is generator # */
#define TUNE_OP_RESTART   0xe0  /* restart the score from the beginning */
#define TUNE_OP_STOP      0xf0  /* stop playing */


class ArduboyPlaytune
{
public:
  ArduboyPlaytune(boolean (*outEn)());

  void static initChannel(byte pin);

  void playScore(const byte *score);

  void stopScore();

  void closeChannels();

  boolean playing();

  void tone(unsigned int frequency, unsigned long duration);

  void toneMutesScore(boolean mute);

private:
  void static playNote(byte chan, byte note);
  void static stopNote(byte chan);

public:
  // called via interrupt. Should not be called by a program.
  void static step();
};

#endif
