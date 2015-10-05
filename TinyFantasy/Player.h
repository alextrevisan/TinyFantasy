#ifndef PLAYER_H
#define PLAYER_H

#include "PCD8544_SPI.h"
enum KEYS
{
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
    USE = 4
};
class Player
{
    public:
        Player(PCD8544_SPI_FB& lcd);
        virtual ~Player();
        void drawPlayer(int x, int y, char dir);
        void move(KEYS p);
    protected:
    private:
        PCD8544_SPI_FB& LCD;
};

#endif // PLAYER_H
