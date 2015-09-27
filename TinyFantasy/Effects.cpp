#include "Effects.h"

Effects::Effects(PCD8544_SPI_FB& lcd)
:LCD(lcd),raining(false)
{
}

Effects::~Effects()
{
}

void Effects::drawEffects()
{
    if(raining)
        rain();
}

void Effects::setRaining(bool r)
{
    raining = r;
}

void Effects::rain()
{
    static short dropy = 0;
    static short dropx = 0;
    for(int x = 0; x < 84; x+=8)
    {
        for(int y = 0; y < 48; y+=8)
        {
            short dx = x+dropx;
            short dy = y+dropy;
            LCD.setPixel((dx>84?dx-84:dx), (dy>48?dy-48:dy),1);
            LCD.setPixel(1+(dx>84?dx-84:dx),1+(dy>48?dy-48:dy),1);
        }
    }
    dropy++;
    if(dropy>48)dropy=0;
    dropx++;
    if(dropx>84)dropx=0;
}


