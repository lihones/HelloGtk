#ifndef __GTKDISPLAYIMPL_H__
#define __GTKDISPLAYIMPL_H__

#include "browser/display/impl/DisplayImpl.h"

namespace pt {

class GtkDisplayImpl : public DisplayImpl
{
public:
	GtkDisplayImpl();
	virtual ~GtkDisplayImpl();

public:
	virtual bool connect() = 0;
	virtual Window* createWindow(int width, int height) = 0;
	virtual void eventLoop() = 0;
	virtual void close() = 0;

private:
	virtual void nextEvent(Window &win, Event &ev) = 0;
};

}
