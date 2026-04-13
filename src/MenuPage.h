#pragma once
#include "State.h"
#include "BaseEngine.h"
#include "FollowMouse.h"
#include "SCYSY3Button.h"
#include "PlayerCar.h"
#include "Car.h"
#include "Point.h"
#include "Theme.h"


class MenuPage :
    public State
{

public:
    MenuPage(BaseEngine* pEngine);
    virtual ~MenuPage();
    virtual void setBackGroundForState() override;

    virtual void InitializeState();

    virtual void PreUpdate();
    virtual void DoBeforeUpdate();
    virtual void DoAfterUpdate();
    virtual void PostUpdate();

    virtual void virtPreDraw();
    virtual void virtPostDraw();
    virtual void virtMouseDown(int iButton, int iX, int iY);
    void CameraLocate(SCYSY3DisplayableObject* object);

    int GenerateMap();
    int GenerateBackGround(int mode, int theme, int** MapColor);
    void DrawImageToMap(SCYSY3Image* image, int startX, int startY, int** MapColor);
    void renderMap();

    bool ReadCheckPoint(const std::string& filePath);
    void MenuPage::elasticCollision(PhysicalObject* a, PhysicalObject* b);
    void DrawTheme(int x, int y, int** MapColor);
    int timeRecord = 0;
    int mapWidth;
    int mapHeight;
    int BlockSize = 400;
    Theme theme;
    int** MapColor1;
    int** MapColor2;
    int** MapColor3;
    int** MapData;
    std::vector<Point> RoadList;
    std::vector<Point> CheckPoint;
    Point startBlock;
    int Round = 100;
    int RoundComplete = -1;
    SCYSY3Image* map = nullptr;
    SCYSY3Image* mapGrass;
    SCYSY3Image* Grass;
    SCYSY3Image* cactus;
    SCYSY3Image* Snow;
    SCYSY3Image* TreeSnow;
    
    SCYSY3Image* flag;
    SCYSY3Image* endFlag;
    SCYSY3DisplayableObject* titleWheel;
    SCYSY3Image SPEEDpp;
    NEWGAME newGame;
    LoadGame loadGame;
    ExitGame exitGame;
    Car* AI1;
    Car* AI2;
    PlayerCar* playerCar;
    FollowMouse* f1;
    char speed[5] = { '0','0','0','0','\0' };

    
};