#ifndef AFCONTEXT_H
#define AFCONTEXT_H

namespace af {

class AfWindow;
class AfProxy;

/*
 * context of app foundation
 */
class AfContext
{
public:
	AfContext();
	virtual ~AfContext();
public:
	virtual AfWindow* createWindow(int x, int y, int width, int height) = 0;
	virtual AfProxy* proxy() = 0;
};

}

#endif
