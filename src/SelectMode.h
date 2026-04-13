#pragma once

#include "State.h"
#include "SCYSY3Button.h"
#include "TitleWheel.h"
class SelectMode :
    public State
{
public:
    SelectMode(BaseEngine* pEngine);
    virtual ~SelectMode();
    virtual void InitializeState();
    virtual void setBackGroundForState();
    void virtKeyDown(int iKeyCode);
    
    virtual void virtPreDraw();
    virtual void virtPostDraw();
    SCYSY3Image SPEEDpp;
    TitleWheel* titleWheel;
    SeleteAMap* seleteAMap;
    Custom* custom;
};