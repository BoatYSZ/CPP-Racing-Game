#include "header.h"

#include "ImageManager.h"
#include "DrawingSurface.h"
#include "BaseEngine.h"
#include "SCYSY3Image.h"
#include "ImagePixelMapping.h"
#include "SCYSY3DisplayableObject.h"
#include "Gaming1.h"
static CroppedImagePixelMapping nullMapping;

SCYSY3Image::SCYSY3Image():
	SimpleImage() {
}

SCYSY3Image::SCYSY3Image(std::string strURL):
	SimpleImage::SimpleImage(ImageManager::get()->getImagebyURL(strURL, true/*Load*/, false/*Keep it loaded*/)) 
{
}

SCYSY3Image::~SCYSY3Image() {
	//SimpleImage::~SimpleImage();
	if (m_mapping != nullptr) {
		delete(m_mapping);
		m_mapping = nullptr;
	}
}

void SCYSY3Image::renderImageApplyingMapping(BaseEngine* pEngine, DrawingSurface* pTarget,
	int iXDrawLocation, int iYDrawLocation, int iWidth, int iHeight,
	ImagePixelMapping* mapping) const
{
	if (mapping == nullptr)
		mapping = &nullMapping;

	int xStart = iXDrawLocation;
	int yStart = iYDrawLocation;
	int xMinOffset = 0;
	int xMaxOffset = iWidth;
	int yMinOffset = 0;
	int yMaxOffset = iHeight;

	int iLHS = pEngine->convertClickedToVirtualPixelXPosition(0);
	int iTop = pEngine->convertClickedToVirtualPixelYPosition(0);
	int iRHS = pEngine->convertClickedToVirtualPixelXPosition(pEngine->getWindowWidth());
	int iBottom = pEngine->convertClickedToVirtualPixelYPosition(pEngine->getWindowHeight());

	if (!pEngine->getRedrawAllScreen())
	{
		if ((xStart + iWidth < pEngine->getRedrawRectVirtualLeft())
			|| (xStart > pEngine->getRedrawRectVirtualRight())
			|| (yStart + iHeight < pEngine->getRedrawRectVirtualTop())
			|| (yStart > pEngine->getRedrawRectVirtualBottom()))
		{
			//std::cout << "Ignore piece outside redraw region" << std::endl;
			return;
		}
	}
	else
	{
		if ((xStart > iRHS)
			|| (xStart + iWidth < iLHS)
			|| (yStart > iBottom)
			|| (yStart + iHeight < iTop))
		{
			//std::cout << "Ignore piece off screen" << std::endl;
			return;
		}
	}

	if (xStart + xMinOffset < iLHS)
		xMinOffset = iLHS - xStart;
	//	if (yStart + yMinOffset + iWidth < iTop)
	//        xMinOffset = iLHS - xStart;
	if (yStart + yMinOffset < iTop)
		yMinOffset = iTop - yStart;

	if (xStart + xMaxOffset > iRHS)
		xMaxOffset = iRHS - xStart;
	if (yStart + yMaxOffset > iBottom)
		yMaxOffset = iBottom - yStart;

	// Note: this method can also handle partial redraw of screen, by reducing the size of the draw area:
	if (!pEngine->getRedrawAllScreen())
	{
		/*
		if ((xStart + xMaxOffset < pEngine->getRedrawRectVirtualLeft())
		|| (xStart + xMinOffset > pEngine->getRedrawRectVirtualRight())
		|| (yStart + yMaxOffset < pEngine->getRedrawRectVirtualTop())
		|| (yStart + yMinOffset > pEngine->getRedrawRectVirtualBottom()))
		{
		std::cout << "Ignore piece off display" << std::endl;
		return;
		}
		*/

		//std::cout << "Rect x  " << pEngine->getRedrawRectVirtualLeft()
		//	<< " to " << pEngine->getRedrawRectVirtualRight()
		//	<< " y " << pEngine->getRedrawRectVirtualTop()
		//	<< " to " << pEngine->getRedrawRectVirtualBottom() << std::endl;

		// Not redrawing entire screen...
		int iRedrawPos = pEngine->getRedrawRectVirtualLeft();
		if (iRedrawPos > xStart + xMinOffset)
			xMinOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualTop();
		if (iRedrawPos > yStart + yMinOffset)
			yMinOffset = iRedrawPos - yStart;
		iRedrawPos = pEngine->getRedrawRectVirtualRight();
		if (iRedrawPos < xStart + xMaxOffset)
			xMaxOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualBottom();
		if (iRedrawPos < yStart + yMaxOffset)
			yMaxOffset = iRedrawPos - yStart;
	}

	// Check for not visible
	if (xMaxOffset <= xMinOffset)
	{
		//std::cout << "Image not in x visible area" << std::endl;
		return;
	}
	if (yMaxOffset <= yMinOffset)
		return;

	double dx, dy;
	int iPixel;
	double radius = std::sqrt(iWidth * iWidth + iHeight * iHeight) / 2 + 1;
	double centerX = (xMinOffset + xMaxOffset) / 2;
	double centerY = (yMinOffset + yMaxOffset) / 2;
	int fromX = (int)(centerX - radius) - 1;
	int fromY = (int)(centerY - radius) - 1;
	int endX = (int)(centerX + radius) + 1;
	int endY = (int)(centerY + radius) + 1;
	//std::cout << "Draw from " << xMinOffset << " to " << xMaxOffset << std::endl;
	for (int iYOffset = fromY; iYOffset <= endY; ++iYOffset)
	{
		for (int iXOffset = fromX; iXOffset <= endX; ++iXOffset)
		{
			dx = iXOffset;
			dy = iYOffset;
			if (mapping->mapCoordinates(dx, dy, *this))
			{ // It mapcoordinates returns false, do not draw the pixel
				int iColour = 0xffffff & theData->getRawPixelColour((int)(dx + 0.5), (int)(dy + 0.5));
				if (mapping->changePixelColour(iXDrawLocation + iXOffset, iYDrawLocation + iYOffset, iColour, pTarget))//
				{ // If changePixelColour returns false it means we should not draw the pixel
					pTarget->setPixel((iXDrawLocation + iXOffset + 0.5), (iYDrawLocation + iYOffset + 0.5), iColour);
				}
			}
		}
	}
}

