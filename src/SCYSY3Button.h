#pragma once
#include "BaseEngine.h"
#include "SCYSY3DisplayableObject.h"
#include "State.h"
class SCYSY3Button:
	public SCYSY3DisplayableObject
{
public:
	//SCYSY3Button(int xStart = 300 , int yStart = 300, BaseEngine* pEngine = nullptr , int iWidth = 100, int iHeight = 50, bool useTopLeftFor00 = true, State* state = nullptr);
	SCYSY3Button(int xStart = 300, int yStart = 300, 
				BaseEngine* pEngine = nullptr, 
				int iWidth = 100, int iHeight = 50 , bool useTopLeftFor00 = true, 
				State* belong = nullptr, int link = - 1);

	virtual ~SCYSY3Button();

	virtual void virtMouseDown(int iButton, int iX, int iY);
	void virtMouseUp(int iButton, int iX, int iY);
	void ChangeState(int toState, bool save, bool refresh);
	virtual bool virtIsHover(int x, int y);
	virtual void DoOutSideOfContainner();
	virtual void clickedAndDo();
	unsigned int i_BackGroundColor = 0x000000;
	unsigned int i_StringColor = 0x000000;
	bool bLeftClickDownAtButton;
	bool bMouseHoverAtButton;
	bool bLeftClickUpAtButton;
	
	//virtual void virtExecute();
	int link = -1;
	int p_DestinationState = -1;	
};



class ClickToStart :
	public SCYSY3Button 
{
public:
	ClickToStart(BaseEngine* pEngine, State* belong);

	void virtMouseDown(int iButton, int iX, int iY) {
		if (canShow) {
			if (virtIsHover(iX, iY)) {
				clickedAndDo();
			}
		}
	}
	void ClickToStart::clickedAndDo() {
		if (link >= 0) {
			ChangeState(link, false, false);
		}
	}

	void DoOutSideOfContainner() {
		if (canShow) {
			if (p_BelongState->time_FromCreated % 2000 > 1000) {
				p_BelongState->pEngine->drawForegroundString(getEngine()->getWindowWidth() / 2 - 100, getEngine()->getWindowHeight() / 3 * 2, "Click To Start", 0xFFFF00);
			}
		}
	}
	int link;
	bool canShow = true;
};

class NEWGAME :
	public SCYSY3Button 
{
public:
	NEWGAME(BaseEngine* pEngine, State* belong);

	void NEWGAME::clickedAndDo() {
		ChangeState(link, false, false);
	}

	void DoOutSideOfContainner() {
		if (canShow) {
			p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xC0C0C0);
			
			if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0xFF0000);
			}
			else
			{
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text , 0x000000);
			}
		}
	}
	int link;
	bool canShow = true;
	char* text = "NEW GAME";
};

class LoadGame :
	public NEWGAME
{
public:
	LoadGame(BaseEngine* pEngine, State* belong);

	void LoadGame::virtMouseDown(int iButton, int iX, int iY) {
		if (canShow) {
			if (virtIsHover(iX, iY)) {
				clickedAndDo();
			}
		}
	}

	void LoadGame::clickedAndDo();
	int link;
};

class ExitGame :
	public NEWGAME
{
public:
	ExitGame(BaseEngine* pEngine, State* belong);

	void ExitGame::virtMouseDown(int iButton, int iX, int iY) {
		if (canShow) {
			if (virtIsHover(iX, iY)) {
				clickedAndDo();
			}
		}
	}

	void ExitGame::clickedAndDo() {
		getEngine()->setExitWithCode(1);
	}
};


class SeleteAMap :
	public NEWGAME
{
public:
	SeleteAMap(BaseEngine* pEngine, State* belong);

	void SeleteAMap::virtMouseDown(int iButton, int iX, int iY) {
		if (canShow) {
			if (virtIsHover(iX, iY)) {
				clickedAndDo();
			}
		}
	}

	void SeleteAMap::clickedAndDo() {
		if (link >= 0) {
			ChangeState(link, false, false);
		}
	}
	int link;
};

class Custom :
	public NEWGAME
{
public:
	Custom(BaseEngine* pEngine, State* belong);

	void Custom::virtMouseDown(int iButton, int iX, int iY) {
		if (canShow) {
			if (virtIsHover(iX, iY)) {
				clickedAndDo();
			}
		}
	}

	void Custom::clickedAndDo() {
		if (link >= 0) {
			ChangeState(link, false, false);
		}
	}
	int link;
};


class Next :
	public SCYSY3Button
{
public:
	Next(BaseEngine* pEngine, State* belong);

	void Next::clickedAndDo();

	void DoOutSideOfContainner() {
		if (canShow) {
			p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

			if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 20, m_iCurrentScreenY + 40, text, 0xFF0000);
			}
			else
			{
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 20, m_iCurrentScreenY + 40, text, 0x000000);
			}
		}
	}
	bool canShow = true;
	char* text = "Next";
};

class Prev :
	public SCYSY3Button
{
public:
	Prev(BaseEngine* pEngine, State* belong);

	void Prev::clickedAndDo();

	void DoOutSideOfContainner() {
		if (canShow) {
			p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

			if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 20, m_iCurrentScreenY + 40, text, 0xFF0000);
			}
			else
			{
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 20, m_iCurrentScreenY + 40, text, 0x000000);
			}
		}
	}
	bool canShow = true;
	char* text = "Prev";
};


class Back :
	public SCYSY3Button
{
public:
	Back(BaseEngine* pEngine, State* belong);

	void Back::clickedAndDo() {
		ChangeState(link, false, false);
	}

	void DoOutSideOfContainner() {
		if (canShow) {
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
	int link;
	bool canShow = true;
	char* text = "Back";
};

class Start :
	public SCYSY3Button
{
public:
	Start(BaseEngine* pEngine, State* belong);

	void Start::clickedAndDo() {
		ChangeState(link, false, false);
	}

	void DoOutSideOfContainner() {
		if (canShow) {
			p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

			if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 50, m_iCurrentScreenY + 10, text, 0xFF0000);
			}
			else
			{
				p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 50, m_iCurrentScreenY + 10, text, 0x000000);
			}
		}
	}
	int link;
	bool canShow = true;
	char* text = "Start";
};

class StartCostom :
	public SCYSY3Button
{
public:
	StartCostom(BaseEngine* pEngine, State* belong);

	void StartCostom::clickedAndDo();

	void DoOutSideOfContainner();
	int link;
	bool canShow = true;
	char* text = "Start";
};



