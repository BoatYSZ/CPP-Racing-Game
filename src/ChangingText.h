#pragma once
#include "BaseEngine.h"
class ChangingText :
    public DisplayableObject
{
public:
    ChangingText::ChangingText(BaseEngine* pEngine, int x, int y)
        : DisplayableObject(x, y, pEngine, 100, 200, true),
        pDisplayContent("012345678")
    {
    }
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);

    char pDisplayContent[10] = "0";
    int iTime = 0;
    int iPreTime = 0;
    int x = 20;
    int y = 20;
};

