#pragma once
#include "BaseEngine.h"
#include "FilterPoints.h"

class SCYSY3FilterPoints :
    public FilterPoints
{
public:
	SCYSY3FilterPoints(BaseEngine* pEngine, FilterPoints* pNextFilter);

	virtual bool filter(DrawingSurface* surface, int& x, int& y, unsigned int& uiColour, bool setting);

	virtual int filterConvertRealToVirtualXPosition(int x);
	
	virtual int filterConvertRealToVirtualYPosition(int y);
	
	virtual int filterConvertVirtualToRealXPosition(int x);

	virtual int filterConvertVirtualToRealYPosition(int y);
	void Initialize();
	void SCYSY3FilterPoints::Move(int moveX, int moveY);
	FilterPoints* pNextFilter;
	BaseEngine* m_pEngine;
	int Rate = 1;
	int offset_X = 0;
	int offset_Y = 0;
	int Window_Width;
	int Window_Height;
	int Min_X[4];
	int Min_Y[4];
	int Max_X[4];
	int Max_Y[4];
};

