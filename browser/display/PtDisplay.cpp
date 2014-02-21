#include "PtDisplay.h"
#include <iostream>
#include "PtWindow.h"
#include "PtEvent.h"
#include "impl/DisplayImpl.h"
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkDisplayImpl.h"
#endif

namespace pt {

using namespace std;

PtDisplay::PtDisplay()
{
	mImpl = NULL;
#ifdef PLATFORM__GTK
	mImpl = new GtkDisplayImpl();
#endif
}

PtDisplay::~PtDisplay()
{
	delete mImpl;
}

bool PtDisplay::connect()
{
	return mImpl->connect();
}

PtWindow* PtDisplay::createWindow(int width, int height)
{
	mWindow = new PtWindow();
	mWindow->setLocation(0, 0);
	mWindow->setSize(width, height);
	mWindow->attach(this);
	mWindow->makeup();
	return mWindow;
}

void PtDisplay::eventLoop()
{
	while(true) {
		PtEvent event;
		nextEvent(&event);
		if(event.type() == PtEvent::TYPE_CLOSE) {
			break;
		}

		mWindow->handleEvent(&event);
	}
}

void PtDisplay::nextEvent(PtEvent *ev)
{
	mImpl->nextEvent(ev->impl());
}

void PtDisplay::close()
{
	mImpl->close();
}

DisplayImpl* PtDisplay::impl()
{
	return mImpl;
}

}
