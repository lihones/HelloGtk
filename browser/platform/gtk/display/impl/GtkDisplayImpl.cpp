#include "GtkDisplayImpl.h"
#include <iostream>
#include "GtkEventImpl.h"

namespace pt {

using namespace std;

GtkDisplayImpl::GtkDisplayImpl()
{}

GtkDisplayImpl::~GtkDisplayImpl()
{}

bool GtkDisplayImpl::connect()
{
	mNativeDisplay = XOpenDisplay(NULL);
	return (mNativeDisplay != NULL);
}

void GtkDisplayImpl::nextEvent(EventImpl *ev)
{
	XEvent *nev = ((GtkEventImpl*)ev)->getNativeEvent();
	XNextEvent(mNativeDisplay, nev);
}

void GtkDisplayImpl::close()
{
	XCloseDisplay(mNativeDisplay);
}

Display* GtkDisplayImpl::getNativeDisplay()
{
	return mNativeDisplay;
}

}
