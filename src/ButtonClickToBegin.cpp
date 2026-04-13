#include "header.h"
#include "ButtonClickToBegin.h"

ButtonClickToBegin::ButtonClickToBegin(int xStart, int yStart,
	BaseEngine* pEngine,
	int iWidth, int iHeight, bool useTopLeftFor00,
	State* belong, State* link)
	:
	SCYSY3DisplayableObject(xStart, yStart, pEngine, iWidth, iHeight, useTopLeftFor00, belong)
	, bLeftClickDownAtButton(false)
	, bMouseHoverAtButton(false)
	, bLeftClickUpAtButton(false)
	, p_DestinationState(link)
{
	m_iCurrentScreenX = 500;
	m_iCurrentScreenY = 500;

}

ButtonClickToBegin::~ButtonClickToBegin() {
}


void ButtonClickToBegin::virtDraw() {
	getEngine()->drawBackgroundRectangle(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		0xaaaa00);
	if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
		getEngine()->drawForegroundString(m_iCurrentScreenX + m_iDrawWidth / 3, m_iCurrentScreenY + m_iDrawHeight / 4, "ButtonClickToBegin", 0xFF00FF);
	}

}

void ButtonClickToBegin::virtDoUpdate(int iCurrentTime) {

}

void ButtonClickToBegin::virtMouseDown(int iButton, int iX, int iY) {

}

void ButtonClickToBegin::virtMouseUp(int iButton, int iX, int iY) {

}
bool ButtonClickToBegin::virtIsHover(int x, int y) {
	if (x >= m_iCurrentScreenX && x <= m_iCurrentScreenX + m_iDrawWidth - 1
		&& y >= m_iCurrentScreenY && y <= m_iCurrentScreenY + m_iDrawHeight - 1)
	{
		return true;
	}
	return false;
}
//void ButtonClickToBegin::virtExecute(){}