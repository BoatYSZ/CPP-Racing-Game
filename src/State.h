#pragma once
#include "BaseEngine.h"
class SCYSY3Engine;

class State
{
public:
	State(BaseEngine* pEngine);
	virtual ~State();
	int NO_Page;
	BaseEngine* pEngine;
	DrawingSurface state_ForeSurface;
	DrawingSurface state_BackSurface;
	DrawingSurface* pState_ForeSurface;
	DrawingSurface* pState_BackSurface;
	DisplayableObjectContainer state_DisplayableObjectContainer;
	DisplayableObjectContainer* pState_DisplayableObjectContainer;

	SCYSY3Engine* State::getSCYSY3Engine();

	virtual void virtMouseDown(int iButton, int iX, int iY);
	virtual void virtKeyDown(int iKeyCode);
	virtual void virtMouseWheel(int x, int y, int which, int timestamp);
	virtual void PreUpdate();
	virtual void DoBeforeUpdate();
	virtual void DoAfterUpdate();
	virtual void PostUpdate();
	virtual void virtPreDraw();
	virtual void virtPostDraw();

	virtual void setBackGroundForState();
	virtual void InitializeState();
	//SCYSY3Engine* getSCYSY3Engine();
	double cameraX;
	double cameraY;
	int i_MouseX;
	int i_MouseY;
	int i_timeWhenChangeHere = 0;
	int i_timeFromChangeHere = 0;
	int time_FromCreated = 0;
	int time_WhenCreated;
	int time_Increment = 0;
	int timeRecord = 0;
	bool stop = false;
};

