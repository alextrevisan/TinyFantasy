#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "PCD8544_SPI.h"
#include "Effects.h"
#include "Player.h"
#include "MapManager.h"

PCD8544_SPI_FB lcd;
Effects effects(lcd);
MapManager mapManager(lcd);
Player player(lcd);

void printStart()
{
    File player = SD.open("splash/tiny.bin");
    if(player)
    {
        player.readBytes((char*)&lcd.m_Buffer, 504);
        player.close();
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

    //Splash screen
    printStart();
}

//Player start position
int x = 34;
int y = 20;
//Player start direction
char playerdir = 'd';

void loop()
{
    if(digitalRead(5)==LOW)
    {
        playerdir='u';
        y--;
    }
    if(digitalRead(6)==LOW)
    {
        playerdir='d';
        y++;
    }
    if(digitalRead(7)==LOW)
    {
        playerdir='l';
        x--;
    }
    if(digitalRead(3)==LOW)
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

    effects.setRaining(mapManager.isRaining());
    effects.drawEffects();

    /*lcd.print("x:");
    lcd.print(x);
    lcd.print(" y:");
    lcd.print(y);*/

    lcd.renderAll();
    delay(25);
}
