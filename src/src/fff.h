#pragma once
#include "header.h"
#include "SCYSY3DisplayableObject.h"
#include "SCYSY3Image.h"

class fff :
    public SCYSY3DisplayableObject
{
public:
    fff(int xStart, int yStart, BaseEngine* pEngine, int iWidth, int iHeight, bool useTopLeftFor00, State* belong);
    

	virtual void virtDraw();
	SCYSY3Image image;
	ImagePixelMappingRotate m_pMapping;
};

