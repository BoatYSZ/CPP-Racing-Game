#pragma once
#include "BaseEngine.h"
#include "DisplayableObject.h"
#include "ImagePixelMapping.h"
#include "State.h"
#include "SCYSY3Image.h"
#include "SCYSY3RotateMapping.h"
#include "Point.h"

class SCYSY3Engine; 

class SCYSY3DisplayableObject :
    public DisplayableObject
{
public:
    SCYSY3DisplayableObject(
          int xStart = 88
        , int yStart = 88
        , BaseEngine* pEngine = nullptr
        , int iWidth = 8
        , int iHeight = 8
        , bool useTopLeftFor00 = true
        , State* belong = nullptr
    );

    SCYSY3DisplayableObject(
          BaseEngine* pEngine = nullptr
        , State* belong = nullptr
        , double xStart = 88
        , double yStart = 88
        , bool useTopLeftFor00 = false
    );
    virtual ~SCYSY3DisplayableObject();
    virtual void virtDoUpdate(int iCurrentTime);
    virtual void virtDraw();
    virtual long virtNotify(int iSignalNumber, int x, int y) { 
        printf("ID:%d at %d %d existing\n", ID, (int)x_abs, (int)y_abs);
        return 0; 
    }
    virtual void DoOutSideOfContainner();

    SCYSY3Engine* getSCYSY3Engine();
    void setImage(std::string strURL);
    void setDrawArea();
    void syncImagePosition(SCYSY3Image* image, SCYSY3DisplayableObject* reference);
    void setPosition(double startX, double startY, double direction_base, double direction_rela ,double distance);
    int absXtoWindowX(int absX);
    int absYtoWindowY(int absY);

    virtual void createHitMap(int HitMap_Size);
    virtual void ShowHitMap();
    virtual void CleanHitMap();
    virtual void UpdateHitMap();
    virtual int SCYSY3DisplayableObject::HitMapNumber();
    bool b_useTopLeftFor00;
    State* p_BelongState;
    SCYSY3DisplayableObject* relative_object = nullptr;
    SCYSY3Image* m_image = nullptr;

    std::vector<Point> HitPixel ;
    bool** HitMap = nullptr;
    int HitMap_Size = 0;
    int ID = -1;
    

    double x_abs;
    double y_abs;
    double orientation_abs;

    double x_rela = 0;
    double y_rela = 0;
    double orientation_rela = 0;
    double mass;


    bool canShow = true;
    bool paused = false;
};

