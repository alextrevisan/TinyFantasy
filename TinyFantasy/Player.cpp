#include "Player.h"
#include <SD.h>

Player::Player(PCD8544_SPI_FB& lcd)
:LCD(lcd)
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::drawPlayer(int x, int y, char dir)
{
    char pfile[17];
    sprintf(pfile,"player/p%c.bin",dir);
    //Player sprite, print only when black
    File player = SD.open(pfile);
    if(!player) return;
    int cur_x = x;
    int cur_y = y;
    for(int i = 0; i < 32; ++i)
    {
        int sprite = player.read();
        for(int yy = 0; yy < 8; ++yy)
        {
            if(bitRead(sprite, yy))
            {
                LCD.setPixel(cur_x, yy+cur_y, 1);
            }
        }
        ++cur_x;
        if(cur_x>=16+x)
        {
            cur_x=x;
            cur_y+=8;
        }
    }
    player.close();
    sprintf(pfile,"player/p%c_in.bin",dir);
    //Player internal sprite, print to remove ghost effect from sprite
    player = SD.open(pfile);
    if(!player) return;
    cur_x = x;
    cur_y = y;
    for(int i = 0; i < 32; ++i)
    {
        int sprite = player.read();
        for(int yy = 0; yy < 8; ++yy)
        {
            if(bitRead(sprite, yy))
            {
                LCD.setPixel(cur_x, yy+cur_y, 0);
            }
        }
        ++cur_x;
        if(cur_x>=16+x)
        {
            cur_x=x;
            cur_y+=8;
        }
    }
    player.close();
}

void Player::move(PlayerDirection p)
{
    switch(p)
    {
    case UP:
        break;
    case DOWN:
        break;
    case LEFT:
        break;
    case RIGHT:
        break;
    }
}

