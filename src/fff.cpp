#include "header.h"
#include "fff.h"

fff::fff(int xStart, int yStart, BaseEngine* pEngine, int iWidth, int iHeight, bool useTopLeftFor00, State* belong):
	SCYSY3DisplayableObject(xStart, yStart, pEngine, iWidth, iHeight, useTopLeftFor00, belong),
	m_pMapping(0)
{

}

void fff::virtDraw()
{
	//if (isVisible())
	//{
	//	image.renderImageApplyingMapping(getEngine(), getEngine()->getForegroundSurface(),
	//		m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY, m_iDrawWidth, m_iDrawHeight,
	//		m_pMapping);
	//}
}