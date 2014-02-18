#ifndef __DISPLAYIMPL_H__
#define __DISPLAYIMPL_H__

namespace pt {

class DisplayImpl
{
public:
	DisplayImpl();
	virtual ~DisplayImpl();

public:
	virtual bool connect() = 0;
	virtual Window* createWindow(int width, int height) = 0;
	virtual void eventLoop() = 0;
	virtual void close() = 0;

private:
	virtual void nextEvent(Window &win, Event &ev) = 0;
};

}
