#include "PtBitmap.h"
#include <iostream>

namespace pt {

using namespace std;

PtBitmap::PtBitmap(int width, int height, int format)
{}

PtBitmap::~PtBitmap()
{}

int PtBitmap::getWidth()
{
	return 0;
}

int PtBitmap::getHeight()
{
	return 0;
}

PtGc* PtBitmap::gc()
{
	return NULL;
}

BitmapImpl* PtBitmap::impl()
{
	return mImpl;
}

}
