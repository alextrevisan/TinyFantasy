#ifndef EFFECTS_H
#define EFFECTS_H

#include "PCD8544_SPI.h"

class Effects
{
    public:
        Effects(PCD8544_SPI_FB& lcd);
        ~Effects();
        void drawEffects();
        void setRaining(bool r);
    protected:
    private:
        bool raining;
        void rain();
        PCD8544_SPI_FB& LCD;
};

#endif // EFFECTS_H
