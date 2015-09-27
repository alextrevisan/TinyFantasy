#ifndef PLAYER_H
#define PLAYER_H

#include "PCD8544_SPI.h"
enum PlayerDirection
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};
class Player
{
    public:
        Player(PCD8544_SPI_FB& lcd);
        virtual ~Player();
        void drawPlayer(int x, int y, char dir);
        void move(PlayerDirection p);
    protected:
    private:
        PCD8544_SPI_FB& LCD;
};

#endif // PLAYER_H
