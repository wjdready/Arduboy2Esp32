#include "Arduboy2Esp32.h"
#include <stdint.h>


Arduboy2 arduboy;

void setup() 
{
    arduboy.begin();
    arduboy.setFrameRate(15);    
}




void loop() 
{
    if (!(arduboy.nextFrame()))
        return;

    // first we clear our screen to black
    arduboy.clear();

    // we set our cursor 5 pixels to the right and 10 down from the top
    // (positions start at 0, 0)
    arduboy.setCursor(4, 9);

    // then we print to screen what is in the Quotation marks ""
    arduboy.print(F("Hello World"));
    // arduboy.print(arduboy.buttonsState());
    // arduboy.drawChar(0,0,'A',WHITE,BLACK,1);
    // then we finaly we tell the arduboy to display what we just wrote to the display
    arduboy.display();
}