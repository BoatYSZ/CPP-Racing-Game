#include "header.h"
#include "Gaming1.h"
#include "MenuPage.h"
#include "SCYSY3Button.h"
#include "SCYSY3Engine.h"
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#endif


MenuPage::MenuPage(BaseEngine* pEngine) :
	State(pEngine)
	, startBlock(-1, -1)
	, theme()
	, timeRecord(time_WhenCreated)
	, SPEEDpp("SPEEDpp.png")
	, newGame(pEngine, this)
	, loadGame(pEngine, this)
	, exitGame(pEngine, this)
	
{
	getSCYSY3Engine()->GameMode = 0;
	getSCYSY3Engine()->currentMap = 0;

	SPEEDpp.x_abs = 74;
	SPEEDpp.y_abs = 50;
	NO_Page = NO_Menu;
	srand(time(0));
	
	InitializeState();
}

MenuPage::~MenuPage(void) {
	if (map != nullptr) {
		delete(map);
		map = nullptr;
	}
	delete(titleWheel);
	delete(Grass);
	delete(flag);
	delete(TreeSnow);
	delete(cactus);
	delete(endFlag);
	delete(Snow);

	for (int i = 0; i < mapHeight; i++) {
		delete[] MapColor1[i];
		MapColor1[i] = nullptr;
		delete[] MapColor2[i];
		MapColor2[i] = nullptr;
		delete[] MapColor3[i];
		MapColor3[i] = nullptr;
		delete[] MapData[i];
		MapData[i] = nullptr;
	}
	delete[] MapColor1;
	delete[] MapColor2;
	delete[] MapColor3;
	MapColor1 = nullptr;
	MapColor2 = nullptr;
	MapColor3 = nullptr;
	delete[] MapData;
	MapData = nullptr;
	State::~State();
}

void MenuPage::setBackGroundForState() {
}

