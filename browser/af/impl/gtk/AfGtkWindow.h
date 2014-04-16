#ifndef AFGTKWINDOW_H
#define AFGTKWINDOW_H

#include <X11/Xlib.h>
#include "AfWindow.h"

namespace af {

class AfGtkNative;

class AfGtkWindow : public AfWindow
{
public:
	AfGtkWindow();
	AfGtkWindow(AfGtkNative *native);
	~AfGtkWindow();
public:
	virtual void setRect(int x, int y, int width, int height);
	//from parent
	virtual int map();
	virtual int unmap();
private:
	int mX, mY;
	int mWidth, mHeight;
	AfGtkNative *mNative;
	Window mNativeWindow;
};

}

#endif
