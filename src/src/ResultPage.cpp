#include "header.h"
#include "ResultPage.h"
#include "SCYSY3Engine.h"
#include "SCYSY3Button.h"
ResultPage::ResultPage(BaseEngine* pEngine) :
	State(pEngine)
	,back(pEngine, this)
{
	back.link = 1;
	NO_Page = NO_Result;
	InitializeState();
}
ResultPage::~ResultPage(){}

void ResultPage::InitializeState() {
	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);
}
void ResultPage::setBackGroundForState(){
	//int m_iOffset = time_FromCreated / 10;
	int block = 100;
	int Color;
	pState_BackSurface->mySDLLockSurface();
	for (int y = 0; y < pEngine->getWindowHeight(); y++) {
		for (int x = 0; x < pEngine->getWindowWidth(); x++) {
			if ((x / block + y  / block) % 2 == 1) {
				pState_BackSurface->setPixel(x, y, 0x377D22);
			}
			else {
				pState_BackSurface->setPixel(x, y, 0x75F94D);
			}
		}
	}
	pState_BackSurface->mySDLUnlockSurface();
}
void ResultPage::virtMouseDown(int iButton, int iX, int iY) {
	back.virtMouseDown(iButton, iX, iY);
}
void ResultPage::virtPreDraw(){
	
	m_iOffset = (m_iOffset + 1) % getSCYSY3Engine()->getWindowWidth();
	
	pState_ForeSurface->copyRectangleFrom(pState_BackSurface, 0, 0, pEngine-> getWindowWidth(), pEngine->getWindowHeight(), m_iOffset, 0);
	pState_ForeSurface->copyRectangleFrom(pState_BackSurface, pEngine->getWindowWidth() - m_iOffset, 0, pEngine->getWindowWidth(), pEngine->getWindowHeight(), m_iOffset - pEngine->getWindowWidth(), 0);
	pEngine->redrawDisplay();
}
void ResultPage::virtPostDraw(){
	pState_ForeSurface->drawFastString(400, 400, "Race complete! ", 0xFF0000, nullptr);
	back.DoOutSideOfContainner();
}
