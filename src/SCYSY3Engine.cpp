#include "header.h"
#include "SCYSY3Engine.h"
#ifdef _WIN32
#include <Windows.h>
#endif


SCYSY3Engine::SCYSY3Engine()
	:BaseEngine()
	, vec_StateArray(7)
	, pCurrentState(NO_Title)
	, scysy3filterPoints(this, this)
{	
}

SCYSY3Engine::~SCYSY3Engine(){
	destroyOldObjects(true);
}

int SCYSY3Engine::virtInitialise()
{
	scysy3filterPoints.Initialize();
	//getBackgroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	//getForegroundSurface()->setDrawPointsFilter(&m_filterTranslation);
	// Set up the initial background
	m_pBackgroundSurface->mySDLLockSurface();
	virtSetupBackgroundBuffer();
	m_pBackgroundSurface->mySDLUnlockSurface();

	stateCreators[NO_Title] = &SCYSY3Engine::CreateNewTitlePage;
	stateCreators[NO_Menu] = &SCYSY3Engine::CreateNewMenuPage;
	stateCreators[NO_SelectMode] = &SCYSY3Engine::CreateNewSelectMode;
	stateCreators[NO_SelectMap] = &SCYSY3Engine::CreateNewSelectMap;
	stateCreators[NO_CreateMap] = &SCYSY3Engine::CreateNewCreateMap;
	stateCreators[NO_Gaming1] = &SCYSY3Engine::CreateNewGaming1;
	stateCreators[NO_Result] = &SCYSY3Engine::CreateNewResult;
	//ChangeState(NO_Title, false, false);
	//vec_StateArray[NO_Title] = new TitlePage(this);
	//vec_StateArray[NO_Menu] = new MenuPage(this);
	//vec_StateArray[NO_Gaming1] = new Gaming1(this);
	//vec_StateArray[NO_Result] = new ResultPage(this);
	CreateState(pCurrentState);

	m_pBackgroundSurface = vec_StateArray[pCurrentState]->pState_BackSurface;
	m_pForegroundSurface = vec_StateArray[pCurrentState]->pState_ForeSurface;
	vec_StateArray[pCurrentState]->setBackGroundForState();
	// Create the moving objects
	virtInitialiseObjects();

	return 0; // success
}


void SCYSY3Engine::deinitialise(void)
{
	ContainerTransfer(this, (vec_StateArray[pCurrentState]->pState_DisplayableObjectContainer));
	for (int i = 0; i < vec_StateArray.size(); i++)
	{
		if (vec_StateArray[i] != nullptr) {
			delete(vec_StateArray[i]);
		}
	}
	virtCleanUp();
	delete[] m_pKeyStatus;
}


void SCYSY3Engine::virtMouseDown(int iButton, int iX, int iY) {
	vec_StateArray[pCurrentState]->virtMouseDown(iButton, iX, iY);
}

void SCYSY3Engine::virtKeyDown(int iKeyCode) {
	vec_StateArray[pCurrentState]->virtKeyDown(iKeyCode);
}
void SCYSY3Engine::virtMouseWheel(int x, int y, int which, int timestamp)
{
	vec_StateArray[pCurrentState]->virtMouseWheel(x, y, which, timestamp);
}


void SCYSY3Engine::virtCreateWindows(const char* szCaption)
{
#ifdef _WIN32
	m_pSDL2Window = SDL_CreateWindow(szCaption,
		(GetSystemMetrics(SM_CXSCREEN) - m_iWindowWidth)/2, (GetSystemMetrics(SM_CYSCREEN) - m_iWindowHeight) / 2, 
		m_iWindowWidth, m_iWindowHeight,
		0/*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL*/);
#else
	m_pSDL2Window = SDL_CreateWindow(szCaption,
		400, 100,
		m_iWindowWidth, m_iWindowHeight,
		0/*SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL*/);
#endif
	m_pSDL2Renderer = SDL_CreateRenderer(m_pSDL2Window, -1, 0);
	
	m_pSDL2Texture = SDL_CreateTexture(m_pSDL2Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_iWindowWidth, m_iWindowHeight);
}
void SCYSY3Engine::virtMainLoopPreUpdate() {

	if (ifChangeState) {
		if (pCurrentState != toState) {

			ContainerTransfer(this, (vec_StateArray[pCurrentState]->pState_DisplayableObjectContainer));
			if (save) {

			}
			else {
				delete(vec_StateArray[pCurrentState]);
				vec_StateArray[pCurrentState] = nullptr;
			}

			if (refresh) {
				if (vec_StateArray[toState] != nullptr) {
					delete(vec_StateArray[toState]);
				}
				CreateState(toState);
			}
			else {
				if (vec_StateArray[toState] == nullptr) {
					CreateState(toState);
				}
			}

			pCurrentState = toState;
			ContainerTransfer(vec_StateArray[pCurrentState]->pState_DisplayableObjectContainer, this);

			this->m_pBackgroundSurface = vec_StateArray[pCurrentState]->pState_BackSurface;
			this->m_pForegroundSurface = vec_StateArray[pCurrentState]->pState_ForeSurface;

			vec_StateArray[pCurrentState]->setBackGroundForState();


		}
		ifChangeState = false;
	}
	vec_StateArray[pCurrentState]->PreUpdate();
}
void SCYSY3Engine::virtMainLoopDoBeforeUpdate() {
	SDL_GetMouseState(&i_MouseX, &i_MouseY);
	vec_StateArray[pCurrentState]->DoBeforeUpdate();
}
void SCYSY3Engine::virtMainLoopDoAfterUpdate() {
	vec_StateArray[pCurrentState]->DoAfterUpdate();
}
void SCYSY3Engine::virtMainLoopPostUpdate() {
	redrawDisplay();
}

