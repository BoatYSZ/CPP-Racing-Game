#include "header.h"
#include "SCYSY3Engine.h"
#include "Car.h"

Car::Car(
    BaseEngine* pEngine
    , State* belong
    , double xStart
    , double yStart
    , bool useTopLeftFor00
    , SCYSY3DisplayableObject* relative_object
    
)
    : PhysicalObject(pEngine, belong, xStart, yStart, useTopLeftFor00)
    , wheel_Left_Front(this, 0)
    , wheel_Right_Front(this, 1)
    , wheel_Left_Back(this, 2)
    , wheel_Right_Back(this, 3)
    , NextGoal(0,0)
    
{
    ID = 2;
    HitMap_Size = 100;
    createHitMap(HitMap_Size);
    if (!CheckPoint.empty()) {
        NextGoal = CheckPoint[0];
        Next_NO = 0;
    }
    m_image = new SCYSY3Image("AI1.png");
    m_image->setTransparencyColour(m_image->getPixelColour(0, 0));
    m_image->m_mapping = new SCYSY3RotateMapping(0);
}

Car::~Car(){
    PhysicalObject::~PhysicalObject();
    if (m_image != nullptr) {
        delete(m_image);
        m_image = nullptr;
    }
}



void Car::virtDoUpdate(int iCurrentTime) {
    if (!p_BelongState->stop) {
        BeforeOperate(iCurrentTime);
        AIDecision();
        AfterOperate(iCurrentTime);
    }

    CD_expression -= p_BelongState->time_Increment;
    if (CD_expression < 0) {
        CD_expression = 0;
    }
}
void Car::virtDraw() {
    CleanHitMap();
    HitPixel.clear();
    if (m_image != nullptr){
        m_image->renderImageApplyingMappingAndHitPixel(
            getSCYSY3Engine()
          , getSCYSY3Engine()->getForegroundSurface()
          , m_iCurrentScreenX, m_iCurrentScreenY
          , m_image->m_mapping
          , this
        );
    }
    UpdateHitMap();
    ShowHitMap();
    wheel_Left_Front.virtDraw();
    wheel_Right_Front.virtDraw();
    wheel_Left_Back.virtDraw();
    wheel_Right_Back.virtDraw();
    
}

void Car::turnLeft() {
    //if (frontWheelDirection > 0) {
    //    frontWheelDirection -= 0.1;
    //}
    frontWheelDirection -= 0.04;
    if (frontWheelDirection < -0.3) {
        frontWheelDirection = -0.3;
    }
}
void Car::turnLRight() {
    //if (frontWheelDirection < 0) {
    //    frontWheelDirection += 0.1;
    //}
    frontWheelDirection += 0.04;
    if (frontWheelDirection > 0.3) {
        frontWheelDirection = 0.3;
    }
}

void Car::BeforeOperate(int iCurrentTime) {
    if (CheckPoint.size() >= 1) {
        if ((x_abs - CheckPoint[Next_NO].x) * (x_abs - CheckPoint[Next_NO].x) + (y_abs - CheckPoint[Next_NO].y) * (y_abs - CheckPoint[Next_NO].y) <= 90000) {
            Next_NO++;
            if (Next_NO > CheckPoint.size() - 1) {
                Next_NO = 0;
                RoundCompleted++;
            }
        }
    }
    

    double d = 0;
    v_force.direction = 0;
    v_force.magnitude = 0;
    d = abs(v_velocity.magnitude * cos(orientation_abs + frontWheelDirection - v_velocity.direction));
    if (d == 0) {
        d = 100;
    }
}
void Car::AfterOperate(int iCurrentTime) {
    updatePhysicalAttribute();
    orientation_abs += v_displacement.magnitude / 70 * frontWheelDirection;
    v_velocity.direction += v_displacement.magnitude / 70 * frontWheelDirection;
    //v_velocity.direction += v_displacement.magnitude / 150 * frontWheelDirection;
    while (orientation_abs > M_PI) {
        orientation_abs -= 2 * M_PI;
    }
    while (orientation_abs < -M_PI) {
        orientation_abs += 2 * M_PI;
    }

    while (v_velocity.direction > M_PI) {
        v_velocity.direction -= 2 * M_PI;
    }
    while (v_velocity.direction < -M_PI) {
        v_velocity.direction += 2 * M_PI;
    }

    static_cast<SCYSY3RotateMapping*>(m_image->m_mapping)->setRotation(-orientation_abs);
    syncImagePosition(m_image, this);

    wheel_Left_Front.virtDoUpdate(iCurrentTime);
    wheel_Right_Front.virtDoUpdate(iCurrentTime);
    wheel_Left_Back.virtDoUpdate(iCurrentTime);
    wheel_Right_Back.virtDoUpdate(iCurrentTime);
}

