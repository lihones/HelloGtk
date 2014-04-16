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

void AfGtkNative::gtkSample()
{
	connect();

	int x = 0, y = 0, width = 500, height = 500;
	Window window = XCreateSimpleWindow(mDisplay,
				RootWindow(mDisplay, mDefaultScreen),
				x,
				y,
				width,
				height,
				0,
				BlackPixel(mDisplay, mDefaultScreen),
				WhitePixel(mDisplay, mDefaultScreen));

	/* select kind of events we are interested in */
	XSelectInput(mDisplay, window, ExposureMask | KeyPressMask | StructureNotifyMask);

	/* map (show) the window */
	XMapWindow(mDisplay, window);

	const char *msg = "hello";


	XEvent event;

	while(1) {
		XNextEvent(mDisplay, &event);

		if(event.type == Expose) {
			XDrawString(mDisplay,
					window,
					DefaultGC(mDisplay, mDefaultScreen),
					15,
					15,
					msg,
					strlen(msg));
		}

		if(event.type == DestroyNotify) {
			break;
		}
	}

	disconnect();
}

}
