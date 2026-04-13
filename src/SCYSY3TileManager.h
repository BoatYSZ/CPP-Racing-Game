#pragma once
#include "TileManager.h"
#include "SCYSY3Image.h"
#include "State.h"
class SCYSY3TileManager :
    public TileManager
{
public:
    SCYSY3TileManager(int iTileHeight, int iTileWidth, int iMapWidth, int iMapHeight, BaseEngine* pEngine, State* p_belongState)
        : TileManager(iTileHeight, iTileWidth, iMapWidth, iMapHeight)
        , noRoad("noRoad.png")
        , UD("Mini_Road_up_down.png")
        , LR("Mini_Road_left_right.png")
        , UL("Mini_Road_up_left.png")
        , UR("Mini_Road_up_right.png")
        , DL("Mini_Road_down_left.png")
        , DR("Mini_Road_down_right.png")
        , Unknown("Unknown.png")
        , pEngine(pEngine)
        , p_belongState(p_belongState)
    {
        m_iBaseScreenX = 225;
        m_iBaseScreenY = 50;
    }

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

    int getTileCenterX(int iMapX, int iMapY);
    int getTileCenterY(int iMapX, int iMapY);
    int getTileX(int iMapX, int iMapY);
    int getTileY(int iMapX, int iMapY);
    SCYSY3Image noRoad;
    SCYSY3Image UD;
    SCYSY3Image LR;
    SCYSY3Image UL;
    SCYSY3Image UR;
    SCYSY3Image DL;
    SCYSY3Image DR;
    SCYSY3Image Unknown;
    BaseEngine* pEngine;
    State* p_belongState;
    unsigned int colorForSingleTile = 0x000011;
};

