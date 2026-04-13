#include "header.h"
#include "SCYSY3FilterPoints.h"

SCYSY3FilterPoints::SCYSY3FilterPoints(BaseEngine* pEngine, FilterPoints* pNextFilter = nullptr)
	: pNextFilter(pNextFilter)
	, m_pEngine(pEngine)
{
	
}

bool SCYSY3FilterPoints::filter(DrawingSurface* surface, int& x, int& y, unsigned int& uiColour, bool setting) {
	x += offset_X;
	y += offset_Y;
	if (x < Min_X[Rate] || x > Max_X[Rate] || y < Min_Y[Rate] || y > Max_Y[Rate]) {
		return false;
	}
	for (int fromy = Window_Height/2 - Window_Height* Rate/2 + y * Rate; fromy < Window_Height / 2 - Window_Height * Rate / 2 + y * Rate + Rate; fromy++) {
		for (int fromx = Window_Width / 2 - Window_Width * Rate / 2 + x * Rate; fromx < Window_Width / 2 - Window_Width * Rate / 2 + x * Rate + Rate; fromx++) {
			surface->rawSetPixel(fromx, fromy, uiColour);
		}
	}
	//return pNextFilter->filter(surface, x, y, uiColour, setting);
	return false;
}



int  SCYSY3FilterPoints:: filterConvertRealToVirtualXPosition(int x) { 
	return x / Rate + Window_Width / 2 - Window_Width / (2 * Rate) + offset_X;
	//return x;
}
	

int  SCYSY3FilterPoints::filterConvertRealToVirtualYPosition(int y) { 
	return y / Rate + Window_Height / 2 - Window_Height / (2 * Rate) + offset_Y;
	//return y;
}


int  SCYSY3FilterPoints:: filterConvertVirtualToRealXPosition(int x) { return x; }

int  SCYSY3FilterPoints:: filterConvertVirtualToRealYPosition(int y) { return y; }
void SCYSY3FilterPoints:: Initialize() {
	Window_Width = m_pEngine->getWindowWidth();
	Window_Height = m_pEngine->getWindowHeight();
	for (int i = 1; i < 4; i++) {
		Min_X[i] = (Window_Width * i - Window_Width) / (2 * i);
		Min_Y[i] = (Window_Height * i - Window_Height) / (2 * i);
		Max_X[i] = (Window_Width * i + Window_Width) / (2 * i) - 1;
		Max_Y[i] = (Window_Height * i + Window_Height) / (2 * i) - 1;
	}
}

void SCYSY3FilterPoints::Move(int moveX, int moveY) {
	if (Min_X[Rate] - (offset_X + moveX)  <= 0) {
		offset_X = Min_X[Rate]-1;
	}
	else {
		offset_X += moveX;
	}

	if (Min_Y[Rate] - (offset_Y + moveY) <= 0) {
		offset_Y = Min_Y[Rate]-1;
	}
	else {
		offset_Y += moveY;
	}

	if (Max_X[Rate] - (offset_X + moveX)  >= Window_Width) {
		offset_X = -(Window_Width - 1 - Max_X[Rate] );
	}
	else {
		offset_X += moveX;
	}

	if (Max_Y[Rate] - (offset_Y + moveY)  >= Window_Height) {
		offset_Y = -(Window_Height - 1 - Max_Y[Rate] );
	}
	else {
		offset_Y += moveY;
	}
}