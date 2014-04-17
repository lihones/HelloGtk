#include <iostream>
#include <string.h>
#include "AfGtkWindow.h"
#include "AfGtkNative.h"
#include "AfGc.h"
#include "AfGtkGc.h"

namespace af {

AfGtkWindow::AfGtkWindow()
{
	mNative = NULL;
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mNativeWindow = 0;
	mGc = NULL;
}

AfGtkWindow::AfGtkWindow(AfGtkNative *native)
{
	mNative = native;

	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mNativeWindow = 0;
	mGc = NULL;
}

AfGtkWindow::~AfGtkWindow()
{
	if(mGc != NULL) {
		delete mGc;
		mGc = NULL;
	}
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

int AfGtkWindow::x()
{
	return mX;
}

int AfGtkWindow::y()
{
	return mY;
}

int AfGtkWindow::width()
{
	return mWidth;
}

int AfGtkWindow::height()
{
	return mHeight;
}

AfGtkNative* AfGtkWindow::native()
{
	return mNative;
}

Window AfGtkWindow::nativeWindow()
{
	return mNativeWindow;
}

int AfGtkWindow::map()
{
	Display *display = mNative->display();

	/* select kind of events we are interested in */
	XSelectInput(display, mNativeWindow, ExposureMask | KeyPressMask | StructureNotifyMask);

	/* map (show) the window */
	int ret = XMapWindow(display, mNativeWindow);

	XEvent event;

	while(1) {
		XNextEvent(display, &event);

		if(event.type == Expose) {
			AfGc *gca = gc();
			gca->draw();
//			XDrawString(display,
//					mNativeWindow,
//					DefaultGC(display, screen),
//					15,
//					15,
//					msg,
//					strlen(msg));
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

AfGc* AfGtkWindow::gc()
{
	if(mGc == NULL) {
		mGc = new AfGtkGc(this);
	}
	return mGc;
}

}
