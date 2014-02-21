#ifndef __PTDISPLAY_H__
#define __PTDISPLAY_H__

namespace pt {

class DisplayImpl;
class PtWindow;
class PtEvent;

class PtDisplay
{
public:
	PtDisplay();
	virtual ~PtDisplay();
public:
	virtual bool connect();
	virtual PtWindow* createWindow(int width, int height);
	virtual void eventLoop();
	virtual void nextEvent(PtEvent *ev);
	virtual void close();
public:
	virtual DisplayImpl* impl();
private:
	DisplayImpl *mImpl;
	PtWindow *mWindow;
};

}

#endif
