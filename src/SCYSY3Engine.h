#pragma once
#include "BaseEngine.h"
#include "UtilCollisionDetection.h"
#include "ImageManager.h"

#include "MyObjectB.h"
#include "ChangingText.h"
#include "FollowMouse.h"
#include "AutoMoving.h"
#include "SCYSY3TileManager.h"

#include "TitlePage.h"
#include "MenuPage.h"
#include "SelectMode.h"
#include "SelectMap.h"
#include "CreateMap.h"
#include "Gaming1.h"
#include "ResultPage.h"

#include "SCYSY3DisplayableObject.h"
#include "PhysicalObject.h"
#include "Car.h"
#include "PlayerCar.h"
#include "SCYSY3FilterPoints.h" 

const int NO_Title = 0;
const int NO_Menu = 1;
const int NO_SelectMode = 2;
const int NO_SelectMap = 3;
const int NO_CreateMap = 4;
const int NO_Gaming1 = 5;
const int NO_Result = 6;

const int Theme_Grass = 0;
const int Theme_Snow = 1;
const int Theme_Desert = 2;
const int NameLength = 30;

class SCYSY3Engine :
    public BaseEngine
{
public:
    SCYSY3Engine::SCYSY3Engine();
    SCYSY3Engine::~SCYSY3Engine();
    int virtInitialise();
    void deinitialise();
    void virtCreateWindows(const char* szCaption);
    

    virtual void virtMouseDown(int iButton, int iX, int iY);
    virtual void virtKeyDown(int iKeyCode);
    void SCYSY3Engine::virtMouseWheel(int x, int y, int which, int timestamp);
    bool virtCheckForUpdateTime(void);
    void virtSetupBackgroundBuffer();
    int virtInitialiseObjects();
    virtual void virtCreateSurfaces();
    virtual void destroyOldObjects(bool dDelete);
    void virtCleanUp(void);

    virtual void virtMainLoopPreUpdate();
    virtual void virtMainLoopDoBeforeUpdate();
    virtual void virtMainLoopDoAfterUpdate();
    virtual void virtMainLoopPostUpdate();

    virtual void virtPreDraw();
    virtual void virtPostDraw();

    void CreateState(int NO_State);
    State* CreateNewTitlePage();
    State* CreateNewMenuPage();
    State* CreateNewGaming1();
    State* CreateNewResult();
    State* SCYSY3Engine::CreateNewSelectMode();
    State* SCYSY3Engine::CreateNewSelectMap();
    State* SCYSY3Engine::CreateNewCreateMap();
    void deleteState(int state_NO);
    void ChangeState(int toState, bool save, bool refresh);
    void ContainerTransfer(DisplayableObjectContainer* from, DisplayableObjectContainer* to);
    std::vector<State*> vec_StateArray;
    typedef State* (SCYSY3Engine::* StateCreator)();
    StateCreator stateCreators[7];

    int pCurrentState;
    int i_MouseX;
    int i_MouseY;
    int msPerFrame = 17;

    char playName[NameLength]="";
    int currentNameLength = 0;
    int LastPressedKey = -1;

    bool ifChangeState = false;
    int toState;
    bool save;
    bool refresh;
    int fps = 0;
    int last_time = 0;
    char fps_c[10]= "1";
    int currentTheme = 1;
    int currentMap = 0;
    bool validMap = false;
    std::vector<Point> RoadList;
    int GameMode = 0;
    bool ShouldLoad = false;
    int MapBlock[15][15] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    SCYSY3FilterPoints scysy3filterPoints;
};  

