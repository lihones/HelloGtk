#include <iostream>
#include "AfGtkContext.h"
#include "AfGtkNative.h"
#include "AfWindow.h"
#include "AfProxy.h"
#include "AfGtkWindow.h"

namespace af {

AfGtkContext::AfGtkContext()
{
	mNative = AfGtkNative::instance();
	mNative->connect();
	mWindow = NULL;
}

AfGtkContext::~AfGtkContext()
{
}

AfWindow* AfGtkContext::createWindow(int x, int y, int width, int height)
{
	mWindow = new AfGtkWindow(mNative);
	mWindow->setRect(x, y, width, height);
	return mWindow;
}

AfProxy* AfGtkContext::proxy()
{
	return mNative;
}

}