void SCYSY3Image::renderImageApplyingMapping(
	BaseEngine* pEngine, DrawingSurface* pTarget
	, double X, double Y
	, ImagePixelMapping* mapping
) const 
{
	if (mapping == nullptr)
		mapping = &nullMapping;

	int xStart = (int)(X);
	int yStart = (int)(Y);
	int xMinOffset = 0;
	int xMaxOffset = this-> getWidth();
	int yMinOffset = 0;
	int yMaxOffset = this-> getHeight();

	int iLHS = pEngine->convertClickedToVirtualPixelXPosition(0);
	int iTop = pEngine->convertClickedToVirtualPixelYPosition(0);
	int iRHS = pEngine->convertClickedToVirtualPixelXPosition(pEngine->getWindowWidth());
	int iBottom = pEngine->convertClickedToVirtualPixelYPosition(pEngine->getWindowHeight());

	if (!pEngine->getRedrawAllScreen())
	{
		if ((xStart + this->getWidth() < pEngine->getRedrawRectVirtualLeft())
			|| (xStart > pEngine->getRedrawRectVirtualRight())
			|| (yStart + this->getHeight() < pEngine->getRedrawRectVirtualTop())
			|| (yStart > pEngine->getRedrawRectVirtualBottom()))
		{
			//std::cout << "Ignore piece outside redraw region" << std::endl;
			return;
		}
	}
	else
	{
		if ((xStart > iRHS)
			|| (xStart + this->getWidth() < iLHS)
			|| (yStart > iBottom)
			|| (yStart + this->getHeight() < iTop))
		{
			//std::cout << "Ignore piece off screen" << std::endl;
			return;
		}
	}

	if (xStart + xMinOffset < iLHS)
		xMinOffset = iLHS - xStart;
	//	if (yStart + yMinOffset + iWidth < iTop)
	//        xMinOffset = iLHS - xStart;
	if (yStart + yMinOffset < iTop)
		yMinOffset = iTop - yStart;

	if (xStart + xMaxOffset > iRHS)
		xMaxOffset = iRHS - xStart;
	if (yStart + yMaxOffset > iBottom)
		yMaxOffset = iBottom - yStart;

	// Note: this method can also handle partial redraw of screen, by reducing the size of the draw area:
	if (!pEngine->getRedrawAllScreen())
	{
		/*
		if ((xStart + xMaxOffset < pEngine->getRedrawRectVirtualLeft())
		|| (xStart + xMinOffset > pEngine->getRedrawRectVirtualRight())
		|| (yStart + yMaxOffset < pEngine->getRedrawRectVirtualTop())
		|| (yStart + yMinOffset > pEngine->getRedrawRectVirtualBottom()))
		{
		std::cout << "Ignore piece off display" << std::endl;
		return;
		}
		*/

		//std::cout << "Rect x  " << pEngine->getRedrawRectVirtualLeft()
		//	<< " to " << pEngine->getRedrawRectVirtualRight()
		//	<< " y " << pEngine->getRedrawRectVirtualTop()
		//	<< " to " << pEngine->getRedrawRectVirtualBottom() << std::endl;

		// Not redrawing entire screen...
		int iRedrawPos = pEngine->getRedrawRectVirtualLeft();
		if (iRedrawPos > xStart + xMinOffset)
			xMinOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualTop();
		if (iRedrawPos > yStart + yMinOffset)
			yMinOffset = iRedrawPos - yStart;
		iRedrawPos = pEngine->getRedrawRectVirtualRight();
		if (iRedrawPos < xStart + xMaxOffset)
			xMaxOffset = iRedrawPos - xStart;
		iRedrawPos = pEngine->getRedrawRectVirtualBottom();
		if (iRedrawPos < yStart + yMaxOffset)
			yMaxOffset = iRedrawPos - yStart;
	}

	// Check for not visible
	if (xMaxOffset <= xMinOffset)
	{
		//std::cout << "Image not in x visible area" << std::endl;
		return;
	}
	if (yMaxOffset <= yMinOffset)
		return;

	double dx, dy;
	int iPixel;
	double radius = std::sqrt(this->getWidth() * this->getWidth() + this->getHeight() * this->getHeight()) / 2;
	double centerX = (xMinOffset + xMaxOffset) / 2;
	double centerY = (yMinOffset + yMaxOffset) / 2;
	int fromX = (int)(centerX - radius) - 1;
	int fromY = (int)(centerY - radius) - 1;
	int endX = (int)(centerX + radius) + 1;
	int endY = (int)(centerY + radius) + 1;
	//std::cout << "Draw from " << xMinOffset << " to " << xMaxOffset << std::endl;
	for (int iYOffset = fromY; iYOffset <= endY; ++iYOffset)
	{
		for (int iXOffset = fromX; iXOffset <= endX; ++iXOffset)
		{
			dx = iXOffset;
			dy = iYOffset;
			if (mapping->mapCoordinates(dx, dy, *this))
			{ // It mapcoordinates returns false, do not draw the pixel
				int iColour = 0xffffff & theData->getRawPixelColour((int)(dx + 0.5), (int)(dy + 0.5));
				if (iColour != m_iTransparencyColour)//mapping->changePixelColour(this->x_rela + iXOffset, this->y_rela + iYOffset, iColour, pTarget)
				{ // If changePixelColour returns false it means we should not draw the pixel
					pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + + iYOffset + 0.5), iColour);
				}
			}
		}
	}

}

