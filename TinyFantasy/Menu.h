#ifndef MENU_H
#define MENU_H

#include "PCD8544_SPI.h"

enum
{
    NO_MENU,
    MAINMENU,
    HISTORY1,
    RAINING,
};

class Menu
{
    public:
        Menu(PCD8544_SPI_FB& lcd);
        virtual ~Menu();
        unsigned short onMenu();
        void drawMenu();
        void setMenu(int item);
    protected:
    private:
        PCD8544_SPI_FB& LCD;
        int menuItem;
        short selectIndex;
        bool isPressed;
        void mainMenu();
        void story1();
        void rainingMessage();
};

#endif // MENU_H
