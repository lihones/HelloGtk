#ifndef AFGTKCONTEXT_H
#define AFGTKCONTEXT_H

#include "AfContext.h"

namespace af {

class AfWindow;
class AfProxy;
class AfGtkNative;
class AfGtkWindow;

class AfGtkContext : public AfContext
{
public:
	AfGtkContext();
	~AfGtkContext();
public:
	virtual AfWindow* createWindow(int x, int y, int width, int height);
	virtual AfProxy* proxy();
private:
	AfGtkNative *mNative;
	AfGtkWindow *mWindow;
};

}

#endif
