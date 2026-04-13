#pragma once
#include "State.h"
#include "SCYSY3Button.h"
class ResultPage :
    public State
{
public:
    ResultPage(BaseEngine* pEngine);
    virtual ~ResultPage();
    virtual void InitializeState();
    virtual void setBackGroundForState();
    virtual void ResultPage::virtMouseDown(int iButton, int iX, int iY);
    virtual void virtPreDraw();
    virtual void virtPostDraw();
    int m_iOffset = 0;
    Back back;
};

