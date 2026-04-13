#pragma once
#include "BaseEngine.h"
#include "SCYSY3DisplayableObject.h"


class FollowMouse:
    public SCYSY3DisplayableObject
{
    
public:
    FollowMouse(BaseEngine* pEngine, State* belong)
        : SCYSY3DisplayableObject(300, 300, pEngine, 100, 50, true, belong)
        , p_BelongState(belong)
    {
        m_iCurrentScreenX = 500; // Starting position on the screen
        m_iCurrentScreenY = 500;
        m_iDrawWidth = 50;	// Width of drawing area
        m_iDrawHeight = 50;	// Height of drawing area
    }
    //~FollowMouse();
    void virtDraw();
    void virtDoUpdate(int iCurrentTime);

    int mouseX =500;
    int mouseY =500;
    int color = 0x808080;
    char chr[2] = { '?','\0' };
    
    void virtMouseDown(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);
    State* p_BelongState;
};

