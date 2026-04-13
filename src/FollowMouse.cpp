#include "header.h"
#include "FollowMouse.h"
#include "SCYSY3Engine.h"
#include "UtilCollisionDetection.h"
#include "Gaming1.h"

void FollowMouse::virtDraw()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	getEngine()->drawForegroundOval(
		m_iCurrentScreenX, m_iCurrentScreenY,
		m_iCurrentScreenX + m_iDrawWidth - 1,
		m_iCurrentScreenY + m_iDrawHeight - 1,
		color);
	getEngine()->drawForegroundString(m_iCurrentScreenX + m_iDrawWidth/3, m_iCurrentScreenY + m_iDrawHeight / 4, chr, 0xffffff);
}


void FollowMouse::virtDoUpdate(int iCurrentTime)
{
	SDL_GetMouseState(&mouseX, &mouseY);
	m_iCurrentScreenX = p_BelongState->i_MouseX;
	m_iCurrentScreenY = p_BelongState->i_MouseY;
	this->redrawDisplay();
}


void FollowMouse::virtMouseDown(int iButton, int iX, int iY)
{
	if (iButton == SDL_BUTTON_LEFT)
	{
		color = 0x00FF00;
	}
	else if (iButton == SDL_BUTTON_RIGHT)
	{
		color = 0x0000FF;
	}
	printf("%d %d\n", iX, iY);
}


void FollowMouse::virtKeyDown(int iKeyCode)
{
	
	*chr = char(iKeyCode);
}
