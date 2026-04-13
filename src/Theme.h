#pragma once
#include "BaseEngine.h"
#include "SCYSY3Image.h"

class Theme
{
public:
	Theme::Theme();
	Theme::~Theme();

    SCYSY3Image* mapGrass;
    SCYSY3Image* Grass;
    
    SCYSY3Image* mapSnow;
    SCYSY3Image* Snow;
    SCYSY3Image* TreeSnow;
    
    SCYSY3Image* UD;
    SCYSY3Image* LR;
    SCYSY3Image* UL;
    SCYSY3Image* UR;
    SCYSY3Image* DL;
    SCYSY3Image* DR;
};

