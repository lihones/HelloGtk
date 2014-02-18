#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "impl/DisplayImpl.h"
#include "Event.h"

namespace pt {

class Display
{
public:
	Display();

public:
	bool connect();
	Window* createWindow(int width, int height);
	void eventLoop();
	void close();

private:
	void nextEvent(Window &win, Event &ev);

private:
	DisplayImpl *mImpl;
};

}