void MenuPage::InitializeState() {
#ifdef _WIN32
	PlaySound(TEXT("A-Moment-Apart.wav"), NULL, SND_FILENAME | SND_ASYNC);
#endif

	titleWheel = new TitleWheel(pEngine, this, 0, 0, false);
	titleWheel->setImage("titleWheel.png");
	titleWheel->m_image->m_mapping = new ImagePixelMappingRotate(0);
	titleWheel->m_image->setTransparencyColour(0xFFFFFF);
	titleWheel->x_abs = 221 + 60;
	titleWheel->y_abs = 50 + 200;

	playerCar = new PlayerCar(pEngine, this, 500, 500, false, nullptr);
	AI1 = new Car(pEngine, this, 500, 500, false, nullptr);
	AI2 = new Car(pEngine, this, 500, 500, false, nullptr);

	map = new SCYSY3Image("Map_Grass.png");
	ReadCheckPoint("CheckPoint0.txt");
	playerCar->orientation_abs = -M_PI / 2;
	playerCar->x_abs = 662;
	playerCar->y_abs = 3006;
	AI1->orientation_abs = playerCar->orientation_abs;
	AI1->x_abs = playerCar->x_abs - 100;
	AI1->y_abs = playerCar->y_abs;
	AI2->orientation_abs = AI1->orientation_abs;
	AI2->x_abs = AI1->x_abs - 100;
	AI2->y_abs = AI1->y_abs;
	mapWidth = map->getWidth();
	mapHeight = map->getHeight();

	flag = new SCYSY3Image("Flag.png");
	Grass = new SCYSY3Image("Grass.png");
	Snow = new SCYSY3Image("Snow.png");
	TreeSnow = new SCYSY3Image("Tree_Snow.png");
	cactus = new SCYSY3Image("Cactus.png");
	endFlag = new SCYSY3Image("EndFlag.png");

	try {
		MapColor1 = new int* [mapHeight];
		MapColor2 = new int* [mapHeight];
		MapColor3 = new int* [mapHeight];
		MapData = new int* [mapHeight];
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << "MenuPage.cpp Line118" << std::endl;
	}

	for (int i = 0; i < mapHeight; i++) {
		MapColor1[i] = new int[mapWidth];
		MapColor2[i] = new int[mapWidth];
		MapColor3[i] = new int[mapWidth];
		MapData[i] = new int[mapWidth];
	}

	GenerateBackGround(0, 0, MapColor1);
	GenerateBackGround(0, 1, MapColor2);
	GenerateBackGround(0, 2, MapColor3);
	if (getSCYSY3Engine()->GameMode == 1) {
		playerCar->orientation_abs = M_PI;
		playerCar->x_abs = RoadList[0].x * 400 + 200;
		playerCar->y_abs = RoadList[0].y * 400 + 200;
		AI1->orientation_abs = playerCar->orientation_abs;
		AI1->x_abs = playerCar->x_abs - 100;
		AI1->y_abs = playerCar->y_abs - 100;
		AI2->orientation_abs = AI1->orientation_abs;
		AI2->x_abs = AI1->x_abs - 100;
		AI2->y_abs = AI1->y_abs - 100;
	}
	playerCar->CheckPoint = CheckPoint;
	AI1->CheckPoint = CheckPoint;
	AI2->CheckPoint = CheckPoint;

	pState_DisplayableObjectContainer->drawableObjectsChanged();
	pState_DisplayableObjectContainer->destroyOldObjects(true);
	pState_DisplayableObjectContainer->createObjectArray(0);
	pState_DisplayableObjectContainer->appendObjectToArray(playerCar);
	pState_DisplayableObjectContainer->appendObjectToArray(AI1);
	pState_DisplayableObjectContainer->appendObjectToArray(AI2);
	getSCYSY3Engine()->GameMode = 0;
	//getSCYSY3Engine()->RoadList.clear();
}
void MenuPage::virtMouseDown(int iButton, int iX, int iY) {
	newGame.virtMouseDown( iButton,  iX,  iY);
	loadGame.virtMouseDown( iButton,  iX,  iY);
	exitGame.virtMouseDown( iButton,  iX,  iY);
	if (iButton == SDL_BUTTON_RIGHT) {
		printf("%d %d\n", (int)cameraX + i_MouseX - pEngine->getWindowWidth() / 2, (int)cameraY + i_MouseY - pEngine->getWindowHeight() / 2);
	}
	else if (iButton == SDL_BUTTON_LEFT) {
		printf("%d %d\n", (int)cameraX + i_MouseX - pEngine->getWindowWidth() / 2, (int)cameraY + i_MouseY - pEngine->getWindowHeight() / 2);
	}
}
void MenuPage::PreUpdate() {
	SDL_GetMouseState(&i_MouseX, &i_MouseY);
	
	//CameraLocate(playerCar);
	CameraLocate(AI1);
}
void MenuPage::DoBeforeUpdate() {
	State::DoBeforeUpdate();
}
void MenuPage::DoAfterUpdate() {
	if (playerCar != nullptr && AI1 != nullptr) {
		if (playerCar->IsHit(AI1)) {
			elasticCollision(playerCar, AI1);
			//printf("hit\n");
		}
		if (playerCar->IsHit(AI2)) {
			elasticCollision(playerCar, AI2);
			//printf("hit\n");
		}
		if (AI1->IsHit(AI2)) {
			elasticCollision(AI1, AI2);
			//printf("hit\n");
		}

	}

	if (((AI1->CD_expression) == 0) && (((AI1->x_abs - playerCar->x_abs) * (AI1->x_abs - playerCar->x_abs) + (AI1->y_abs - playerCar->y_abs) * (AI1->y_abs - playerCar->y_abs)) <= 160000)) {
		AI1->SendExpression();
	}
	if (((AI2->CD_expression) == 0) && (((AI2->x_abs - playerCar->x_abs) * (AI2->x_abs - playerCar->x_abs) + (AI2->y_abs - playerCar->y_abs) * (AI2->y_abs - playerCar->y_abs)) <= 160000)) {
		AI2->SendExpression();
	}
}
void MenuPage::PostUpdate() {

}

void MenuPage::virtPreDraw() {
	renderMap();

	if (CheckPoint.size() > 0) {
		//for (int i = 0; i < playerCar->CheckPoint.size(); i++) {
		//	flag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(playerCar->CheckPoint[i].x), playerCar->absYtoWindowY(playerCar->CheckPoint[i].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		//}
		//flag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(CheckPoint[playerCar->Next_NO].x), playerCar->absYtoWindowY(CheckPoint[playerCar->Next_NO].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		//flag->renderImageWithMask(pState_ForeSurface, 0, 0, AI1->absXtoWindowX(CheckPoint[AI1->Next_NO].x), AI1->absYtoWindowY(CheckPoint[AI1->Next_NO].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		if (playerCar->CheckPoint.size() >= 1) {
			endFlag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(playerCar->CheckPoint[CheckPoint.size() - 1].x), playerCar->absYtoWindowY(playerCar->CheckPoint[CheckPoint.size() - 1].y), endFlag->getWidth(), endFlag->getHeight(), 0xff0000);
		}
	}

}

