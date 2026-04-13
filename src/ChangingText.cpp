#include "header.h"
#include "BaseEngine.h"
#include "ChangingText.h"

void ChangingText::virtDraw()
{
	sprintf(pDisplayContent, "%d", iTime);

	getEngine()->lockForegroundForDrawing();
	getEngine()->drawForegroundString(x, y, pDisplayContent, 0xFF0000);	//
	getEngine()->unlockForegroundForDrawing();
}

void ChangingText::virtDoUpdate(int iCurrentTime)
{

	iTime = getEngine()->getRawTime()/1000;
	if (iTime != iPreTime) {
		iPreTime = iTime;
		sprintf(pDisplayContent, "%d", iTime);
	}
	
	this->redrawDisplay();
}


