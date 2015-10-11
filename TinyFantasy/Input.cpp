#include "Input.h"
#include <Arduino.h>
                        //UP    DOWN  LEFT  RIGHT USE
bool Input::keyDown[5] = {false,false,false,false,false};

void Input::readKeys()
{
    for(int i = 0; i < 5;++i)
    {
        keyDown[i] = false;
    }
    if(digitalRead(5)==LOW)
    {
        keyDown[0] = true;
    }
    if(digitalRead(6)==LOW)
    {
        keyDown[1] = true;
    }
    if(digitalRead(7)==LOW)
    {
        keyDown[2] = true;
    }
    if(digitalRead(3)==LOW)
    {
        keyDown[3] = true;
    }
    if(digitalRead(2)==LOW)
    {
        keyDown[4] = true;
    }
}

bool Input::isKeyDown(int key)
{
    return keyDown[key];
}

void Input::waitKeyDown(int key)
{
    while(!keyDown[key])
        readKeys();
}