void SCYSY3Image::renderImageApplyingMappingAndHitPixel(
	BaseEngine* pEngine, DrawingSurface* pTarget
	, double X, double Y
	, ImagePixelMapping* mapping
	, SCYSY3DisplayableObject* object
) const
{
	if (mapping == nullptr)
		mapping = &nullMapping;

	int xStart = (int)(X);
	int yStart = (int)(Y);
	int xMinOffset = 0;
	int xMaxOffset = this->getWidth();
	int yMinOffset = 0;
	int yMaxOffset = this->getHeight();

	double dx, dy;
	int iPixel;
	double radius = std::sqrt(this->getWidth() * this->getWidth() + this->getHeight() * this->getHeight()) / 2;
	double centerX = (xMinOffset + this->getWidth()) / 2;
	double centerY = (yMinOffset + this->getHeight()) / 2;
	int fromX = (int)(centerX - radius) - 1;
	int fromY = (int)(centerY - radius) - 1;
	int endX = (int)(centerX + radius) + 1;
	int endY = (int)(centerY + radius) + 1;

	Gaming1* pState = static_cast<Gaming1*>(object->p_BelongState);
	for (int iYOffset = fromY; iYOffset <= endY; ++iYOffset)
	{
		for (int iXOffset = fromX; iXOffset <= endX; ++iXOffset)
		{
			dx = iXOffset;
			dy = iYOffset;
			if (mapping->mapCoordinates(dx, dy, *this))
			{
				int iColour = 0xffffff & theData->getRawPixelColour((int)(dx + 0.5), (int)(dy + 0.5));
				if (iColour != m_iTransparencyColour)
				{ 
					pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + +iYOffset + 0.5), iColour);
					if (object->HitMap != nullptr) {
						if (theData->getRawPixelColour((int)(dx + 1.5), (int)(dy + 0.5)) == m_iTransparencyColour) {
							object->HitPixel.emplace_back(iXOffset - centerX , iYOffset - centerY);
							//object->HitPixel[object->HitMap_Size / 2 + iXOffset][object->HitMap_Size / 2 + iYOffset]
							//pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + +iYOffset + 0.5), 0xffff00);
						}
						else if (theData->getRawPixelColour((int)(dx - 0.5), (int)(dy + 0.5)) == m_iTransparencyColour) {
							object->HitPixel.emplace_back(iXOffset - centerX, iYOffset - centerY);
							//pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + +iYOffset + 0.5), 0xffff00);
						}
						else if (theData->getRawPixelColour((int)(dx + 0.5), (int)(dy + 1.5)) == m_iTransparencyColour) {
							object->HitPixel.emplace_back(iXOffset - centerX, iYOffset - centerY);
							//pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + +iYOffset + 0.5), 0xffff00);
						}
						else if (theData->getRawPixelColour((int)(dx + 0.5), (int)(dy - 0.5)) == m_iTransparencyColour) {
							object->HitPixel.emplace_back(iXOffset - centerX, iYOffset - centerY);
							//pTarget->setPixel((X - centerX + iXOffset + 0.5), (Y - centerY + +iYOffset + 0.5), 0xffff00);
						}
					}
				}
			}
		}
	}

}


