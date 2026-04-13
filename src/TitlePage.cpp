#include "header.h"
#include "TitlePage.h"
#include "SCYSY3Button.h"
#include "SCYSY3Engine.h"

TitlePage::TitlePage(BaseEngine* pEngine) :
	State(pEngine)
	,S("S.png")
	,P("P.png")
	,E1("E1.png")
	,E2("E2.png")
	,D("D.png")
	,plus1("plus1.png")
	,plus2("plus2.png")
	,Move_S()
	,Move_P()
	,Move_E1()
	,Move_E2()
	,Move_D()
	,Move_plus1()
	,Move_plus2()
{
	NO_Page = NO_Title;
	InitializeState();

}	

TitlePage::~TitlePage(void){
	//pState_DisplayableObjectContainer->destroyOldObjects(true);
}

void TitlePage::PreUpdate() {

}

void TitlePage::DoBeforeUpdate() {
	State::DoBeforeUpdate();

}

void TitlePage::DoAfterUpdate() {
	State::DoAfterUpdate();

}

void TitlePage::PostUpdate() {

}

void TitlePage::virtPreDraw() {

}

void TitlePage::virtPostDraw() {
	Move_S.calculate(time_FromCreated);
	S.x_abs = Move_S.getX();
	S.y_abs = Move_S.getY();

	Move_P.calculate(time_FromCreated);
	P.x_abs = Move_P.getX();
	P.y_abs = Move_P.getY();

	Move_E1.calculate(time_FromCreated);
	E1.x_abs = Move_E1.getX();
	E1.y_abs = Move_E1.getY();

	Move_E2.calculate(time_FromCreated);
	E2.x_abs = Move_E2.getX();
	E2.y_abs = Move_E2.getY();

	Move_D.calculate(time_FromCreated);
	D.x_abs = Move_D.getX();
	D.y_abs = Move_D.getY();

	Move_plus1.calculate(time_FromCreated);
	plus1.x_abs = Move_plus1.getX();
	plus1.y_abs = Move_plus1.getY();

	Move_plus2.calculate(time_FromCreated);
	plus2.x_abs = Move_plus2.getX();
	plus2.y_abs = Move_plus2.getY();

	if (titleGoUp == false) {
		if (time_FromCreated >= 2500) {
			Move_S.setup((int)S.x_abs, 262, 74, 50, time_FromCreated, time_FromCreated + 500);
			Move_P.setup((int)P.x_abs, 262, 221, 50, time_FromCreated, time_FromCreated + 500);
			Move_E1.setup((int)E1.x_abs, 262, 376, 50, time_FromCreated, time_FromCreated + 500);
			Move_E2.setup((int)E2.x_abs, 262, 507, 50, time_FromCreated, time_FromCreated + 500);
			Move_D.setup((int)D.x_abs, 262, 638, 50, time_FromCreated, time_FromCreated + 500);
			Move_plus1.setup((int)plus1.x_abs, 262, 829, 50, time_FromCreated, time_FromCreated + 500);
			Move_plus2.setup((int)plus2.x_abs, 262, 1004, 50, time_FromCreated, time_FromCreated + 500);

			titleGoUp = true;
		}
	}

	if (titleGoUp == true) {
		if (time_FromCreated >= 3100) {
			titleStop = true;
		}
	}


	if (titleStop == true && titleGoUp == true) {
		titleWheel->canShow = true;
		clickTostart->canShow = true;
	}
	
	S.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)S.x_abs, (int)S.y_abs, S.getWidth(), S.getHeight(), 0xFFFFFF , 0xFFFFFF, 80);
	P.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)P.x_abs, (int)P.y_abs, P.getWidth(), P.getHeight(), 0xFFFFFF, 0xFF0000, 80);
	E1.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)E1.x_abs, (int)E1.y_abs, E1.getWidth(), E1.getHeight(), 0xFFFFFF, 0xFFFFFF, 80);
	E2.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)E2.x_abs, (int)E2.y_abs, E2.getWidth(), E2.getHeight(), 0xFFFFFF, 0xFFFFFF, 80);
	D.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)D.x_abs, (int)D.y_abs, D.getWidth(), D.getHeight(), 0xFFFFFF, 0xFFFFFF, 80);
	plus1.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)plus1.x_abs, (int)plus1.y_abs, plus1.getWidth(), plus1.getHeight(), 0xFFFFFF, 0xFFFF00, 80);
	plus2.renderImageWithMaskAndTransparencyAndReplace(pState_ForeSurface, 0, 0, (int)plus2.x_abs, (int)plus2.y_abs, plus2.getWidth(), plus2.getHeight(), 0xFFFFFF, 0xFFFF00, 80);

	clickTostart->DoOutSideOfContainner();

	titleWheel->x_abs = P.x_abs + 60;
	titleWheel->y_abs = P.y_abs + 200;
	titleWheel->DoOutSideOfContainner();
}

void TitlePage::setBackGroundForState() {
	
}

void TitlePage::InitializeState() {
	int start = 800;
	int t = 200;
	Move_S.setup(-200, 262, 74, 262, start + 0, start + t);
	Move_P.setup(-200, 262, 221, 262, start + t, start + t*2);
	Move_E1.setup(-200, 262, 376, 262, start + t * 2, start + t * 3);
	Move_E2.setup(-200, 262, 507, 262, start + t * 3, start + t * 4);
	Move_D.setup(-200, 262, 638, 262, start + t * 4, start + t * 5);
	Move_plus1.setup(-200, 262, 829, 262, start + t * 5, start + t * 6);
	Move_plus2.setup(-200, 262, 1004, 262, start + t * 6, start + t * 7);

	f1 = new FollowMouse(pEngine, this);
	clickTostart = new ClickToStart(pEngine, this);

	titleWheel = new TitleWheel(pEngine, this, 0, 0, false);
	titleWheel -> setImage("titleWheel.png");
	titleWheel->m_image->m_mapping = new ImagePixelMappingRotate(0);
	titleWheel->m_image->setTransparencyColour(0xFFFFFF);

	titleWheel->canShow = false;
	clickTostart->canShow = false;

	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);
	pState_DisplayableObjectContainer->appendObjectToArray(	f1);
	pState_DisplayableObjectContainer->appendObjectToArray(clickTostart);
	pState_DisplayableObjectContainer->appendObjectToArray(titleWheel);
}







