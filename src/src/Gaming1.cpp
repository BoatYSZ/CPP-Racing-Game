#include "header.h"
#include "Gaming1.h"
#include "SCYSY3Button.h"
#include "SCYSY3Engine.h"
#include <fstream>
#include <sstream>
//#include <SFML/Audio.hpp>
//#include "SDL.h"
//#include "SDL_mixer.h"

Gaming1::Gaming1(BaseEngine* pEngine) :
	State(pEngine)
	, startBlock(-1, -1)
	, stopButton(pEngine, this)
	, continueButton(pEngine, this)
	, endGame(pEngine, this)
	, theme()
	
{
	pState_ForeSurface->setDrawPointsFilter(&(getSCYSY3Engine()->scysy3filterPoints));
	pState_BackSurface->setDrawPointsFilter(&(getSCYSY3Engine()->scysy3filterPoints));
	NO_Page = NO_Gaming1;
	srand(time(0));
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			MapBlock[y][x] = getSCYSY3Engine()->MapBlock[y][x];
		}
	}
	InitializeState();
}

Gaming1::~Gaming1(void) {
	//if (getSCYSY3Engine()->GameMode == 0) {
	//	if (getSCYSY3Engine()->currentMap == 0) {
	//		WriteCheckPoint("CheckPoint0.txt");
	//	}
	//	else if (getSCYSY3Engine()->currentMap == 1) {
	//		WriteCheckPoint("CheckPoint1.txt");
	//	}
	//	else if (getSCYSY3Engine()->currentMap == 2) {
	//		WriteCheckPoint("CheckPoint2.txt");
	//	}
	//}
	if (getSCYSY3Engine()->GameMode == 0 ) {
		Save();
	}
	
	if (map != nullptr) {
		delete(map);
		map = nullptr;
	}
	
	delete(Grass);
	delete(UD);
	delete(LR);
	delete(UL);
	delete(UR);
	delete(DL);
	delete(DR);
	delete(panel);
	delete(flag);
	delete(TreeSnow);
	delete(cactus);
	delete(endFlag);
	delete(Snow);


	for (int i = 0; i < mapHeight; i++) {
		delete[] MapColor[i];
		MapColor[i] = nullptr;
		delete[] MapData[i];
		MapData[i] = nullptr;
	}
	delete[] MapColor;
	MapColor = nullptr;
	delete[] MapData;
	MapData = nullptr;
	State::~State();
	
	//pState_DisplayableObjectContainer->destroyOldObjects(true);
}

void Gaming1::setBackGroundForState() {
	//pEngine->fillBackground(0x808080);
}


