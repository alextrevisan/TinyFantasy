#include "Menu.h"
#include "Input.h"

#include "SDCardManager.h"

Menu::Menu(PCD8544_SPI_FB& lcd)
:LCD(lcd)
,menuItem(1)
,selectIndex(0)
,isPressed(false)
{
    //ctor
}

unsigned short Menu::onMenu()
{
    return menuItem;
}

void Menu::drawMenu()
{
    //LCD.clear();
    if(menuItem==0)return;
    switch(menuItem)
    {
    case 1:
        /*{
            short x[] = {4, 50};
            short y[] = {40, 40};
            uint8_t selector[8];
            sprintf(menuName, "menu/select.bin", menuItem);
            menu = SD.open(menuName);
            menu.readBytes((char*)selector,8);
            if(Input::isKeyDown(2) || Input::isKeyDown(3))
            {
                selectIndex++;
                if(selectIndex>1)
                    selectIndex=0;
            }
            LCD.writeBitmap(selector,x[selectIndex], y[selectIndex], 8,1);
            break;
        }*/
        {
            File menu = SD.open("menu/menu1.bin");
            if(menu)
            {
                menu.readBytes((char*)&LCD.m_Buffer, 504);
                menu.close();
            }
            else
            {
                LCD.print(F("ERROR LOADING FILE"));
            }
            short x[] = {1, 48};
            short y[] = {38, 38};
            menu = SD.open("menu/select.bin");
            if(Input::isKeyDown(Input::LEFT) || Input::isKeyDown(Input::RIGHT))
            {
                if(!isPressed)
                    selectIndex++;

                if(selectIndex>1)
                    selectIndex=0;

                isPressed = true;
            }
            else
            {
                isPressed = false;
            }
            for(int i = 0; i < 8; ++i)
            {
                int sprite = menu.read();
                for(int yy = 0; yy < 8; ++yy)
                {
                    if(bitRead(sprite, yy))
                    {
                        LCD.setPixel(x[selectIndex] + i, y[selectIndex] + yy, 1);
                    }
                }
            }
            menu.close();
            if(Input::isKeyDown(Input::USE))
            {
                menuItem = 0;
            }
        }
    default:
        break;
    }
    LCD.renderAll();
}
Menu::~Menu()
{
    //dtor
}
