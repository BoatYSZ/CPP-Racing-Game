#pragma once
#include "SCYSY3DisplayableObject.h"


class TitleWheel :
    public SCYSY3DisplayableObject
{
public:
    bool canShow = true;

    TitleWheel::TitleWheel(
        BaseEngine* pEngine
        , State* belong
        , double xStart
        , double yStart
        , bool useTopLeftFor00);

    void TitleWheel::virtDraw();

    void TitleWheel::virtDoUpdate(int iCurrentTime);

    void TitleWheel::DoOutSideOfContainner();
};