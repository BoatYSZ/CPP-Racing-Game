#pragma once
#include "State.h"
#include "BaseEngine.h"
#include "FollowMouse.h"
#include "SCYSY3Button.h"
#include "UtilMovementPosition.h"
#include "TitleWheel.h"

class TitlePage :
    public State
{

public:
    TitlePage(BaseEngine* pEngine);
    virtual ~TitlePage();
    virtual void InitializeState();
    virtual void setBackGroundForState() override;
    

    virtual void PreUpdate();
    virtual void DoBeforeUpdate();
    virtual void DoAfterUpdate();
    virtual void PostUpdate();

    virtual void virtPreDraw();
    virtual void virtPostDraw();

    
    SCYSY3Button* b1;
    FollowMouse* f1;
    SCYSY3Image S;
    SCYSY3Image P;
    SCYSY3Image E1;
    SCYSY3Image E2;
    SCYSY3Image D;
    SCYSY3Image plus1;
    SCYSY3Image plus2;
    MovementPosition Move_S;
    MovementPosition Move_P;
    MovementPosition Move_E1;
    MovementPosition Move_E2;
    MovementPosition Move_D;
    MovementPosition Move_plus1;
    MovementPosition Move_plus2;

    ClickToStart* clickTostart;
    TitleWheel* titleWheel;
    bool titleGoUp = false;
    bool titleStop = false;
};