void SCYSY3Image::renderImageWithMaskAndTransparency(DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight,
	int iMaskColour, int opacityPercentage) const
{
	//if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight))
	//	return; // No need - off the screen

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++)
	{
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++)
		{
			int iPixel = theData->getRawPixelColour(iXS, iYS);
			if (iPixel != iMaskColour)
			{
				int iBackground = pTarget->rawGetPixel(iXT, iYT);
				int iR = (0xff & (iPixel >> 16)) * opacityPercentage + (0xff & (iBackground >> 16)) * (100 - opacityPercentage);
				int iG = (0xff & (iPixel >> 8)) * opacityPercentage + (0xff & (iBackground >> 8)) * (100 - opacityPercentage);
				int iB = (0xff & iPixel) * opacityPercentage + (0xff & iBackground) * (100 - opacityPercentage);
				//std::cout << "R " << iR << " G " << iG << " B " << iB << std::endl;
				//std::cout << "R " << (iR / 100) << " G " << (iG / 100) << " B " << (iB / 100) << std::endl;
				pTarget->setPixel(iXT, iYT, (((iR / 100) & 0xff) << 16) | (((iG / 100) & 0xff) << 8) | ((iB / 100) & 0xff));
			}
			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}
}

void SCYSY3Image::renderImageWithMaskAndReplace(DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight,
	int iMaskColor, int iReplaceColor) const
{
	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight))
		return; // No need - off the screen

	if (iMaskColor == -1)
	{ // Assumes that the bottom right pixel is the transparency colour if you do not provide one.
		iMaskColor = theData->getRawPixelColour(theData->getWidth() - 1, theData->getHeight() - 1);
	}

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++)
	{
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++)
		{
			int iPixel = theData->getRawPixelColour(iXS, iYS);
			if (iPixel != iMaskColor)
				pTarget->setPixel(iXT, iYT, iReplaceColor);
			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}
}

