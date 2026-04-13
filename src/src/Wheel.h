#pragma once
#include "SCYSY3DisplayableObject.h"

class Wheel :
    public SCYSY3DisplayableObject
{
public:
    Wheel(SCYSY3DisplayableObject* relative_object1, int position);
    virtual void virtDoUpdate(int iCurrentTime);
    virtual void virtDraw();
    int position;
};

