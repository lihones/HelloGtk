#ifndef __PTWINDOW_H__
#define __PTWINDOW_H__

namespace pt {

class WindowImpl;
class PtDisplay;
class PtGc;
class PtEvent;

class PtWindow
{
public:
	PtWindow();
	virtual ~PtWindow();
public:
	virtual void setLocation(int x, int y);
	virtual void setSize(int width, int height);
	//
	virtual void move(int x, int y);
	virtual void resize(int width, int height);
	virtual void moveAndResize(int x, int y, int width, int height);
	//
	virtual void attach(PtDisplay *display);
	virtual void makeup();
	//
	virtual PtGc* gc();
	virtual void draw();
	//
	virtual bool handleEvent(PtEvent *event);
public:
	virtual WindowImpl* impl();
private:
	PtDisplay *mDisplay;
	WindowImpl *mImpl;
};

}

#endif
