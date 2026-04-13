#include "header.h"
#include "PlayerCar.h"
#include "Gaming1.h"
#include "SCYSY3Engine.h"

PlayerCar::PlayerCar(
    BaseEngine* pEngine
    , State* belong
    , double xStart
    , double yStart
    , bool useTopLeftFor00
    , SCYSY3DisplayableObject* relative_object
) : Car(pEngine, belong, xStart, yStart, useTopLeftFor00, nullptr)
{
    power = 13000;
    ID = 1;
    delete(m_image);
    m_image = new SCYSY3Image("Car.png");
    m_image->setTransparencyColour(m_image->getPixelColour(0, 0));
    m_image->m_mapping = new SCYSY3RotateMapping(0);
}


void PlayerCar::virtDoUpdate(int iCurrentTime) {
    if (!paused) {
        
        BeforeOperate(iCurrentTime);


        if (RoundCompleted >= Round) {
            getSCYSY3Engine()->ChangeState(NO_Result, false, false);
            return;
        }
        if (getEngine()->isKeyPressed(SDLK_w)) {
            //getEnergy(orientation_abs + frontWheelDirection, power);
            getEnergy(orientation_abs, power);
        }
        if (getEngine()->isKeyPressed(SDLK_a)) {
            turnLeft();
        }
        if (getEngine()->isKeyPressed(SDLK_d)) {
            turnLRight();
        }
        if (getEngine()->isKeyPressed(SDLK_s)) {
            x_abs -= cos(orientation_abs) * 2;
            y_abs -= sin(orientation_abs) * 2;
        }
        //if (getEngine()->isKeyPressed(SDLK_SPACE)) {
        //    getEnergy(0, 80000);
        //}
        

        if (!getEngine()->isKeyPressed(SDLK_a) && !getEngine()->isKeyPressed(SDLK_d)) {
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

        AfterOperate(iCurrentTime);
        //printf("%f\n", v_velocity.direction / M_PI);
    }
    
}

void PlayerCar::virtMouseDown(int iButton, int iX, int iY) {
    
}

