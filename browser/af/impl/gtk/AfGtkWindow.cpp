#include <iostream>
#include <string.h>
#include "AfGtkWindow.h"
#include "AfGtkNative.h"

namespace af {

AfGtkWindow::AfGtkWindow()
{
	mNative = NULL;
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mNativeWindow = 0;
}

AfGtkWindow::AfGtkWindow(AfGtkNative *native)
{
	mNative = native;

	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mNativeWindow = 0;
}

AfGtkWindow::~AfGtkWindow()
{
}

void AfGtkWindow::setRect(int x, int y, int width, int height)
{
	mX = x;
	mY = y;
	mWidth = width;
	mHeight = height;

	Display *display = mNative->display();
	int screen = mNative->defaultScreen();
	mNativeWindow = XCreateSimpleWindow(display,
				RootWindow(display, screen),
				x,
				y,
				width,
				height,
				0,
				BlackPixel(display, screen),
				WhitePixel(display, screen));
}

int AfGtkWindow::map()
{
	Display *display = mNative->display();
	int screen = mNative->defaultScreen();

	/* select kind of events we are interested in */
	XSelectInput(display, mNativeWindow, ExposureMask | KeyPressMask | StructureNotifyMask);

	/* map (show) the window */
	int ret = XMapWindow(display, mNativeWindow);

	const char *msg = "hello, gtk";

	XEvent event;

	while(1) {
		XNextEvent(display, &event);

		if(event.type == Expose) {
			XDrawString(display,
					mNativeWindow,
					DefaultGC(display, screen),
					15,
					15,
					msg,
					strlen(msg));
		}

		if(event.type == DestroyNotify) {
			break;
		}
	}

	return ret;
}

int AfGtkWindow::unmap()
{
	Display *display = mNative->display();

	int ret = XUnmapWindow(display, mNativeWindow);

	return ret;
}

}