void Gaming1::InitializeState(){
	playerCar = new PlayerCar(pEngine, this, 500, 500, false, nullptr);
	AI1 = new Car(pEngine, this, 500, 500, false, nullptr);
	AI2 = new Car(pEngine, this, 500, 500, false, nullptr);
	if (getSCYSY3Engine()->ShouldLoad) {
		Load();
	}
	else
	{
		if (getSCYSY3Engine()->GameMode == 0) {
			if (getSCYSY3Engine()->currentMap == 0) {
				map = new SCYSY3Image("Map_Grass.png");
				ReadCheckPoint("CheckPoint0.txt");
				playerCar->orientation_abs = -M_PI / 2;
				playerCar->x_abs = 662;
				playerCar->y_abs = 3006;
				AI1->orientation_abs = playerCar->orientation_abs;
				AI1->x_abs = playerCar->x_abs - 100;
				AI1->y_abs = playerCar->y_abs;
				AI2->orientation_abs = AI1->orientation_abs;
				AI2->x_abs = AI1->x_abs - 200;
				AI2->y_abs = AI1->y_abs - 200;

			}
			else if (getSCYSY3Engine()->currentMap == 1) {
				map = new SCYSY3Image("Map_Snow.png");
				ReadCheckPoint("CheckPoint1.txt");
				playerCar->orientation_abs = -M_PI / 3;
				playerCar->x_abs = 717;
				playerCar->y_abs = 825;
				AI1->orientation_abs = playerCar->orientation_abs;
				AI1->x_abs = playerCar->x_abs - 100;
				AI1->y_abs = playerCar->y_abs;
				AI2->orientation_abs = AI1->orientation_abs;
				AI2->x_abs = AI1->x_abs - 200;
				AI2->y_abs = AI1->y_abs - 200;
			}
			else if (getSCYSY3Engine()->currentMap == 2) {
				map = new SCYSY3Image("Map_Sand.png");
				ReadCheckPoint("CheckPoint2.txt");
				playerCar->orientation_abs = -M_PI / 2;
				playerCar->x_abs = 658;
				playerCar->y_abs = 2541;
				AI1->orientation_abs = playerCar->orientation_abs;
				AI1->x_abs = playerCar->x_abs - 100;
				AI1->y_abs = playerCar->y_abs;
				AI2->orientation_abs = AI1->orientation_abs;
				AI2->x_abs = AI1->x_abs - 200;
				AI2->y_abs = AI1->y_abs - 200;
			}
			mapWidth = map->getWidth();
			mapHeight = map->getHeight();
		}
		else if (getSCYSY3Engine()->GameMode == 1) {
			mapWidth = 6000;
			mapHeight = 6000;
			RoadList = getSCYSY3Engine()->RoadList;
		}
	}
	

	flag = new SCYSY3Image("Flag.png");
	Grass = new SCYSY3Image("Grass.png");
	Snow = new SCYSY3Image("Snow.png");
	TreeSnow = new SCYSY3Image("Tree_Snow.png");
	cactus = new SCYSY3Image("Cactus.png");
	endFlag = new SCYSY3Image("EndFlag.png");
	UD = new SCYSY3Image("Road_up_down.png");
	LR = new SCYSY3Image("Road_left_right.png");
	UL = new SCYSY3Image("Road_up_left.png");
	UR = new SCYSY3Image("Road_up_right.png");
	DL = new SCYSY3Image("Road_down_left.png");
	DR = new SCYSY3Image("Road_down_right.png");
	panel = new SCYSY3Image("panel.png");


	

	try {
		MapColor = new int* [mapHeight];
		MapData = new int* [mapHeight];
	}
	catch (const std::bad_alloc& e) {
		std::cerr << "Memory allocation failed: " << e.what() << "Gaming1.cpp Line91" <<std::endl;
	}
	
	for (int i = 0; i < mapHeight; i++) {
		MapColor[i] = new int[mapWidth];
		MapData[i] = new int[mapWidth];
	}
	
	GenerateBackGround(getSCYSY3Engine()->GameMode, getSCYSY3Engine()->currentTheme, MapColor);
	if (getSCYSY3Engine()->GameMode == 1) {
		playerCar->orientation_abs = M_PI;
		playerCar->x_abs = RoadList[0].x * 400 + 200;
		playerCar->y_abs = RoadList[0].y * 400 + 200;
		AI1->orientation_abs = playerCar->orientation_abs;
		AI1->x_abs = playerCar->x_abs - 100;
		AI1->y_abs = playerCar->y_abs - 100;
		AI2->orientation_abs = AI1->orientation_abs;
		AI2->x_abs = AI1->x_abs - 100;
		AI2->y_abs = AI1->y_abs = 100;
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
	//getSCYSY3Engine()->GameMode = 0;
	//getSCYSY3Engine()->RoadList.clear();
	playerCar->Round = Round;
}
void Gaming1::virtMouseDown(int iButton, int iX, int iY){
	stopButton.virtMouseDown(iButton, iX, iY);
	//continueButton.virtMouseDown(iButton, iX, iY);
	endGame.virtMouseDown(iButton, iX, iY);
	
	if (iButton == SDL_BUTTON_RIGHT) {
		//CheckPoint.emplace_back(
		//	(int)cameraX + i_MouseX - pEngine->getWindowWidth() / 2,
		//	(int)cameraY + i_MouseY - pEngine->getWindowHeight() / 2
		//);
		printf("%d %d\n", (int)cameraX + i_MouseX - pEngine->getWindowWidth() / 2, (int)cameraY + i_MouseY - pEngine->getWindowHeight() / 2);
	}
	else if (iButton == SDL_BUTTON_LEFT) {
		printf("%d %d\n", (int)cameraX + i_MouseX - pEngine->getWindowWidth() / 2, (int)cameraY + i_MouseY - pEngine->getWindowHeight() / 2);
	}
}
void Gaming1::virtMouseWheel(int x, int y, int which, int timestamp) {
	if (y < 0)
		getSCYSY3Engine()->scysy3filterPoints.Rate--;
	else if (y > 0)
		getSCYSY3Engine()->scysy3filterPoints.Rate++;

	if (getSCYSY3Engine()->scysy3filterPoints.Rate < 1) {
		getSCYSY3Engine()->scysy3filterPoints.Rate = 1;
	}
	if (getSCYSY3Engine()->scysy3filterPoints.Rate > 3) {
		getSCYSY3Engine()->scysy3filterPoints.Rate = 3;
	}
	getSCYSY3Engine()->scysy3filterPoints.Move(0, 0);
}
void Gaming1::PreUpdate() {
	SDL_GetMouseState(&i_MouseX, &i_MouseY);
	//static_cast<Gaming1*>(p_BelongState)->CameraLocate(this);
	CameraLocate(playerCar);
	if (pEngine->isKeyPressed(SDLK_UP)) {
		getSCYSY3Engine()->scysy3filterPoints.Move(0,  1);
	}
	if (pEngine->isKeyPressed(SDLK_DOWN)) {
		getSCYSY3Engine()->scysy3filterPoints.Move(0, -1);
	}
	if (pEngine->isKeyPressed(SDLK_LEFT)) {
		getSCYSY3Engine()->scysy3filterPoints.Move(1,  0);
	}
	if (pEngine->isKeyPressed(SDLK_RIGHT)) {
		getSCYSY3Engine()->scysy3filterPoints.Move(-1, 0);
	}

	//CameraLocate(AI1);
}
void Gaming1::DoBeforeUpdate(){
	if (!stopButton.stop) {
		time_Increment = getSCYSY3Engine()->getRawTime() - timeRecord;
		time_FromCreated += time_Increment;
	}
	else {
	}
	timeRecord = getSCYSY3Engine()->getRawTime();
}
void Gaming1::DoAfterUpdate(){

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
void Gaming1::PostUpdate(){}

void Gaming1::virtPreDraw() {
	panel->renderImageWithMask(pState_ForeSurface, 0, 0, 0, pEngine->getWindowHeight()- panel->getHeight() , panel->getWidth(), panel->getHeight(), 0xffffff);
	std::strcpy(speed, std::to_string(static_cast<int>(playerCar->v_velocity.magnitude)).c_str());
	pEngine->drawForegroundString(panel->getWidth()/4, pEngine->getWindowHeight() - (panel->getHeight() / 2), speed, 0xff0000);
	
	renderMap();
	
	if (CheckPoint.size() > 0) {
		//for (int i = 0; i < playerCar->CheckPoint.size(); i++) {
		//	flag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(playerCar->CheckPoint[i].x), playerCar->absYtoWindowY(playerCar->CheckPoint[i].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		//}

		flag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(CheckPoint[playerCar->Next_NO].x), playerCar->absYtoWindowY(CheckPoint[playerCar->Next_NO].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		//flag->renderImageWithMask(pState_ForeSurface, 0, 0, AI1->absXtoWindowX(CheckPoint[AI1->Next_NO].x), AI1->absYtoWindowY(CheckPoint[AI1->Next_NO].y), flag->getWidth(), flag->getHeight(), 0xffffff);
		if (playerCar->CheckPoint.size() >= 1) {
			endFlag->renderImageWithMask(pState_ForeSurface, 0, 0, playerCar->absXtoWindowX(playerCar->CheckPoint[CheckPoint.size() - 1].x), playerCar->absYtoWindowY(playerCar->CheckPoint[CheckPoint.size() - 1].y), endFlag->getWidth(), endFlag->getHeight(), 0xff0000);
		}
	}
	
	
}

void Gaming1::virtPostDraw() {
	
	if (playerCar != nullptr) {

		std::string str = "Round: " + std::to_string(playerCar->RoundCompleted) + " / " + std::to_string(Round);
		const char* cstr = str.c_str();

		char* modifiable_cstr = new char[str.length() + 1];
		strcpy(modifiable_cstr, str.c_str());

		pState_ForeSurface->drawFastString(0, 0, cstr, 0xff0000, nullptr);
		delete[] modifiable_cstr;  

		std::string str2 = "TIME: " + std::to_string((time_FromCreated / 1000) / 60) + " : " + std::to_string((time_FromCreated / 1000) % 60) + " : " + std::to_string((time_FromCreated % 1000)/10);
		const char* cstr2 = str2.c_str();

		char* modifiable_cstr2 = new char[str2.length() + 1];
		strcpy(modifiable_cstr2, str2.c_str());

		pState_ForeSurface->drawFastString(0, 20, cstr2, 0xff0000, nullptr);
		delete[] modifiable_cstr2;
	}
	stopButton.DoOutSideOfContainner();
	//continueButton.DoOutSideOfContainner();
	endGame.DoOutSideOfContainner();
	//playerCar->ShowHitMap();
}


void Gaming1::CameraLocate(SCYSY3DisplayableObject* object) {
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

void Gaming1::renderMap() {
	

	pState_BackSurface->mySDLLockSurface();

	for (int y = 0; y < pEngine->getWindowHeight(); y++) {
		for (int x = 0; x < pEngine->getWindowWidth(); x++) {
			pState_BackSurface->setPixel(x, y, MapColor[(int)cameraY - pEngine->getWindowHeight() / 2 + y][(int)cameraX - pEngine->getWindowWidth() / 2 + x]);
		}
	}
	// 
	//map->renderImage(
	//	pState_BackSurface,
	//	(int)cameraX - pEngine->getWindowWidth() / 2,
	//	(int)cameraY - pEngine->getWindowHeight() / 2,
	//	0, 0
	//	,pEngine->getWindowWidth()
	//	,pEngine->getWindowHeight()
	//);
	//printf("%d %d\n", cameraX, cameraY);
	pState_BackSurface->mySDLUnlockSurface();
}

int Gaming1::GenerateMap() { return 0; }

int Gaming1::GenerateBackGround(int mode, int theme, int** MapColor) {
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
							DrawImageToMap(Grass, x, y);
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
							DrawImageToMap(Snow, x, y);
						}

					}

				}
			}
			for (int y = 0; y < mapHeight; y++) {
				for (int x = 0; x < mapWidth; x++) {
					if ((y % (TreeSnow->getHeight() * 3)) == 0 && (x % (TreeSnow->getWidth() * 3)) == 0) {
						int r = rand();
						if ((r % 10) >= 8) {
							DrawImageToMap(TreeSnow, x, y);
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
							DrawImageToMap(cactus, x, y);
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
						MapColor[y][x] = map->getPixelColour(x, y);
						MapData[y][x] = 1;
					}
				}
			}
		}
		else if(mode == 1){
			DrawCustomRoad();
			for (int i = 0; i < RoadList.size(); i++) {
				CheckPoint.emplace_back(RoadList[i].x * 400 + 200, RoadList[i].y * 400 + 200);
			}
			//getSCYSY3Engine()->GameMode = 0;
		}

	return 0;
}

