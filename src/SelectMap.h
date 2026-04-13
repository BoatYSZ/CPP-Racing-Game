#pragma once
#include "State.h"
#include "SCYSY3Button.h"
#include "SCYSY3Image.h"
class SelectMap :
    public State
{
public:
    SelectMap(BaseEngine* pEngine);
    virtual ~SelectMap();
    virtual void InitializeState();
    virtual void setBackGroundForState();

    virtual void virtPreDraw();
    virtual void virtPostDraw();

    Prev* prev;
    Next* next;
    Start* start;
    Back* back;
    int i_currentImage = 0;
    std::vector<SCYSY3Image*> v_Image;
    int currentMap = 0;
};

