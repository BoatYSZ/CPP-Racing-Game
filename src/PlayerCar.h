#pragma once
#include "Car.h"

class PlayerCar :
    public Car
{
public:
    PlayerCar(
        BaseEngine* pEngine
        , State* belong
        , double xStart
        , double yStart
        , bool useTopLeftFor00
        , SCYSY3DisplayableObject* relative_object
    );
    void virtMouseDown(int iButton, int iX, int iY);
    void virtDoUpdate(int iCurrentTime);
    int Round = 3;
};

