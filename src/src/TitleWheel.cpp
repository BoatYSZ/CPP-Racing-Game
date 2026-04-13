#include "header.h"
#include "SCYSY3Engine.h"
#include "TitleWheel.h"
#include "TitlePage.h"

TitleWheel::TitleWheel(
      BaseEngine* pEngine = nullptr
    , State* belong = nullptr
    , double xStart = 88
    , double yStart = 88
    , bool useTopLeftFor00 = false)
  :SCYSY3DisplayableObject(
       pEngine
        ,belong
        ,xStart
        ,yStart
        ,useTopLeftFor00
    )
{

}

void TitleWheel::virtDraw() {

}

void TitleWheel::virtDoUpdate(int iCurrentTime) {
    
}

void TitleWheel::DoOutSideOfContainner() {
    
    static_cast<ImagePixelMappingRotate*>(m_image->m_mapping)->setRotation((double)(p_BelongState->time_FromCreated) / 500.0);
    syncImagePosition(m_image, this);
    if (canShow) {
        if (m_image != nullptr) {
            m_image->renderImageApplyingMapping(
                getSCYSY3Engine()
                , getSCYSY3Engine()->getForegroundSurface()
                , x_abs
                , y_abs
                , m_image->m_mapping);
        }
    }
}