void MenuPage::virtPostDraw() {
	//SPEEDpp.renderImageWithMaskAndReplace2(pState_ForeSurface, pState_BackSurface, 0, 0, SPEEDpp.x_abs, SPEEDpp.y_abs, SPEEDpp.getWidth(), SPEEDpp.getHeight(), 0xFFFFFF);
	SPEEDpp.renderImageWithMaskAndTransparency(pState_ForeSurface, 0, 0, (int)SPEEDpp.x_abs, (int)SPEEDpp.y_abs, SPEEDpp.getWidth(), SPEEDpp.getHeight(), 0xFFFFFF, 70);
	newGame.DoOutSideOfContainner();
	loadGame.DoOutSideOfContainner();
	exitGame.DoOutSideOfContainner();
	titleWheel->DoOutSideOfContainner();
}


void MenuPage::CameraLocate(SCYSY3DisplayableObject* object) {
	if ((int)(object->x_abs + 0.5) <= pEngine->getWindowWidth() / 2) {
		cameraX = pEngine->getWindowWidth() / 2;
	}
	else if ((int)(object->x_abs + 0.5) >= mapWidth - pEngine->getWindowWidth() / 2) {
		cameraX = mapWidth - pEngine->getWindowWidth() / 2;
	}
	else {
		cameraX = (int)(object->x_abs + 0.5);
	}

	if ((int)(object->y_abs + 0.5) <= pEngine->getWindowHeight() / 2) {
		cameraY = pEngine->getWindowHeight() / 2;
	}
	else if ((int)(object->y_abs + 0.5) >= mapHeight - pEngine->getWindowHeight() / 2) {
		cameraY = mapHeight - pEngine->getWindowHeight() / 2;
	}
	else {
		cameraY = (int)(object->y_abs + 0.5);
	}
}

void MenuPage::renderMap() {
	int thresheld = 4000;
	int time = pEngine->getRawTime();
	
	pState_BackSurface->mySDLLockSurface();
	for (int y = 0; y < pEngine->getWindowHeight(); y++) {
		for (int x = 0; x < pEngine->getWindowWidth(); x++) {
			int now = (time + x + y) % 12000;
			if (now < thresheld) {
				pState_BackSurface->setPixel(x, y, MapColor1[(int)cameraY - pEngine->getWindowHeight() / 2 + y][(int)cameraX - pEngine->getWindowWidth() / 2 + x]);

			}
			else if(now < thresheld*2) {
				pState_BackSurface->setPixel(x, y, MapColor2[(int)cameraY - pEngine->getWindowHeight() / 2 + y][(int)cameraX - pEngine->getWindowWidth() / 2 + x]);
			}
			else if(now < thresheld*3) {
				pState_BackSurface->setPixel(x, y, MapColor3[(int)cameraY - pEngine->getWindowHeight() / 2 + y][(int)cameraX - pEngine->getWindowWidth() / 2 + x]);
			}
			
		}
	}
	pState_BackSurface->mySDLUnlockSurface();
}

int MenuPage::GenerateMap() { return 0; }

