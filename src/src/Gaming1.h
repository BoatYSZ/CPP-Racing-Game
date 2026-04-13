#pragma once
#include "State.h"
#include "BaseEngine.h"
#include "FollowMouse.h"
#include "SCYSY3Button.h"
#include "PlayerCar.h"
#include "Car.h"
#include "Point.h"
#include "Theme.h"
const int rows = 15;
const int cols = 15;

class PauseButton :
    public SCYSY3Button
{
public:
    PauseButton(BaseEngine* pEngine, State* belong);
    ~PauseButton();

    void PauseButton::clickedAndDo();
    void PauseButton::DoOutSideOfContainner();
    SCYSY3Image NotStopIcon;
    SCYSY3Image StopIcon;
    bool stop = false;
};

class Continue :
    public NEWGAME
{
public:
    Continue(BaseEngine* pEngine, State* belong);

    void Continue::clickedAndDo() {

    }

    void DoOutSideOfContainner() {
        if (canShow) {
            p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

            if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
                p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0xFF0000);
            }
            else
            {
                p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0x000000);
            }
        }
    }
    int link;
    bool canShow = false;
    char* text = "CONTINUE";
};

class EndGame :
    public NEWGAME
{
public:
    EndGame(BaseEngine* pEngine, State* belong);

    void EndGame::clickedAndDo() {
        ChangeState(link, false, false);
    }

    void EndGame::virtMouseDown(int iButton, int iX, int iY) {
        if (canShow) {
            if (virtIsHover(iX, iY)) {
                clickedAndDo();
            }
        }
    }
    void DoOutSideOfContainner() {
        if (canShow) {
            p_BelongState->pEngine->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth, m_iCurrentScreenY + m_iDrawHeight, 0xA0A0A0);

            if (virtIsHover(p_BelongState->i_MouseX, p_BelongState->i_MouseY)) {
                p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0xFF0000);
            }
            else
            {
                p_BelongState->pEngine->drawForegroundString(m_iCurrentScreenX + 75, m_iCurrentScreenY + 10, text, 0x000000);
            }
        }
    }
    //Gaming1* p = static_cast<Gaming1*>(p_BelongState);
    int link;
    bool canShow = false;
    char* text = "SAVE AND END";
};



class Gaming1 :
    public State
{

public:
    Gaming1(BaseEngine* pEngine);
    virtual ~Gaming1();
    virtual void setBackGroundForState() override;
  
    virtual void InitializeState();

    virtual void PreUpdate();
    virtual void DoBeforeUpdate();
    virtual void DoAfterUpdate();
    virtual void PostUpdate();

    virtual void virtPreDraw();
    virtual void virtPostDraw();
    virtual void virtMouseDown(int iButton, int iX, int iY);
    virtual void virtMouseWheel(int x, int y, int which, int timestamp);
    void CameraLocate(SCYSY3DisplayableObject* object);
    
    int GenerateMap();
    int GenerateBackGround(int mode, int theme, int** MapColor);
    void DrawImageToMap(SCYSY3Image* image, int startX, int startY);
    void renderMap();
    int DrawStuff();
    int DrawCustomRoad();

    int FindNextBlock(Point& current, int NO);
    bool ReadCheckPoint(const std::string& filePath);
    bool WriteCheckPoint(const std::string& filePath);
    void Gaming1::elasticCollision(PhysicalObject* a, PhysicalObject* b);
    void Gaming1::Save();
    void Gaming1::Load();
    int mapWidth;
    int mapHeight;
    int BlockSize = 400;
    Theme theme;
    int MapBlock[rows][cols] = {
    {37, 38, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    {36, 1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0 },
    {35, 34, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0 },
    {0, 33, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
    {0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17 },
    {0, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18 },
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
    bool shouldSaveGame = false;
    int** MapColor;
    int** MapData;
    std::vector<Point> RoadList;
    std::vector<Point> CheckPoint;
    Point startBlock;
    int Round = 5;
    int RoundComplete = -1;
    PauseButton stopButton;
    Continue continueButton;
    EndGame endGame;
    SCYSY3Image* map = nullptr;

    SCYSY3Image* mapGrass;
    SCYSY3Image* Grass;
    SCYSY3Image* cactus;
    //SCYSY3Image* mapSnow;
    //SCYSY3Image* mapSand;
    //SCYSY3Image* Map_Grass;
    SCYSY3Image* Snow;
    SCYSY3Image* TreeSnow;
    SCYSY3Image* UD;
    SCYSY3Image* LR;
    SCYSY3Image* UL;
    SCYSY3Image* UR;
    SCYSY3Image* DL;
    SCYSY3Image* DR;
    SCYSY3Image* panel;
    SCYSY3Image* flag;
    SCYSY3Image* endFlag;
    PlayerCar* playerCar;
    Car* AI1;
    Car* AI2;
    FollowMouse* f1;
    char speed[5] = {'0','0','0','0','\0'};
    
};
