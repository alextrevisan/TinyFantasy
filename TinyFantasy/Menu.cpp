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

void Menu::setMenu(int item)
{
    menuItem = item;
}
void Menu::drawMenu()
{
    //LCD.clear();
    if(menuItem==NO_MENU)return;
    switch(menuItem)
    {
    case MAINMENU:
        mainMenu();
        break;
    case HISTORY1:
        story1();
        break;
    case RAINING:
        rainingMessage();
        break;
    default:
        break;
    }
    LCD.renderAll();
}

void Menu::mainMenu()
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
        if(selectIndex==0)
            menuItem = 2;
        else
            menuItem = 0;
    }
}

void Menu::story1()
{
    static short count = 0;
    if(count<=8)
    {
        char name[19];
        sprintf(name,"history/block%d.bin", ((short)floor(count/3)) +1);

        File menu = SD.open(name);
        if(menu)
        {
            menu.readBytes((char*)&LCD.m_Buffer, 504);
            menu.close();
        }
        else
        {
            LCD.print(F("ERROR LOADING FILE "));
            LCD.print(name);
        }
        count++;
    }
    else
    {
        if(count == 9)
        {
            File menu = SD.open("history/h1-1.bin");
            if(menu)
            {
                menu.readBytes((char*)&LCD.m_Buffer, 504);
                menu.close();
            }
        }
        if(count == 10)
        {
            File menu = SD.open("history/h1-2.bin");
            if(menu)
            {
                menu.readBytes((char*)&LCD.m_Buffer, 504);
                menu.close();
            }
        }
        if(count == 11)
        {
            menuItem = 0;
        }

        if(Input::isKeyDown(Input::USE))
        {
            if(!isPressed)
                count++;
            isPressed = true;
        }
        else
        {
            isPressed = false;
        }
    }

}
void Menu::rainingMessage()
{
    File menu = SD.open("history/rain.bin");
    if(menu)
    {
        menu.readBytes((char*)&LCD.m_Buffer, 504);
        menu.close();
    }
    if(Input::isKeyDown(Input::USE))
    {
        if(!isPressed)
            menuItem = 0;
        isPressed = true;
    }
    else
    {
        isPressed = false;
    }
}



Menu::~Menu()
{
    //dtor
}
