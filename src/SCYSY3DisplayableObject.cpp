#include "header.h"
#include "SCYSY3Engine.h"
#include "SCYSY3DisplayableObject.h"
#include "Gaming1.h"
#include "State.h"

SCYSY3DisplayableObject::SCYSY3DisplayableObject(
    int xStart, int yStart, BaseEngine* pEngine, 
    int iWidth, int iHeight, bool useTopLeftFor00, State* belong
)
    : DisplayableObject(xStart, yStart, pEngine, iWidth, iHeight, useTopLeftFor00)
    , p_BelongState(belong)
    , b_useTopLeftFor00(useTopLeftFor00)
    , x_abs(double(xStart))
    , y_abs(double(yStart))
    , orientation_abs(0)
    , mass(100)
{
    
}

SCYSY3DisplayableObject::SCYSY3DisplayableObject(
    BaseEngine* pEngine, State* belong,
    double xStart, double yStart, bool useTopLeftFor00
)
    : DisplayableObject((int)xStart, (int)yStart, pEngine, 77, 77, false)
    , p_BelongState(belong)
    , mass(1)
    , b_useTopLeftFor00(useTopLeftFor00)
{
    x_abs = xStart;
    y_abs = yStart;
    orientation_abs = double(0);
    m_iCurrentScreenX = (int)(x_abs + 0.5);
    m_iCurrentScreenY = (int)(x_abs + 0.5);
}

SCYSY3DisplayableObject::~SCYSY3DisplayableObject() {
    if (m_image != nullptr) {
        delete(m_image);
        m_image = nullptr;
    }

    if (HitMap != nullptr) {
        for (int i = 0; i < HitMap_Size; i++) {
            delete[] HitMap[i];
            HitMap[i] = nullptr;
        }
        delete[] HitMap;
        HitMap = nullptr;
    }
}

void SCYSY3DisplayableObject::createHitMap(int HitMap_Size) {
    try {
        HitMap = new bool* [HitMap_Size];
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << "Gaming1.cpp Line91" << std::endl;
    }

    for (int i = 0; i < HitMap_Size; i++) {
        HitMap[i] = new bool[HitMap_Size];
    }

    for (int y = 0; y < HitMap_Size; y++) {
        for (int x = 0; x < HitMap_Size; x++) {
            HitMap[y][x] = false;
        }
    }
}
void SCYSY3DisplayableObject::ShowHitMap(){
    //for (int i = 0; i < HitPixel.size(); i++) {
    //    p_BelongState->pState_ForeSurface->setPixel(HitPixel[i].x, HitPixel[i].y, 0xFFFFFF);
    //    //HitMap[HitPixel[i].y][HitPixel[i].x]
    //}
    for (int y = 0; y < HitMap_Size; y++) {
        for (int x = 0; x < HitMap_Size; x++) {
            if (HitMap[y][x]) {
                //p_BelongState->pState_ForeSurface->setPixel(m_iCurrentScreenX + x - HitMap_Size / 2, m_iCurrentScreenY + y - HitMap_Size / 2, 0xFFFFFF);
            }
        }
    }
    //p_BelongState->pState_ForeSurface->setPixel(HitMap_Size / 2, HitMap_Size / 2, 0x000000);
}

void SCYSY3DisplayableObject::CleanHitMap() {
    for (int i = 0; i < HitPixel.size(); i++) {
        HitMap[HitPixel[i].y + HitMap_Size / 2][HitPixel[i].x + HitMap_Size / 2] = false;
    }
}
int SCYSY3DisplayableObject::HitMapNumber() {
    int i = 0;
    for (int y = 0; y < HitMap_Size; y++) {
        for (int x = 0; x < HitMap_Size; x++) {
            if (HitMap[y][x]) {
                i++;
            }
        }
    }
    return i;
}

void SCYSY3DisplayableObject::UpdateHitMap() {
    for (int i = 0; i < HitPixel.size(); i++) {
        HitMap[HitPixel[i].y + HitMap_Size / 2][HitPixel[i].x + HitMap_Size / 2] = true;
    }
}

void SCYSY3DisplayableObject::virtDoUpdate(int iCurrentTime) {
    
}

void SCYSY3DisplayableObject::virtDraw() {
    
}


void SCYSY3DisplayableObject::setImage(std::string strURL) {
    this -> m_image = new SCYSY3Image(strURL);
}

void SCYSY3DisplayableObject::setDrawArea() {
    if (b_useTopLeftFor00) {

    }
    else{
       
    }
}
SCYSY3Engine* SCYSY3DisplayableObject::getSCYSY3Engine() {
    return static_cast<SCYSY3Engine*>(getEngine());
}

void SCYSY3DisplayableObject::syncImagePosition(SCYSY3Image* image, SCYSY3DisplayableObject* reference) {
    image -> x_abs = this-> x_abs;
    image -> y_abs = this-> y_abs;
}

void SCYSY3DisplayableObject::setPosition(double startX, double startY, double direction_base, double direction_rela, double distance) {
    x_abs = startX + distance * cos(direction_base + direction_rela);
    y_abs = startY + distance * sin(direction_base + direction_rela);
    //orientation_abs += direction;
}
void SCYSY3DisplayableObject::DoOutSideOfContainner() {

}

int SCYSY3DisplayableObject::absXtoWindowX(int absX) {
    return absX - (int)(p_BelongState->cameraX) + getEngine()->getWindowWidth()/2;
}
int SCYSY3DisplayableObject::absYtoWindowY(int absY) {
    return absY - (int)(p_BelongState->cameraY) + getEngine()->getWindowHeight()/2;
}




