#include "WaterSurface.h"

CWaterSurface::CWaterSurface(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l;
	height = b - t;
}

void CWaterSurface::Render()
{
	RenderBoundingBox();
}

void CWaterSurface::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}