#ifndef __WINDOWIMPL_H__
#define __WINDOWIMPL_H__

namespace pt {

class DisplayImpl;
class GcImpl;
class EventImpl;

class WindowImpl
{
public:
	WindowImpl();
	virtual ~WindowImpl();
public:
	virtual void setLocation(int x, int y) = 0;
	virtual void setSize(int width, int height) = 0;
	//
	virtual void move(int x, int y) = 0;
	virtual void resize(int width, int height) = 0;
	virtual void moveAndResize(int x, int y, int width, int height) = 0;
	//
	virtual void attach(DisplayImpl *display) = 0;
	virtual void makeup() = 0;
	//
	virtual GcImpl* gc() = 0;
	virtual void draw() = 0;
	//
	virtual bool handleEvent(EventImpl *event) = 0;
};

}

#endif
