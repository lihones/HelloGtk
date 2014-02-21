#include "GtkWindowImpl.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GtkDisplayImpl.h"
#include "GtkEventImpl.h"
#include "browser/display/PtEvent.h"

namespace pt {

using namespace std;

GtkWindowImpl::GtkWindowImpl()
{}

GtkWindowImpl::~GtkWindowImpl()
{}

void GtkWindowImpl::setLocation(int x, int y)
{
	mX = x;
	mY = y;
}

void GtkWindowImpl::setSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void GtkWindowImpl::move(int x, int y)
{
	mX += x;
	mY += y;
}

void GtkWindowImpl::resize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void GtkWindowImpl::moveAndResize(int x, int y, int width, int height)
{
	mX += x;
	mY += y;
	mWidth = width;
	mHeight = height;
}

void GtkWindowImpl::attach(DisplayImpl *display)
{
	mNativeDisplay = ((GtkDisplayImpl*)display)->getNativeDisplay();
	mNativeScreen = DefaultScreen(mNativeDisplay);
}

void GtkWindowImpl::makeup()
{
	mNativeWindow = XCreateSimpleWindow(mNativeDisplay,
			RootWindow(mNativeDisplay, mNativeScreen),
			mX,
			mY,
			mWidth,
			mHeight,
			0,
			BlackPixel(mNativeDisplay, mNativeScreen),
			WhitePixel(mNativeDisplay, mNativeScreen));

	/* select kind of events we are interested in */
	XSelectInput(mNativeDisplay, mNativeWindow, ExposureMask | KeyPressMask | StructureNotifyMask);

	/* map (show) the window */
	XMapWindow(mNativeDisplay, mNativeWindow);
}

GcImpl* GtkWindowImpl::gc()
{
	return NULL;
}

void GtkWindowImpl::draw()
{
	const char *msg = "hello";
	XDrawString(mNativeDisplay,
			mNativeWindow,
			DefaultGC(mNativeDisplay, mNativeScreen),
			5,
			5,
			msg,
			strlen(msg));
}

bool GtkWindowImpl::handleEvent(EventImpl *event)
{
	XEvent *nev = ((GtkEventImpl*)event)->getNativeEvent();
	if(nev->type == Expose) {
		draw();
	}

	switch (nev->type) {
	case KeyPress:
		break;

	case DestroyNotify:
		nev->type = PtEvent::TYPE_CLOSE;
		break;

	case ClientMessage:
		break;
	}
	return true;
}

}
