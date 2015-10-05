#include "MapManager.h"
#include "SDCardManager.h"

MapManager::MapManager(PCD8544_SPI_FB& lcd)
:LCD(lcd), raining(false)
{
    //ctor
}

MapManager::~MapManager()
{
    //dtor
}

void MapManager::drawMap(int& x, int& y)
{
    char mapname[16];
    if(x>95 && x < 102 && y < 15 && y > 12 && location == 0)
    {
        location = 1;
        x = 34;
        y = 32;
        raining = false;
    }
    else if(x < 3 && y < 3 && location == 1)
    {
        location = 2;
        x = 8;
        y = 5;
        raining = false;
    }
    else if(x < 3 && y < 3 && location == 2)
    {
        location = 1;
        x = 8;
        y = 5;
        raining = false;
    }
    else if(x >28 && x < 42 && y >32 && location == 1)
    {
        location = 0;
        x = 95;
        y = 20;
        raining = true;
    }
    switch(location)
    {
    case 0:
        sprintf(mapname,"map/m%dx%d.bin",x/64,y/48);
        break;
    case 1:
        sprintf(mapname,"map/house1.bin");
        break;
    case 2:
        sprintf(mapname,"map/house2.bin");
        break;
    }
    File map = SD.open(mapname);
    if(map)
    {
        map.readBytes((char*)&LCD.m_Buffer, 504);
        map.close();
    }
    else
    {
        LCD.print("ERROR LOADING FILE ");
        LCD.print(mapname);
    }
}