void SCYSY3Engine::virtPreDraw() {
	vec_StateArray[pCurrentState]->virtPreDraw();
}

void SCYSY3Engine::virtPostDraw() {
	
	vec_StateArray[pCurrentState]->virtPostDraw();
	////fps = 1000 / (getRawTime() - last_time);
	//if (getRawTime() - last_time >= 1000){
	//	std::strcpy(fps_c, std::to_string(fps).c_str());
	//	fps = 1;
	//}
	//else
	//{
	//	fps++;
	//	last_time = getRawTime();
	//}
	//drawForegroundString(0, 0, fps_c, 0xff0000);
	
}

bool SCYSY3Engine::virtCheckForUpdateTime(void)
{

	if (m_iDefaultUpdatePeriod < msPerFrame)
		m_iDefaultUpdatePeriod = msPerFrame;

	if (this->isTimeToAct())
	{
		this->setTimeToAct(m_iDefaultUpdatePeriod);
		return true;
	}
	else
	{
		return false;
	}
}

void SCYSY3Engine::virtSetupBackgroundBuffer()
{

}

int SCYSY3Engine::virtInitialiseObjects()
{
	// Record the fact that we are about to change the array
	// so it doesn't get used elsewhere without reloading it
	drawableObjectsChanged();
	SCYSY3Engine::destroyOldObjects(true);
	createObjectArray(1);
	
	this->notifyObjectsAboutMouse(true);
	this->notifyObjectsAboutKeys(true);
	
	ContainerTransfer(vec_StateArray[pCurrentState]->pState_DisplayableObjectContainer, this);
	
	setAllObjectsVisible(true);
	return 0;
}

void SCYSY3Engine::virtCreateSurfaces()
{
	BaseEngine::virtCreateSurfaces();
}
void SCYSY3Engine::destroyOldObjects(bool dDelete)
{
	drawableObjectsChanged();
	for (int i = 0; i < m_vecDisplayableObjects.size(); i++)
	{
		DisplayableObject* pOb = m_vecDisplayableObjects[i];
		m_vecDisplayableObjects[i] = nullptr;
		if (pOb != nullptr){
			if (dDelete && pOb->deleteOnRemoval())
				delete pOb;
		}
	}
	m_iCurrentItemIndex = 0;
}

void SCYSY3Engine::virtCleanUp(void)
{
	this->clearContents();
}

void SCYSY3Engine::ContainerTransfer(DisplayableObjectContainer* from, DisplayableObjectContainer* to) {
	to->createObjectArray(from->getContentCount());
	for (int i = 0; i < from->getContentCount(); i++) {
		to->storeObjectInArray(i, from->getContentItem(i));
		from->storeObjectInArray(i, nullptr);
	}
}

void SCYSY3Engine::ChangeState(int toState, bool save, bool refresh) {
	ifChangeState = true;
	this->toState = toState;
	this->save = save;
	this->refresh = refresh;
}

void SCYSY3Engine::deleteState(int state_NO){
	delete(vec_StateArray[state_NO]);
}


State* SCYSY3Engine::CreateNewTitlePage(){
	vec_StateArray[NO_Title] = new TitlePage(this);
	return vec_StateArray[NO_Title];
}

State* SCYSY3Engine::CreateNewMenuPage(){
	vec_StateArray[NO_Menu] = new MenuPage(this);
	return vec_StateArray[NO_Menu];
}
State* SCYSY3Engine::CreateNewSelectMode() {
	vec_StateArray[NO_SelectMode] = new SelectMode(this);
	return vec_StateArray[NO_SelectMode];
}
State* SCYSY3Engine::CreateNewSelectMap() {
	vec_StateArray[NO_SelectMap] = new SelectMap(this);
	return vec_StateArray[NO_SelectMap];
}
State* SCYSY3Engine::CreateNewCreateMap() {
	vec_StateArray[NO_CreateMap] = new CreateMap(this);
	return vec_StateArray[NO_CreateMap];
}

State* SCYSY3Engine::CreateNewGaming1() {
	vec_StateArray[NO_Gaming1] = new Gaming1(this);
	return vec_StateArray[NO_Gaming1];
}
State* SCYSY3Engine::CreateNewResult() {
	vec_StateArray[NO_Result] = new ResultPage(this);
	return vec_StateArray[NO_Result];
}
void SCYSY3Engine::CreateState(int NO_State) {
	(this->*stateCreators[NO_State])();
}


