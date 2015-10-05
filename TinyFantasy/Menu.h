#ifndef MENU_H
#define MENU_H

#include "PCD8544_SPI.h"

class Menu
{
    public:
        Menu(PCD8544_SPI_FB& lcd);
        virtual ~Menu();
        unsigned short onMenu();
        void drawMenu();
    protected:
    private:
        PCD8544_SPI_FB& LCD;
        int menuItem;
        short selectIndex;
        bool isPressed;
};

#endif // MENU_H
