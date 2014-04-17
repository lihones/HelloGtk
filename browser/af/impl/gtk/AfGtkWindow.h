#ifndef AFGTKWINDOW_H
#define AFGTKWINDOW_H

#include <X11/Xlib.h>
#include "AfWindow.h"

namespace af {

class AfGtkNative;
class AfGtkGc;

class AfGtkWindow : public AfWindow
{
public:
	AfGtkWindow();
	AfGtkWindow(AfGtkNative *native);
	~AfGtkWindow();
public:
	virtual void setRect(int x, int y, int width, int height);
	virtual int x();
	virtual int y();
	virtual int width();
	virtual int height();
	virtual AfGtkNative* native();
	virtual Window nativeWindow();
	//from parent
	virtual int map();
	virtual int unmap();
	virtual AfGc* gc();
private:
	int mX, mY;
	int mWidth, mHeight;
	AfGtkNative *mNative;
	Window mNativeWindow;
	AfGtkGc *mGc;
};

}

#endif
