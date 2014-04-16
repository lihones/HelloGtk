#include "AfGtkNative.h"
#include <iostream>
#include <string.h>

namespace af {

AfGtkNative* AfGtkNative::mInstance = NULL;

AfGtkNative* AfGtkNative::instance()
{
	if(mInstance == NULL) {
		mInstance = new AfGtkNative();
	}
	return mInstance;
}

void AfGtkNative::release()
{
	if(mInstance != NULL) {
		delete mInstance;
		mInstance = NULL;
	}
}

AfGtkNative::AfGtkNative()
{
	mDisplay = NULL;
	mDefaultScreen = 0;
}

AfGtkNative::~AfGtkNative()
{
}

int AfGtkNative::connect()
{
	mDisplay = XOpenDisplay(NULL);
	mDefaultScreen = DefaultScreen(mDisplay);
	return 0;
}

int AfGtkNative::disconnect()
{
	int ret;
	ret = XCloseDisplay(mDisplay);
	return ret;
}

Display* AfGtkNative::display()
{
	return mDisplay;
}

int AfGtkNative::defaultScreen()
{
	return mDefaultScreen;
}

}
