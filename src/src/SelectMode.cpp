#include "header.h"
#include "SelectMode.h"
#include "SCYSY3Engine.h"
SelectMode::SelectMode(BaseEngine* pEngine) :
	State(pEngine)
	, SPEEDpp("SPEEDpp.png")
{
	SPEEDpp.x_abs = 74;
	SPEEDpp.y_abs = 50;
	NO_Page = NO_SelectMode;
	InitializeState();
}
SelectMode::~SelectMode() {
	delete(titleWheel);
}

void SelectMode::InitializeState() {

	titleWheel = new TitleWheel(pEngine, this, 0, 0, false);
	titleWheel->setImage("titleWheel.png");
	titleWheel->m_image->m_mapping = new ImagePixelMappingRotate(0);
	titleWheel->m_image->setTransparencyColour(0xFFFFFF);
	titleWheel->x_abs = 221 + 60;
	titleWheel->y_abs = 50 + 200;

	seleteAMap = new SeleteAMap(pEngine, this);
	custom = new Custom(pEngine, this);
	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);
	pState_DisplayableObjectContainer->appendObjectToArray(seleteAMap);
	pState_DisplayableObjectContainer->appendObjectToArray(custom);
}
void SelectMode::setBackGroundForState() {
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

void SelectMode::virtPreDraw() {

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
	SPEEDpp.renderImageWithMaskAndReplace2(pState_ForeSurface, pState_BackSurface, 0, 0, SPEEDpp.x_abs, SPEEDpp.y_abs, SPEEDpp.getWidth(), SPEEDpp.getHeight(), 0xFFFFFF);
	pEngine->redrawDisplay();
}
void SelectMode::virtKeyDown(int iKeyCode) {
	if (iKeyCode >= 97 && iKeyCode <= 122) {
		if (getSCYSY3Engine()->currentNameLength < NameLength - 1) {
			getSCYSY3Engine()->playName[getSCYSY3Engine()->currentNameLength] = (char)iKeyCode;
			getSCYSY3Engine()->currentNameLength++;
			getSCYSY3Engine()->playName[getSCYSY3Engine()->currentNameLength] = 0;
			
		}
		
	}
	else if (iKeyCode == 8) {
		if (getSCYSY3Engine()->currentNameLength >= 1) {
			getSCYSY3Engine()->playName[getSCYSY3Engine()->currentNameLength-1] = 0;
			getSCYSY3Engine()->currentNameLength--;
		}
	}
	getSCYSY3Engine()->LastPressedKey = iKeyCode;
}
void SelectMode::virtPostDraw() {
	pState_ForeSurface->drawFastString(400, 400, "Name: ", 0xFFFFFF, nullptr);
	pState_ForeSurface->drawFastString(500, 400, getSCYSY3Engine()->playName, 0xFFFFFF, nullptr);
	seleteAMap->DoOutSideOfContainner();
	custom->DoOutSideOfContainner();
	titleWheel->DoOutSideOfContainner();
}