int Gaming1::DrawStuff() { return 0; }

int Gaming1::DrawCustomRoad() {
	Point Current(startBlock.x, startBlock.y);

	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	int NO = 1;
	int Next = -1;
	do {
		Next = FindNextBlock(Current, NO);
		if (Next == 0) {
			RoadList.emplace_back(Current.x, Current.y - 1);
			Current.y -= 1;
		}
		else if (Next == 1) {
			RoadList.emplace_back(Current.x, Current.y + 1);
			Current.y += 1;
		}
		else if (Next == 2) {
			RoadList.emplace_back(Current.x - 1, Current.y);
			Current.x -= 1;
		}
		else if (Next == 3) {
			RoadList.emplace_back(Current.x + 1, Current.y);
			Current.x += 1;
		}
		NO++;

	} while (Next <= 3 && Next >= 0);


	for (auto it = RoadList.begin(); it != RoadList.end(); ++it) {
		auto prev_it = it != RoadList.begin() ? std::prev(it) : RoadList.end() - 1;
		auto next_it = std::next(it) != RoadList.end() ? std::next(it) : RoadList.begin();

		if (abs(next_it->x - prev_it->x) == 2) {
			left = true;
			right = true;
		}
		else if (abs(next_it->y - prev_it->y) == 2) {
			up = true;
			down = true;
		}

		if (next_it->y + prev_it->y - it->y * 2 == 1) {
			down = true;
		}
		if (next_it->x + prev_it->x - it->x * 2 == 1) {
			right = true;
		}
		if (next_it->y + prev_it->y - it->y * 2 == -1) {
			up = true;
		}
		if ((next_it->x + prev_it->x - it->x * 2 == -1)) {
			left = true;
		}

		if (up) {
			if (left) {
				DrawImageToMap(UL, it->x * BlockSize, it->y * BlockSize);
			}
			else if (right)
			{
				DrawImageToMap(UR, it->x * BlockSize, it->y * BlockSize);
			}
			else if (down) {
				DrawImageToMap(UD, it->x * BlockSize, it->y * BlockSize);
			}
		}
		else if (down) {
			if (left) {
				DrawImageToMap(DL, it->x * BlockSize, it->y * BlockSize);
			}
			else if (right) {
				DrawImageToMap(DR, it->x * BlockSize, it->y * BlockSize);
			}
		}
		else if (left && right) {
			DrawImageToMap(LR, it->x * BlockSize, it->y * BlockSize);
		}
		up = false;
		down = false;
		left = false;
		right = false;
	}

	return 0;
}
int Gaming1::FindNextBlock(Point& current, int NO) {
	if (MapBlock[current.y - 1][current.x] == NO + 1) { //up
		return 0;
	}
	else if (MapBlock[current.y + 1][current.x] == NO + 1) { //down
		return 1;
	}
	else if (MapBlock[current.y][current.x - 1] == NO + 1) { //left
		return 2;
	}
	else if (MapBlock[current.y][current.x + 1] == NO + 1) { //right
		return 3;
	}

	if (MapBlock[current.y - 1][current.x] == 1) { //up
		return 4;
	}
	else if (MapBlock[current.y + 1][current.x] == 1) { //down
		return 5;
	}
	else if (MapBlock[current.y][current.x - 1] == 1) { //left
		return 6;
	}
	else if (MapBlock[current.y][current.x + 1] == 1) { //right
		return 7;
	}
	return -1;
}
void Gaming1::DrawImageToMap(SCYSY3Image* image, int startX, int startY) {
	for (int y = 0; y < image->getHeight(); y++) {
		for (int x = 0; x < image->getWidth(); x++) {
			if ((startX + x >= 0 && startX + x < mapWidth) && (startY + y >= 0 && startY + y < mapHeight)) {
				int color =  image->getPixelColour(x, y);
				if (color != 0xff0000) {
					MapColor[startY + y][startX + x] = color;
					MapData[startY + y][startX + x] = 1;
				}
			}
		}
	}
}