void SCYSY3Image::renderImageWithMaskAndTransparencyAndReplace(DrawingSurface* pTarget,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight,
	int iMaskColour, int iReplaceColour,int opacityPercentage) const
{
	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight))
		return; // No need - off the screen

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++)
	{
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++)
		{
			int iPixel = theData->getRawPixelColour(iXS, iYS);
			if (iPixel != iMaskColour)
			{
				iPixel = iReplaceColour;
				int iBackground = pTarget->rawGetPixel(iXT, iYT);
				int iR = (0xff & (iPixel >> 16)) * opacityPercentage + (0xff & (iBackground >> 16)) * (100 - opacityPercentage);
				int iG = (0xff & (iPixel >> 8)) * opacityPercentage + (0xff & (iBackground >> 8)) * (100 - opacityPercentage);
				int iB = (0xff & iPixel) * opacityPercentage + (0xff & iBackground) * (100 - opacityPercentage);
				//std::cout << "R " << iR << " G " << iG << " B " << iB << std::endl;
				//std::cout << "R " << (iR / 100) << " G " << (iG / 100) << " B " << (iB / 100) << std::endl;
				pTarget->setPixel(iXT, iYT, (((iR / 100) & 0xff) << 16) | (((iG / 100) & 0xff) << 8) | ((iB / 100) & 0xff));
			}
			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}
}

void SCYSY3Image::renderImageWithMaskAndReplace2(DrawingSurface* pTarget, DrawingSurface* pSource,
	int iXSource, int iYSource,
	int iXTarget, int iYTarget,
	int iWidth, int iHeight,
	int iMaskColor) const
{
	if (!adjustXYWidthHeight(pTarget, iXSource, iYSource, iXTarget, iYTarget, iWidth, iHeight))
		return; // No need - off the screen

	if (iMaskColor == -1)
	{ // Assumes that the bottom right pixel is the transparency colour if you do not provide one.
		iMaskColor = theData->getRawPixelColour(theData->getWidth() - 1, theData->getHeight() - 1);
	}

	int iXS, iYS = iYSource, iXT, iYT = iYTarget;

	for (int iYOffset = 0; iYOffset < iHeight; iYOffset++)
	{
		iXS = iXSource;
		iXT = iXTarget;
		for (int iXOffset = 0; iXOffset < iWidth; iXOffset++)
		{
			int iPixel = theData->getRawPixelColour(iXS, iYS);
			if (iPixel != iMaskColor) {
				int sample = pSource->rawGetPixel(iXT, iYT) & 0x00FFFFFF;
				if (sample == 0x377D22) {
					pTarget->setPixel(iXT, iYT, 0x000000);
				}
				else {
					pTarget->setPixel(iXT, iYT, 0xFFFFFF);
				}
			}
			iXS++;
			iXT++;
		}
		iYS++;
		iYT++;
	}
}