#pragma once
#include "BaseEngine.h"
class AutoMoving :
    public DisplayableObject
{
public:
    AutoMoving(BaseEngine* pEngine)
        :DisplayableObject(pEngine)
    {
        m_iCurrentScreenX = 200; // Starting position on the screen
        m_iCurrentScreenY = 700;
        m_iDrawWidth = 60;	// Width of drawing area
        m_iDrawHeight = 60;	// Height of drawing area
    }
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);

    bool direction = true;
    int speed = 3;
    int color = 0x000000;
};