bool Gaming1::ReadCheckPoint(const std::string& filePath) {
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

bool Gaming1::WriteCheckPoint(const std::string& filePath) {
	std::ofstream outfile(filePath);

	if (!outfile.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
	}

	for (const Point& pt : CheckPoint) {
		outfile << pt.x << " " << pt.y << std::endl;
	}

	outfile.close();
	return true;
}

void Gaming1::elasticCollision (PhysicalObject* a, PhysicalObject* b){
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
	printf("hit\n");
}
void Gaming1::Save() {
	std::ofstream fileOut1("save/playCar.txt");
	if (fileOut1.is_open()) {
		fileOut1 << playerCar->x_abs << "\n";
		fileOut1 << playerCar->y_abs << "\n";
		fileOut1 << playerCar->orientation_abs << "\n";
		fileOut1 << playerCar->v_velocity.magnitude << "\n";
		fileOut1 << playerCar->v_velocity.direction << "\n";
		fileOut1 << playerCar->Next_NO << "\n";
		fileOut1 << playerCar->RoundCompleted << "\n";
		fileOut1.close();
	}
	else {
		std::cout << "Unable to open file: save/playCar.txt";
	}
	{
		std::ofstream fileOut2("save/AI1.txt");
		if (fileOut2.is_open()) {
			fileOut2 << AI1->x_abs << "\n";
			fileOut2 << AI1->y_abs << "\n";
			fileOut2 << AI1->orientation_abs << "\n";
			fileOut2 << AI1->v_velocity.magnitude << "\n";
			fileOut2 << AI1->v_velocity.direction << "\n";
			fileOut2 << AI1->Next_NO << "\n";
			fileOut2 << AI1->RoundCompleted << "\n";
			fileOut2.close();
		}
		else {
			std::cout << "Unable to open file: save/AI1.txt";
		}
	}
	{
		std::ofstream fileOut2("save/AI2.txt");
		if (fileOut2.is_open()) {
			fileOut2 << AI2->x_abs << "\n";
			fileOut2 << AI2->y_abs << "\n";
			fileOut2 << AI2->orientation_abs << "\n";
			fileOut2 << AI2->v_velocity.magnitude << "\n";
			fileOut2 << AI2->v_velocity.direction << "\n";
			fileOut2 << AI2->Next_NO << "\n";
			fileOut2 << AI2->RoundCompleted << "\n";
			fileOut2.close();
		}
		else {
			std::cout << "Unable to open file: save/AI2.txt";
		}
	}
	std::ofstream fileOut3("save/CheckPoint.txt");
	if (fileOut3.is_open()) {
		for (const auto& element : CheckPoint) {
			fileOut3 << element.x << " " << element.y << std::endl;
		}
		fileOut3.close();
	}
	else {
		std::cout << "Unable to open file: save/CheckPoint.txt";
	}

	std::ofstream fileOut4("save/MapTheme.txt");
	if (fileOut4.is_open()) {
		fileOut4 << getSCYSY3Engine()->currentMap << std::endl;
		fileOut4 << mapWidth << std::endl;
		fileOut4 << mapHeight << std::endl;
		fileOut4 << time_FromCreated << std::endl;
		fileOut4.close();
	}
	else {
		std::cout << "Unable to open file: save/MapTheme.txt";
	}
}

void Gaming1::Load() {
	{
		std::ifstream fileIn("save/playCar.txt");
		if (fileIn.is_open()) {
			fileIn >> playerCar->x_abs >> playerCar->y_abs >> playerCar->orientation_abs
				>> playerCar->v_velocity.magnitude >> playerCar->v_velocity.direction
				>> playerCar->Next_NO >> playerCar->RoundCompleted;
			fileIn.close();
		}
		else {
			std::cout << "Unable to open file: " << "save/playCar.txt" << std::endl;
		}
	}

	{
		std::ifstream fileIn("save/AI1.txt");
		if (fileIn.is_open()) {
			fileIn >> AI1->x_abs >> AI1->y_abs >> AI1->orientation_abs
				>> AI1->v_velocity.magnitude >> AI1->v_velocity.direction
				>> AI1->Next_NO >> AI1->RoundCompleted;
			fileIn.close();
		}
		else {
			std::cout << "Unable to open file: " << "save/AI1.txt" << std::endl;
		}
	}
	{
		std::ifstream fileIn("save/AI2.txt");
		if (fileIn.is_open()) {
			fileIn >> AI2->x_abs >> AI2->y_abs >> AI2->orientation_abs
				>> AI2->v_velocity.magnitude >> AI2->v_velocity.direction
				>> AI2->Next_NO >> AI2->RoundCompleted;
			fileIn.close();
		}
		else {
			std::cout << "Unable to open file: " << "save/AI2.txt" << std::endl;
		}
	}
	{
		std::ifstream fileIn("save/MapTheme.txt");
		if (fileIn.is_open()) {
			fileIn >> getSCYSY3Engine()->currentMap >> mapWidth >> mapHeight >> time_FromCreated;
			fileIn.close();
			getSCYSY3Engine()->currentTheme = getSCYSY3Engine()->currentMap;
		}
		else {
			std::cout << "Unable to open file: " << "save/MapTheme.txt" << std::endl;
		}
	}

	{
		std::ifstream fileIn("save/CheckPoint.txt");
		if (fileIn.is_open()) {
			int x, y;
			while (fileIn >> x >> y) {
				CheckPoint.emplace_back(x, y);
			}
			fileIn.close();
		}
		else {
			std::cout << "Unable to open file: " << "save/CheckPoint.txt" << std::endl;
		}
	}

	if (getSCYSY3Engine()->currentMap == 0) {
		map = new SCYSY3Image("Map_Grass.png");
	}
	else if (getSCYSY3Engine()->currentMap == 1) {
		map = new SCYSY3Image("Map_Snow.png");
	}
	else if (getSCYSY3Engine()->currentMap == 2) {
		map = new SCYSY3Image("Map_Sand.png");
	}
	getSCYSY3Engine()->ShouldLoad = false;
}

PauseButton::PauseButton(BaseEngine* pEngine, State* belong) :
	SCYSY3Button(0, 0, pEngine, 0, 0, true, belong, NO_Gaming1)
	, StopIcon("Paused.png")
	, NotStopIcon("NotPaused.png")
{
	m_iCurrentScreenX = getEngine()->getWindowWidth() - StopIcon.getWidth() - 10;
	m_iCurrentScreenY = 10;
	m_iDrawWidth = StopIcon.getWidth();
	m_iDrawHeight = StopIcon.getHeight();
}
PauseButton::~PauseButton() {
}

void PauseButton::clickedAndDo() {
	stop = !stop;
	static_cast<Gaming1*>(p_BelongState)->stop = !(static_cast<Gaming1*>(p_BelongState)->stop);
	static_cast<Gaming1*>(p_BelongState)->endGame.canShow = !static_cast<Gaming1*>(p_BelongState)->endGame.canShow;
	return;
}

void PauseButton::DoOutSideOfContainner() {
	if (!stop) {
		NotStopIcon.renderImage(p_BelongState->pState_ForeSurface, 0, 0, getEngine()->getWindowWidth() - StopIcon.getWidth() - 10, 10, StopIcon.getWidth(), StopIcon.getHeight());
		static_cast<Gaming1*>(p_BelongState)->playerCar->paused = false;
	}
	else {
		StopIcon.renderImage(p_BelongState->pState_ForeSurface, 0, 0, getEngine()->getWindowWidth() - StopIcon.getWidth() - 10, 10, NotStopIcon.getWidth(), NotStopIcon.getHeight());
		static_cast<Gaming1*>(p_BelongState)->playerCar->paused = true;
	}

	return;
}

Continue::Continue(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = -1;
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = pEngine->getWindowWidth() / 2 - m_iDrawWidth / 2;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 + 100;
}

EndGame::EndGame(BaseEngine* pEngine, State* belong) :
	NEWGAME(pEngine, belong)
{
	link = NO_Menu;
	m_iDrawWidth = 300;
	m_iDrawHeight = 50;
	m_iCurrentScreenX = pEngine->getWindowWidth() / 2 - m_iDrawWidth / 2;
	m_iCurrentScreenY = pEngine->getWindowHeight() / 2 - m_iDrawHeight / 2 ;
}


