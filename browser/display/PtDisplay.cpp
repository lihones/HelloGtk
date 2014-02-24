#include "PtDisplay.h"
#include <iostream>
#include "PtWindow.h"
#include "PtEvent.h"
#include "impl/DisplayImpl.h"

namespace pt {

using namespace std;

PtDisplay::PtDisplay()
{
	mImpl = DisplayImpl::create();
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
