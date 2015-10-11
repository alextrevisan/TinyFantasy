#include <Arduino.h>
#include <SPI.h>
#include "SDCardManager.h"
#include "PCD8544_SPI.h"
#include "Effects.h"
#include "Player.h"
#include "MapManager.h"
#include "Input.h"
#include "Menu.h"

SdFat SD;
PCD8544_SPI_FB lcd;

Menu menu(lcd);
Effects effects(lcd);
MapManager mapManager(lcd);
Player player(lcd);

void printStart()
{
    File menu = SD.open("splash/tiny.bin");
    if(menu)
    {
        menu.readBytes((char*)&lcd.m_Buffer, 504);
        menu.close();
    }
    else
    {
        lcd.print("ERROR LOADING FILE ");
    }
    lcd.renderAll();
    delay(3000);

}

void setup()
{

	Serial.begin(9600);
    lcd.begin(false, 0xBD, 0x04, 0x14);
    lcd.clear();
    if(!SD.begin(4))
    {
        lcd.print("ERRO INITIALIZING SD");
        Serial.println("ERRO INITIALIZING SD");
        lcd.renderAll();
        while(1);
    }
    pinMode(5,INPUT_PULLUP);//UP
    pinMode(6,INPUT_PULLUP);//DOWN
    pinMode(7,INPUT_PULLUP);//LEFT
    pinMode(3,INPUT_PULLUP);//RIGHT

    pinMode(2,INPUT_PULLUP);//USE

    //Splash screen
    printStart();
}

//Player start position
int x = 34;
int y = 20;
//Player start direction
char playerdir = 'd';
bool lastRainStatus = false;

void loop()
{
    Input::readKeys();
    if(menu.onMenu()!=NO_MENU)
    {
        menu.drawMenu();
    }
    else
    {
        if(Input::isKeyDown(Input::UP))
        {
            playerdir='u';
            y--;
        }
        if(Input::isKeyDown(Input::DOWN))
        {
            playerdir='d';
            y++;
        }
        if(Input::isKeyDown(Input::LEFT))
        {
            playerdir='l';
            x--;
        }
        if(Input::isKeyDown(Input::RIGHT))
        {
            playerdir='r';
            x++;
        }

        //Current map limits
        if(y<0)y=0;
        if(y>80)y=80;
        if(x<0)x=0;
        if(x>112)x=112;

        mapManager.drawMap(x,y);
        player.drawPlayer(x-(floor(x/64)*64),y-(floor(y/48)*48), playerdir);

        if(lastRainStatus!=mapManager.isRaining() && lastRainStatus == false)
        {
            lastRainStatus = mapManager.isRaining();
            menu.setMenu(RAINING);
        }
        effects.setRaining(mapManager.isRaining());
        effects.drawEffects();
    }

    /*lcd.print("x:");
    lcd.print(x);
    lcd.print(" y:");
    lcd.print(y);*/

    lcd.renderAll();
    delay(25);
}
