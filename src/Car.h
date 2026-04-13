#pragma once
#include "PhysicalObject.h"
#include "Wheel.h"
#include "Point.h"
#include "Expression.h"
class Gaming1;

class Car :
    public PhysicalObject
{
public:
    Car(
        BaseEngine* pEngine
        , State* belong
        , double xStart
        , double yStart
        , bool useTopLeftFor00
        , SCYSY3DisplayableObject* relative_object
    );
    virtual ~Car();
    void virtDoUpdate(int iCurrentTime);
    void virtDraw();
    void turnLeft();
    void turnLRight();
    void AIDecision();
    virtual void BeforeOperate(int iCurrentTime);
    virtual void AfterOperate(int iCurrentTime);
    void Car::RecoverDirection();
    virtual bool IsHit(Car* car);
    double Car::distanceToRay(double x1, double y1, double x2, double y2, double theta);
    void Car::SendExpression();
    
    double power = 13000;
    double frontWheelDirection = 0;
    //Gaming1* p = nullptr;
    std::vector<Point> CheckPoint;
    std::vector<Point> RoadList;
    Point NextGoal;
    int RoundCompleted = 0;
    int Next_NO = 0;
    double CD_expression = 0;
    Wheel wheel_Left_Front;
    Wheel wheel_Right_Front;
    Wheel wheel_Left_Back;
    Wheel wheel_Right_Back;
   
};

