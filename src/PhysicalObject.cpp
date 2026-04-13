#include "header.h"
#include "SCYSY3Engine.h"
#include "PhysicalObject.h"

PhysicalObject::PhysicalObject(
      BaseEngine* pEngine
    , State* belong
    , double xStart
    , double yStart
    , bool useTopLeftFor00
)
    : SCYSY3DisplayableObject(pEngine, belong, xStart, yStart, useTopLeftFor00)
    , v_energy(0, 0)
    , v_force(0, 0)
    , v_acce(0, 0)
    , v_velocity(0, 0)
    , v_displacement(0, 0)
    , v_middle(0, 0)

{
}

PhysicalObject::~PhysicalObject(){

}

void PhysicalObject::virtDoUpdate(int iCurrentTime) {
    updatePhysicalAttribute();
    static_cast<ImagePixelMappingRotate*>(m_image->m_mapping)->setRotation((double)iCurrentTime / 1000);
    m_image->x_abs = this->x_abs;
    m_image->x_abs = this->x_abs;


    syncImagePosition(m_image, this);
}
void PhysicalObject::virtDraw() {
    if (m_image != nullptr) {
        m_image->renderImageApplyingMapping(
            getSCYSY3Engine()
            , getSCYSY3Engine()->getForegroundSurface()
            , this->x_abs, this->y_abs
            , m_image->m_mapping);
    }

    getSCYSY3Engine()->getForegroundSurface()->setPixel(m_iCurrentScreenX, m_iCurrentScreenY, 0x00FF00);
    getSCYSY3Engine()->getForegroundSurface()->setPixel(m_iCurrentScreenX + 1, m_iCurrentScreenY + 1, 0x00FF00);
    getSCYSY3Engine()->getForegroundSurface()->setPixel(m_iCurrentScreenX, m_iCurrentScreenY+1, 0x00FF00);
    getSCYSY3Engine()->getForegroundSurface()->setPixel(m_iCurrentScreenX + 1, m_iCurrentScreenY, 0x00FF00);
}

void PhysicalObject::getEnergy(double direction, double mag) {
    double a = -1;
    double b = -1;
    double c = -1;
    a = v_velocity.getX() * abs(v_velocity.getX()) + 2 * cos(direction) * abs(cos(direction)) * mag / mass;
    b = v_velocity.getY() * abs(v_velocity.getY()) + 2 * sin(direction) * abs(sin(direction)) * mag / mass;
    v_velocity.magnitude = sqrt(abs(a) + abs(b));
    if (a < 0) {
        a = a * (-1);
        a = sqrt(a);
        a = a * (-1);
    }
    else {
        a = sqrt(a);
    }
    
    if (b < 0) {
        b = b * (-1);
        b = sqrt(b);
        b = b * (-1);
    }
    else {
        b = sqrt(b);
    }
    v_velocity.direction = atan2(b, a);
}
void PhysicalObject::updatePhysicalAttribute(){
    double time = double(getSCYSY3Engine()->msPerFrame) * 0.001;
    v_displacement = (v_velocity * time);

    x_abs += v_displacement.getX();
    y_abs += v_displacement.getY();

    getEnergy(v_displacement.direction + M_PI, v_displacement.magnitude * f * mass ); //Loss energy due to overcoming ground friction
    if (v_velocity.magnitude < 8) {
        v_velocity.magnitude = 0;
    }

    m_iCurrentScreenX = (int)(x_abs - static_cast<Gaming1*>(p_BelongState)->cameraX + getEngine()->getWindowWidth() / 2);
    m_iCurrentScreenY = (int)(y_abs - static_cast<Gaming1*>(p_BelongState)->cameraY + getEngine()->getWindowHeight() / 2);
}