int MenuPage::GenerateBackGround(int mode, int theme, int** MapColor) {
	if (theme == 0) {
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				MapColor[y][x] = 0x80FF80;

			}
		}
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				if ((y % (Grass->getHeight() * 3)) == 0 && (x % (Grass->getWidth() * 3)) == 0) {
					int r = rand();
					if ((r % 10) == 1) {
						DrawImageToMap(Grass, x, y, MapColor);
					}
				}

			}
		}
	}
	else if (theme == 1) {
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				MapColor[y][x] = 0xFFFFFF;

			}
		}
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				if ((y % (Snow->getHeight() * 3)) == 0 && (x % (Snow->getWidth() * 3)) == 0) {
					int r = rand();
					if ((r % 10) <= 2) {
						DrawImageToMap(Snow, x, y, MapColor);
					}

				}

			}
		}
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				if ((y % (TreeSnow->getHeight() * 3)) == 0 && (x % (TreeSnow->getWidth() * 3)) == 0) {
					int r = rand();
					if ((r % 10) >= 8) {
						DrawImageToMap(TreeSnow, x, y, MapColor);
					}

				}

			}
		}
	}
	else if (theme == 2) {
		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				MapColor[y][x] = 0xF7D700;

			}
		}

		for (int y = 0; y < mapHeight; y++) {
			for (int x = 0; x < mapWidth; x++) {
				if ((y % (TreeSnow->getHeight() * 5)) == 0 && (x % (TreeSnow->getWidth() * 5)) == 0) {
					int r = rand();
					if ((r % 10) >= 8) {
						DrawImageToMap(cactus, x, y, MapColor);
					}

				}

			}
		}

	}

	if (mode == 0) {
		for (int y = 0; y < mapHeight; y++) {	//Road
			for (int x = 0; x < mapWidth; x++) {
				if (map->getPixelColour(x, y) == 0xFF0000) {
					MapData[y][x] = 0;
				}
				else {
					if (theme == 0) {
						MapColor[y][x] = 0xD1BB86;
					}
					else if(theme ==1)
					{
						MapColor[y][x] = 0xA0A0B0;
					}
					else if (theme == 2) {
						MapColor[y][x] = 0xC0C0B0;
					}
					
					MapData[y][x] = 1;
				}
			}
		}
	}
	else if (mode == 1) {
		
		for (int i = 0; i < RoadList.size(); i++) {
			CheckPoint.emplace_back(RoadList[i].x * 400 + 200, RoadList[i].y * 400 + 200);
		}
	}

	return 0;
}

void MenuPage::DrawImageToMap(SCYSY3Image* image, int startX, int startY, int**MapColor) {
	for (int y = 0; y < image->getHeight(); y++) {
		for (int x = 0; x < image->getWidth(); x++) {
			if ((startX + x >= 0 && startX + x < mapWidth) && (startY + y >= 0 && startY + y < mapHeight)) {
				int color = image->getPixelColour(x, y);
				if (color != 0xff0000) {
					MapColor[startY + y][startX + x] = color;
					MapData[startY + y][startX + x] = 1;
				}
			}
		}
	}
}

bool MenuPage::ReadCheckPoint(const std::string& filePath) {
	std::ifstream infile(filePath);

	if (!infile.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return true;
	}
	std::string line;
	while (getline(infile, line)) {
		std::istringstream iss(line);
		int x, y;

		if (iss >> x >> y) {
			CheckPoint.push_back(Point(x, y));
		}
		else {
			std::cerr << "Error reading line: " << line << std::endl;
		}
	}
	return true;
}


void MenuPage::elasticCollision(PhysicalObject* a, PhysicalObject* b) {
	double& directionA = a->v_velocity.direction;
	double& magnitudeA = a->v_velocity.magnitude;
	double& directionB = b->v_velocity.direction;
	double& magnitudeB = b->v_velocity.magnitude;
	double Ax = a->x_abs;
	double Ay = a->y_abs;
	double Bx = b->x_abs;
	double By = b->y_abs;

	double v1x = magnitudeA * cos(directionA);
	double v1y = magnitudeA * sin(directionA);
	double v2x = magnitudeB * cos(directionB);
	double v2y = magnitudeB * sin(directionB);


	double dx = Bx - Ax;
	double dy = By - Ay;
	double distance = sqrt(dx * dx + dy * dy);
	double nx = dx / distance;
	double ny = dy / distance;

	double u1 = v1x * nx + v1y * ny;
	double u2 = v2x * nx + v2y * ny;


	double un1 = u2;
	double un2 = u1;


	v1x += (un1 - u1) * nx;
	v1y += (un1 - u1) * ny;
	v2x += (un2 - u2) * nx;
	v2y += (un2 - u2) * ny;

	magnitudeA = sqrt(v1x * v1x + v1y * v1y);
	directionA = atan2(v1y, v1x);
	magnitudeB = sqrt(v2x * v2x + v2y * v2y);
	directionB = atan2(v2y, v2x);
}





