#pragma once
#include "State.h"
#include "SCYSY3Button.h"
#include "SCYSY3TileManager.h"
#include "Point.h"
class CreateMap :
    public State
{
public:
    CreateMap(BaseEngine* pEngine);
    virtual ~CreateMap();
    virtual void InitializeState();
    virtual void setBackGroundForState();
    void CreateMap::virtMouseDown(int iButton, int iX, int iY);

    virtual void PreUpdate();
    virtual void virtPreDraw();
    virtual void virtPostDraw();
    SCYSY3TileManager CostomMap;
    SCYSY3Image noRoad;
    Back backButton;
    StartCostom startButton;
    int MapLength = 0;
    std::vector<Point> RoadList;
    bool validMap = false;
    Point startBlock;
    //FollowMouse* followMouse;
    //SCYSY3DisplayableObject* MainControl;
};

