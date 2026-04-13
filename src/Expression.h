#pragma once
#include "SCYSY3DisplayableObject.h"
class Expression :
    public SCYSY3DisplayableObject
{
public:
    Expression(BaseEngine* pEngine, State* state_belong, SCYSY3DisplayableObject* obj_belong);
    ~Expression();
    void Expression::virtDoUpdate(int iCurrentTime);
    void virtDraw();
    double timeRemaining = 3000;
};