bool Car::IsHit(Car* car) {
    if ((this->x_abs - car->x_abs) * (this->x_abs - car->x_abs) + (this->y_abs - car->y_abs) * (this->y_abs - car->y_abs) >= 10000) {
        return false;
    }
    if (car->HitMap == nullptr) {
        return false;
    }
    int carX;
    int carY;
    for (int i = 0; i < HitPixel.size(); i++) {
        for (int j = 0; j < car->HitPixel.size(); j++) {
            if ((HitPixel[i].x + m_iCurrentScreenX == car->HitPixel[j].x + car->m_iCurrentScreenX)&& (HitPixel[i].y + m_iCurrentScreenY == car->HitPixel[j].y + car->m_iCurrentScreenY)) {
                return true;
            }
        }
        
    }
    return false;
}
//carX = HitPixel[i].x + m_iCurrentScreenX - car->m_iCurrentScreenX + (car->HitMap_Size) / 2;
        //carY = HitPixel[i].y + m_iCurrentScreenY - car->m_iCurrentScreenY + (car->HitMap_Size) / 2;
        //if (carX >= car->HitMap_Size || carX < 0) {
        //    return false;
        //}
        //if (carY >= car->HitMap_Size || carY < 0) {
        //    return false;
        //}
        //if (car->HitMap[carY][carX]) {
        //    p->pState_ForeSurface->mySDLLockSurface();
        //    p->pState_ForeSurface->drawRectangle(
        //        m_iCurrentScreenX,
        //        m_iCurrentScreenY,
        //         m_iCurrentScreenX + 100,
        //         m_iCurrentScreenY + 100,
        //        0x00FF00
        //    );
        //    p->pState_ForeSurface->mySDLUnlockSurface();
        //    //printf("%d %d\n", absXtoWindowX(HitPixel[i].x + (car->HitMap_Size) / 2),
        //    //    absYtoWindowY(HitPixel[i].y + (car->HitMap_Size) / 2));
        //    //printf("%d %d\n", HitPixel[i].y + (car->HitMap_Size) / 2,
        //    //    HitPixel[i].x + (car->HitMap_Size) / 2);
        //    return true;
        //    
        //}
void Car::AIDecision() {
    if (p_BelongState->stop) {
        return;
    }
    double target = atan2(CheckPoint[Next_NO].y - y_abs, CheckPoint[Next_NO].x - x_abs);
    double target_rela = target - orientation_abs;
    while (target_rela > M_PI) {
        target_rela -= 2 * M_PI;
    }
    while(target_rela < -M_PI) {
        target_rela += 2 * M_PI;
    }
    double offset;

    

    if (target_rela >= 0 && target_rela < M_PI / 2) {
        offset = distanceToRay(x_abs, y_abs, CheckPoint[Next_NO].x, CheckPoint[Next_NO].y, orientation_abs);
        if (target_rela < M_PI / 6 && offset <= 200) {
            RecoverDirection();
        }
        else
        {
            turnLRight();
        }
        getEnergy(orientation_abs, power);
    }
    else if (target_rela >= M_PI / 2 && target_rela <= M_PI){
        turnLRight();
        getEnergy(orientation_abs, power);
    }
    else if (target_rela >= - M_PI && target_rela < - M_PI / 2)
    {
        turnLeft();
        getEnergy(orientation_abs, power);

    }
    else if (target_rela >= -M_PI / 2 && target_rela < 0)
    {   
        offset = distanceToRay(x_abs, y_abs, CheckPoint[Next_NO].x, CheckPoint[Next_NO].y, orientation_abs);
        if (target_rela > -M_PI / 6 && offset <= 200) {
            RecoverDirection();
        }
        else
        {
            turnLeft();
        }
        getEnergy(orientation_abs, power);
    }
           
}

double Car::distanceToRay(double x1, double y1, double x2, double y2, double theta) {
    double dx = cos(theta);
    double dy = sin(theta);
    double vx = x2 - x1;
    double vy = y2 - y1;
    double dot = vx * dx + vy * dy;
    double projX = dot * dx;       
    double projY = dot * dy;       
    double distX = vx - projX;
    double distY = vy - projY;
    return sqrt(distX * distX + distY * distY);
}

void Car::RecoverDirection() {
    if (frontWheelDirection > 0) {
        frontWheelDirection -= 0.05;
        if (frontWheelDirection < 0) {
            frontWheelDirection = 0;
        }
    }
    else {
        frontWheelDirection += 0.05;
        if (frontWheelDirection > 0) {
            frontWheelDirection = 0;
        }
    }
}

void Car::SendExpression(){
    CD_expression = 6000;
    getEngine()->appendObjectToArray(new Expression(getEngine(), p_BelongState, this));
}


