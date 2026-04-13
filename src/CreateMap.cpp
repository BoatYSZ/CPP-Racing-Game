#include "header.h"
#include "CreateMap.h"
#include "SCYSY3Engine.h"

CreateMap::CreateMap(BaseEngine* pEngine) :
	State(pEngine)
	, CostomMap(50, 50 , 15 , 15, pEngine, this)
	, backButton(pEngine, this)
	, noRoad("noRoad.pnd")
	, startBlock(-1, -1)
	, startButton(pEngine, this)
{
	NO_Page = NO_Result;
	InitializeState();
}
CreateMap::~CreateMap() {
	getSCYSY3Engine()->RoadList = RoadList;
}

void CreateMap::InitializeState() {
	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);

}
void CreateMap::setBackGroundForState() {
	int m_iOffset = time_FromCreated / 10;
	int block = 100;
	int Color;
	pState_BackSurface->mySDLLockSurface();
	for (int y = 0; y < pEngine->getWindowHeight(); y++) {
		for (int x = 0; x < pEngine->getWindowWidth(); x++) {
			if (((x + m_iOffset) / block + (y + m_iOffset) / block) % 2 == 1) {
				pState_BackSurface->setPixel(x, y, 0x377D22);
			}
			else {
				pState_BackSurface->setPixel(x, y, 0x75F94D);
			}
		}
	}
	pState_BackSurface->mySDLUnlockSurface();
}

void CreateMap::PreUpdate() {
	State::PreUpdate();
}
void CreateMap::virtMouseDown(int iButton, int iX, int iY) {
	backButton.virtMouseDown(iButton, iX, iY);
	startButton.virtMouseDown(iButton, iX, iY);
	int x = CostomMap.getMapXForScreenX(iX);
	int y = CostomMap.getMapYForScreenY(iY);

	if (x >= 0 && x < CostomMap.getMapWidth()) {
		if (y >= 0 && y < CostomMap.getMapHeight()) {
			if (RoadList.size() == 0) {
				RoadList.emplace_back(x, y);
				CostomMap.setMapValue(x, y, RoadList.size());
			}
			else {
				if (x == RoadList[RoadList.size()-1].x && y == RoadList[RoadList.size() - 1].y) {
					CostomMap.setMapValue(x, y, 0);
					startBlock.x = x;
					startBlock.y = y;
					if (!RoadList.empty()) {
						RoadList.pop_back();
					}
				}
				else if (CostomMap.getMapValue(x, y) == 0) {
					if (x - 1 == RoadList[RoadList.size() - 1].x && y == RoadList[RoadList.size() - 1].y) {
						RoadList.emplace_back(x, y);
						CostomMap.setMapValue(x, y, RoadList.size());
					}
					else if (x + 1 == RoadList[RoadList.size() - 1].x && y == RoadList[RoadList.size() - 1].y) {
						RoadList.emplace_back(x, y);
						CostomMap.setMapValue(x, y, RoadList.size());
					}
					else if (x == RoadList[RoadList.size() - 1].x && y - 1 == RoadList[RoadList.size() - 1].y) {
						RoadList.emplace_back(x, y);
						CostomMap.setMapValue(x, y, RoadList.size());
					}
					else if (x == RoadList[RoadList.size() - 1].x && y + 1 == RoadList[RoadList.size() - 1].y) {
						RoadList.emplace_back(x, y);
						CostomMap.setMapValue(x, y, RoadList.size());
					}
				}
			}
		}
	}

}
void CreateMap::virtPreDraw() {

	int m_iOffset = time_FromCreated / 10;
	int block = 100;
	int Color;
	for (int y = 0; y < pEngine->getWindowHeight(); y++) {
		for (int x = 0; x < pEngine->getWindowWidth(); x++) {
			if (((x + m_iOffset) / block + (y + m_iOffset) / block) % 2 == 1) {
				pState_BackSurface->setPixel(x, y, 0x377D22);
			}
			else {
				pState_BackSurface->setPixel(x, y, 0x75F94D);
			}
		}
	}


	backButton.DoOutSideOfContainner();
	startButton.DoOutSideOfContainner();
	CostomMap.drawAllTiles(pEngine, pState_ForeSurface);
	if (RoadList.size() >= 1) {
		if ((abs(RoadList[0].x - RoadList[RoadList.size() - 1].x) + abs(RoadList[0].y - RoadList[RoadList.size() - 1].y) == 1)&& RoadList.size()>=4) {
			
			validMap = true;
		}
		else {
			CostomMap.Unknown.renderImage(pState_ForeSurface, 0, 0, 225 + CostomMap.getTileWidth() * RoadList[0].x, 50 + CostomMap.getTileHeight() * RoadList[0].y, CostomMap.getTileWidth(), CostomMap.getTileHeight());
			CostomMap.Unknown.renderImage(pState_ForeSurface, 0, 0, 225 + CostomMap.getTileWidth() * RoadList[RoadList.size() - 1].x, 50 + CostomMap.getTileHeight() * RoadList[RoadList.size() - 1].y, CostomMap.getTileWidth(), CostomMap.getTileHeight());
			validMap = false;
		}
	}
	

	pEngine->redrawDisplay();
}
void CreateMap::virtPostDraw() {

}
