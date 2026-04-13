#include "header.h"
#include "SCYSY3Button.h"
#include "SCYSY3Engine.h"
#include "SelectMap.h";
#include "CreateMap.h"
SCYSY3Button::SCYSY3Button(
	int xStart, 
	int yStart,
	BaseEngine* pEngine, 
	int iWidth, 
	int iHeight, 
	bool useTopLeftFor00, 
	State* belong, 
	int link)
	:
	SCYSY3DisplayableObject(xStart, yStart, pEngine, iWidth, iHeight, useTopLeftFor00, belong)
	,bLeftClickDownAtButton(false)
	,bMouseHoverAtButton(false)
	,bLeftClickUpAtButton(false)
	,link(link)
{
	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = 0;
	m_iDrawWidth = 200;
	m_iDrawHeight = 200;
}

SCYSY3Button::~SCYSY3Button(){
}

void SCYSY3Button::virtMouseDown(int iButton, int iX, int iY) {
	if (canShow) {
		if (virtIsHover(iX, iY)) {
			clickedAndDo();
		}
	}
}

void SCYSY3Button::virtMouseUp(int iButton, int iX, int iY) {

}
bool SCYSY3Button::virtIsHover(int x, int y) {
	if (x >= m_iCurrentScreenX && x <= m_iCurrentScreenX + m_iDrawWidth - 1
		&& y >= m_iCurrentScreenY && y <= m_iCurrentScreenY + m_iDrawHeight - 1)
	{
		return true;
	}
	return false;
}

void SCYSY3Button::DoOutSideOfContainner() {
	getEngine()->drawForegroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xaaaa00);
	if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
		getEngine()->drawForegroundString(m_iCurrentScreenX + m_iDrawWidth / 3, m_iCurrentScreenY + m_iDrawHeight / 4, "A Button", 0xFF00FF);
	}

}
void SCYSY3Button::ChangeState(int toState, bool save, bool refresh) {
	getSCYSY3Engine()->ChangeState(toState, false, false);
}

void SCYSY3Button::clickedAndDo() {

}

ClickToStart::ClickToStart(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 0, 0, true, belong, NO_Menu)
{
	link = NO_Menu;
	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2;
	m_iDrawWidth = pEngine->getWindowWidth();
	m_iDrawHeight = pEngine->getWindowHeight();
}

NEWGAME::NEWGAME(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 0, 0, true, belong, NO_Gaming1)
{
	link = NO_SelectMode;
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	//m_iCurrentScreenX = pEngine->getWindowWidth() / 2 - m_iDrawWidth / 2;
	m_iCurrentScreenX = 100;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 50;
}

LoadGame::LoadGame(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = NO_Gaming1;
	text = "LOAD GAME";
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = 100;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 150;
}

ExitGame::ExitGame(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = NO_Title;
	text = "EXIT GAME";
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = 100;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 250;
}

SeleteAMap::SeleteAMap(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = NO_SelectMap;
	text = "Selete Map";
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = pEngine->getWindowWidth() / 2 - m_iDrawWidth / 2;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 100;
}

Custom::Custom(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = NO_CreateMap;
	text = "Custom Map";
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = pEngine->getWindowWidth() / 2 - m_iDrawWidth / 2;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 200;
}

Prev::Prev(BaseEngine* pEngine, State* belong):
	SCYSY3Button(50, 400, pEngine, 100, 100, true, belong, -1)
{
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	m_iCurrentScreenX = 50;
	m_iCurrentScreenY = 400;
}

Next::Next(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(900, 400, pEngine, 100, 100, true, belong, -1)
{
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	m_iCurrentScreenX = 1050;
	m_iCurrentScreenY = 400;
}

Back::Back(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 100, 100, true, belong, -1)
{
	link = NO_SelectMode;
	m_iDrawWidth = 200;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = 0;
	m_iCurrentScreenY = 0;
}

Start::Start(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 100, 100, true, belong, -1)
{
	m_iDrawWidth = 200;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = 500;
	m_iCurrentScreenY = 800;
	link = NO_Gaming1;
}

void Prev::clickedAndDo() {
	SelectMap* p = static_cast<SelectMap*>(p_BelongState);
	p->i_currentImage--;
	if (p->i_currentImage < 0) {
		p->i_currentImage = p->v_Image.size() - 1;
	}
}

void Next::clickedAndDo() {
	SelectMap* p = static_cast<SelectMap*>(p_BelongState);
	p->i_currentImage++;
	if (p->i_currentImage > p->v_Image.size() - 1) {
		p->i_currentImage = 0;
	}
}

StartCostom::StartCostom(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 100, 100, true, belong, -1)
{
	m_iDrawWidth = 200;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = 500;
	m_iCurrentScreenY = 850;
	link = NO_Gaming1;
}
void StartCostom::clickedAndDo()
{
	
	if (static_cast<CreateMap*>(p_BelongState)-> validMap) {
		getSCYSY3Engine()->GameMode = 1;
		CreateMap* p = static_cast<CreateMap*>(p_BelongState);
		for (int x = 0; x < 15; x++) {
			for (int y = 0; y < 15; y++) {
				getSCYSY3Engine()->MapBlock[y][x] = p->CostomMap.getMapValue(x, y);
			}
		}
		ChangeState(link, false, false);
	}
	
}
void StartCostom::DoOutSideOfContainner() {
	if (canShow && static_cast<CreateMap*>(p_BelongState)->validMap) {
		p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

		if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
			p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0xFF0000);
		}
		else
		{
			p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0x000000);
		}
	}
}

void LoadGame::clickedAndDo() {
	if (link >= 0) {
		getSCYSY3Engine()->ShouldLoad = true;
		ChangeState(link, false, false);
	}
}

