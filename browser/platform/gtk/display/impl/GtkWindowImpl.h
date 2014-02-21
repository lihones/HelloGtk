#ifndef __GTKWINDOWIMPL_H__
#define __GTKWINDOWIMPL_H__

#include <X11/Xlib.h>
#include "browser/display/impl/WindowImpl.h"

namespace pt {

class DisplayImpl;
class GcImpl;

class GtkWindowImpl : public WindowImpl
{
public:
	GtkWindowImpl();
	virtual ~GtkWindowImpl();
public:
	//from parent
	virtual void setLocation(int x, int y);
	virtual void setSize(int width, int height);
	virtual void move(int x, int y);
	virtual void resize(int width, int height);
	virtual void moveAndResize(int x, int y, int width, int height);
	virtual void attach(DisplayImpl *display);
	virtual void makeup();
	virtual GcImpl* gc();
	virtual void draw();
	virtual bool handleEvent(EventImpl *event);
private:
	int mX, mY;
	int mWidth, mHeight;
	Display *mNativeDisplay;
	int mNativeScreen;
	Window mNativeWindow;
};

}

#endif
