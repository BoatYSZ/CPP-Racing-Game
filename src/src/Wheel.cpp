#include "header.h"
#include "Wheel.h"
#include "SCYSY3Engine.h"
Wheel::Wheel(SCYSY3DisplayableObject* relative_object1, int position)
    :SCYSY3DisplayableObject(
        relative_object1->getSCYSY3Engine(),
        relative_object1->p_BelongState,
        relative_object1->x_abs,
        relative_object1->y_abs,
        false
    ),
    position(position)
{
    relative_object = relative_object1; 
    setPosition(relative_object->x_abs, relative_object->y_abs, relative_object->orientation_abs, 0.2 * M_PI, 25);
    m_image = new SCYSY3Image("wheel.png");
    m_image->m_mapping = new SCYSY3RotateMapping(relative_object -> orientation_abs);

}

void Wheel::virtDoUpdate(int iCurrentTime) {
    if (position == 0) {
        setPosition(relative_object->x_abs, relative_object->y_abs, relative_object->orientation_abs, atan2(-19, 21), 28.3);
        orientation_abs = relative_object->orientation_abs + static_cast<Car*>(relative_object)->frontWheelDirection;
    }
    else if (position == 1) {
        setPosition(relative_object->x_abs, relative_object->y_abs, relative_object->orientation_abs, atan2(19, 21), 28.3);
        orientation_abs = relative_object->orientation_abs + static_cast<Car*>(relative_object)->frontWheelDirection;
    }
    else if (position == 2) {
        setPosition(relative_object->x_abs, relative_object->y_abs, relative_object->orientation_abs, atan2(19, -36), 40.7);
        orientation_abs = relative_object->orientation_abs;
    }
    else if (position == 3) {
        setPosition(relative_object->x_abs, relative_object->y_abs, relative_object->orientation_abs, atan2(-19, -36), 40.7);
        orientation_abs = relative_object->orientation_abs;
    }
    
    //m_iCurrentScreenX = (int)(x_abs - static_cast<Gaming1*>(p_BelongState)->cameraX + getEngine()->getWindowWidth() / 2);
    //m_iCurrentScreenY = (int)(y_abs - static_cast<Gaming1*>(p_BelongState)->cameraY + getEngine()->getWindowHeight() / 2);
    m_iCurrentScreenX = absXtoWindowX((int)x_abs);
    m_iCurrentScreenY = absYtoWindowY((int)y_abs);
    static_cast<SCYSY3RotateMapping*>(m_image->m_mapping)->setRotation( - orientation_abs);
    syncImagePosition(m_image, this);
}
void Wheel::virtDraw() {
    if (m_image != nullptr) {
        m_image->renderImageApplyingMappingAndHitPixel(
            relative_object->getSCYSY3Engine()
           ,relative_object->getSCYSY3Engine()->getForegroundSurface()
           , m_iCurrentScreenX, m_iCurrentScreenY
           ,m_image->m_mapping
           ,this
        );
    }
}