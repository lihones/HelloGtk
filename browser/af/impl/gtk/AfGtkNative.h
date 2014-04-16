#ifndef AFGTKNATIVE_H
#define AFGTKNATIVE_H

#include <X11/Xlib.h>
#include "AfProxy.h"

namespace af {

class AfGtkNative : public AfProxy
{
public:
	static AfGtkNative* instance();
	static void release();
public:
	virtual int connect();
	virtual int disconnect();
	virtual Display* display();
	virtual int defaultScreen();
private:
	AfGtkNative();
	~AfGtkNative();
private:
	static AfGtkNative *mInstance;
	Display *mDisplay;
	int mDefaultScreen;
};

}

#endif
