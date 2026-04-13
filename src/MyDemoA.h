#pragma once
#include "BaseEngine.h"
#include "MyTilemanager.h" // Insert this line (to define the class)!!!

class MyDemoA :
    public BaseEngine
{
public:
    void virtSetupBackgroundBuffer();
    void virtMouseDown(int iButton, int iX, int iY);
    void virtKeyDown(int iKeyCode);

protected:
    MyTileManager tm; // Insert this line (for composition)!!!
public:
    int virtInitialiseObjects();
};

