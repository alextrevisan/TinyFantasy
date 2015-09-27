#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "PCD8544_SPI.h"

class MapManager
{
    public:
        MapManager(PCD8544_SPI_FB& lcd);
        virtual ~MapManager();
        void drawMap(int& x, int& y);
        bool isRaining(){return raining;}
    protected:
    private:
        int location;
        bool raining;
        PCD8544_SPI_FB& LCD;
};

#endif // MAPMANAGER_H
