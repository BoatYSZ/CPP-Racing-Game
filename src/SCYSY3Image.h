#pragma once
#include "header.h"
#include "SimpleImage.h"
#include "ImagePixelMapping.h"
class SCYSY3DisplayableObject;

class SCYSY3Image :
    public SimpleImage
{
public:
	SCYSY3Image();
	SCYSY3Image(std::string strURL);
	~SCYSY3Image();

	void renderImageApplyingMapping(
		BaseEngine* pEngine
		, DrawingSurface* pTarget
		, int iXDrawLocation
		, int iYDrawLocation
		, int iWidth
		, int iHeight
		, ImagePixelMapping* mapping
	) const;

	void renderImageApplyingMapping(
		  BaseEngine* pEngine
		, DrawingSurface* pTarget
		, double X
		, double Y
		, ImagePixelMapping* mapping
	) const;

	void SCYSY3Image::renderImageApplyingMappingAndHitPixel(
		BaseEngine* pEngine, DrawingSurface* pTarget
		, double X, double Y
		, ImagePixelMapping* mapping
		, SCYSY3DisplayableObject* object
	) const;

	void SCYSY3Image::renderImageWithMaskAndTransparency(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight,
		int iMaskColour, int opacityPercentage) const;

	void SCYSY3Image::renderImageWithMaskAndTransparencyAndReplace(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight,
		int iMaskColour, int iReplaceColourint, int opacityPercentage) const;

	void SCYSY3Image::renderImageWithMaskAndReplace(DrawingSurface* pTarget,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight,
		int iMaskColor, int iReplaceColor) const;

	void SCYSY3Image::renderImageWithMaskAndReplace2(DrawingSurface* pTarget, DrawingSurface* pSource,
		int iXSource, int iYSource,
		int iXTarget, int iYTarget,
		int iWidth, int iHeight,
		int iMaskColor) const;

	ImagePixelMapping* m_mapping = nullptr;

	double x_abs;
	double y_abs;
	double orientation_abs;

	double y_rela;
	double x_rela;
	double orientation_rela;
};

