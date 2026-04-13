#pragma once
#include "SCYSY3DisplayableObject.h"
#include "PhysicalVector.h"


class PhysicalObject :
    public SCYSY3DisplayableObject
{
public:
    PhysicalObject(
        BaseEngine* pEngine
        , State* belong
        , double xStart
        , double yStart
        , bool useTopLeftFor00
    );
    virtual ~PhysicalObject();
    virtual void virtDoUpdate(int iCurrentTime);
    virtual void virtDraw();
    virtual void updatePhysicalAttribute();
    virtual void getEnergy(double direction, double mag);
    PhysicalVector v_energy;
    PhysicalVector v_force;
    PhysicalVector v_acce;
    PhysicalVector v_velocity;
    PhysicalVector v_displacement;
    PhysicalVector v_middle;
  
    double f = 400;
};

