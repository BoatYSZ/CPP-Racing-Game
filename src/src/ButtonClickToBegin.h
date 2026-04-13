#pragma once
#include "BaseEngine.h"
#include "SCYSY3DisplayableObject.h"
#include "State.h"

class ButtonClickToBegin :
	public SCYSY3DisplayableObject
{
public:
	//ButtonClickToBegin(int xStart = 300 , int yStart = 300, BaseEngine* pEngine = nullptr , int iWidth = 100, int iHeight = 50, bool useTopLeftFor00 = true, State* state = nullptr);
	ButtonClickToBegin(int xStart = 300, int yStart = 300,
		BaseEngine* pEngine = nullptr,
		int iWidth = 100, int iHeight = 50, bool useTopLeftFor00 = true,
		State* belong = nullptr, State* link = nullptr);

	virtual ~ButtonClickToBegin();
	void virtDraw();
	void virtDoUpdate(int iCurrentTime);
	void virtMouseDown(int iButton, int iX, int iY);
	void virtMouseUp(int iButton, int iX, int iY);
	virtual bool virtIsHover(int x, int y);
	unsigned int i_BackGroundColor = 0x000000;
	unsigned int i_StringColor = 0x000000;
	bool bLeftClickDownAtButton;
	bool bMouseHoverAtButton;
	bool bLeftClickUpAtButton;

	//virtual void virtExecute();
	State* p_DestinationState;
};

