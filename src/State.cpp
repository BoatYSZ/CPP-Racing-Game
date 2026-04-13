#include "header.h"
#include "State.h"
#include "SCYSY3Engine.h"

State::State(BaseEngine* pEngine):
	pEngine(pEngine),
	state_ForeSurface(pEngine),
	state_BackSurface(pEngine),
	state_DisplayableObjectContainer(7),
	NO_Page(-1),
	time_WhenCreated(pEngine->getRawTime())
	,timeRecord(time_WhenCreated)
{
	pState_ForeSurface = &state_ForeSurface;
	pState_BackSurface = &state_BackSurface;

	pState_ForeSurface->createSurface(pEngine->getWindowWidth(), pEngine->getWindowHeight());
	pState_BackSurface->createSurface(pEngine->getWindowWidth(), pEngine->getWindowHeight());

	pState_DisplayableObjectContainer = &state_DisplayableObjectContainer;
}


State::~State(void){
	
}
SCYSY3Engine* State::getSCYSY3Engine() {
	return static_cast<SCYSY3Engine*>(pEngine);
}
void State::setBackGroundForState(){
	pEngine->fillBackground(0xFFFF00);	
}

void State::InitializeState() {

}


void State::virtMouseDown(int iButton, int iX, int iY) {
	
}

void State::virtKeyDown(int iKeyCode) {

}
void State::virtMouseWheel(int x, int y, int which, int timestamp) {

}
void State::PreUpdate() {
	SDL_GetMouseState(&i_MouseX, &i_MouseY);
}

void State::DoBeforeUpdate() {
	time_Increment = getSCYSY3Engine()->getRawTime() - timeRecord;
	time_FromCreated += time_Increment;
	timeRecord = getSCYSY3Engine()->getRawTime();
}

void State::DoAfterUpdate() {

}

void State::PostUpdate() {

}

void State::virtPreDraw() {

}
void State::virtPostDraw() {
}
//SCYSY3Engine* State::getSCYSY3Engine() {
//	return nullptr;
//		//dynamic_cast<SCYSY3Engine*>(pEngine);
//}

