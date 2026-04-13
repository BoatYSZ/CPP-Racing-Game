#pragma once
#include "TileManager.h"
class MyTileManager :
    public TileManager
{
public:
    MyTileManager(int x, int y, int width, int height)
        : TileManager(x, y, width, height)
    {
    }

    virtual void virtDrawTileAt(
        BaseEngine* pEngine,
        DrawingSurface* pSurface,
        int iMapX, int iMapY,
        int iStartPositionScreenX, int iStartPositionScreenY) const override;

};

