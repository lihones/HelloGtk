#ifndef __GTKDISPLAYIMPL_H__
#define __GTKDISPLAYIMPL_H__

#include "browser/display/impl/DisplayImpl.h"
#include <X11/Xlib.h>

namespace pt {

class EventImpl;

class GtkDisplayImpl : public DisplayImpl
{
public:
	GtkDisplayImpl();
	virtual ~GtkDisplayImpl();
public:
	//from parent
	virtual bool connect();
	virtual void nextEvent(EventImpl *ev);
	virtual void close();
	//native method
	virtual Display* getNativeDisplay();
private:
	Display* mNativeDisplay;
};

}

#endif
