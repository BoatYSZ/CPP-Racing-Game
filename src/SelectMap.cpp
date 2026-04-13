#include "header.h"
#include "SelectMap.h"
#include "SCYSY3Engine.h"
SelectMap::SelectMap(BaseEngine* pEngine) :
	State(pEngine)
{
	NO_Page = NO_Result;
	InitializeState();
}
SelectMap::~SelectMap() {
	
	for (auto obj : v_Image) {
		delete obj;
	}
	v_Image.clear();
}

void SelectMap::InitializeState() {
	prev = new Prev(pEngine, this);
	next = new Next(pEngine, this);
	start = new Start(pEngine, this);
	back = new Back(pEngine, this);

	v_Image.push_back(new SCYSY3Image("select0.png"));
	v_Image.push_back(new SCYSY3Image("select1.png"));
	v_Image.push_back(new SCYSY3Image("select2.png"));
	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);
	pState_DisplayableObjectContainer->appendObjectToArray(prev);
	pState_DisplayableObjectContainer->appendObjectToArray(next);
	pState_DisplayableObjectContainer->appendObjectToArray(start);
	pState_DisplayableObjectContainer->appendObjectToArray(back);
}
void SelectMap::setBackGroundForState() {
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

void SelectMap::virtPreDraw() {

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
	v_Image[i_currentImage]->renderImage(pState_BackSurface, 0, 0, 300, 100, v_Image[i_currentImage]->getWidth(), v_Image[i_currentImage]->getHeight());
	getSCYSY3Engine()->currentTheme = i_currentImage;
	getSCYSY3Engine()->currentMap = i_currentImage;
	prev->DoOutSideOfContainner();
	next->DoOutSideOfContainner();
	start->DoOutSideOfContainner();
	back->DoOutSideOfContainner();

	pEngine->redrawDisplay();
}
void SelectMap::virtPostDraw() {
	
}