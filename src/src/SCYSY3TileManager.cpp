#include "header.h"
#include "SCYSY3TileManager.h"
#include "Point.h"
#include "State.h"
#include "CreateMap.h"
void SCYSY3TileManager::virtDrawTileAt(
	BaseEngine* pEngine,
	DrawingSurface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY) const
{
	int iMapValue = getMapValue(iMapX, iMapY);
	pSurface->mySDLLockSurface();
	noRoad.renderImage(pSurface, 0, 0, iStartPositionScreenX, iStartPositionScreenY, noRoad.getWidth(), noRoad.getHeight());
	if (iMapValue > 0) {
		bool up = false;
		bool down = false;
		bool left = false;
		bool right = false;
		CreateMap* p = static_cast<CreateMap*>(p_belongState);
		Point current = p->RoadList[iMapValue-1];
		Point prev = iMapValue != 1 ? p->RoadList[iMapValue-2] : p->RoadList[p->RoadList.size()-1];
		Point next = iMapValue != p->RoadList.size() ? p->RoadList[iMapValue] : p->RoadList[0];
		if (abs(next.x - prev.x) == 2) {
			left = true;
			right = true;
		}
		else if (abs(next.y - prev.y) == 2) {
			up = true;
			down = true;
		}

		if (next.y + prev.y - current.y * 2 == 1) {
			down = true;
		}
		if (next.x + prev.x - current.x * 2 == 1) {
			right = true;
		}
		if (next.y + prev.y - current.y * 2 == -1) {
			up = true;
		}
		if ((next.x + prev.x - current.x * 2 == -1)) {
			left = true;
		}

		
		if (up) {
			if (left) {
				UL.renderImage(p->pState_ForeSurface, 0 , 0 ,m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
			}
			else if (right)
			{
				UR.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
			}
			else if (down) {
				UD.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
			}
		}
		else if (down) {
			if (left) {
				DL.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
			}
			else if (right) {
				DR.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
			}
		}
		else if (left && right) {
			LR.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
		}
		else {
			Unknown.renderImage(p->pState_ForeSurface, 0, 0, m_iBaseScreenX + getTileWidth() * current.x, m_iBaseScreenY + getTileHeight() * current.y, getTileWidth(), getTileHeight());
		}
		
	}
	pSurface->mySDLUnlockSurface();
}

int SCYSY3TileManager::getTileCenterX(int iMapX, int iMapY) {
	return m_iTileWidth * (iMapX) + m_iTileWidth / 2 + m_iBaseScreenX;
}

int SCYSY3TileManager::getTileCenterY(int iMapX, int iMapY) {
	return m_iTileHeight * (iMapY)+m_iTileHeight / 2 + m_iBaseScreenY;
}

int SCYSY3TileManager::getTileX(int iMapX, int iMapY) {
	return m_iTileWidth * (iMapX) + m_iBaseScreenX;
}
int SCYSY3TileManager::getTileY(int iMapX, int iMapY) {
	return m_iTileWidth * (iMapY)+  m_iBaseScreenY;
}