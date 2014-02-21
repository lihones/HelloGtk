#include "PtWindow.h"
#include <iostream>
#include "PtDisplay.h"
#include "PtEvent.h"
#include "impl/WindowImpl.h"
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkWindowImpl.h"
#endif


namespace pt {

using namespace std;

PtWindow::PtWindow()
{
	mImpl = NULL;
#ifdef PLATFORM__GTK
	mImpl = new GtkWindowImpl();
#endif
}

PtWindow::~PtWindow()
{
	delete mImpl;
}

void PtWindow::setLocation(int x, int y)
{
	mImpl->setLocation(x, y);
}

void PtWindow::setSize(int width, int height)
{
	mImpl->setSize(width, height);
}

void PtWindow::move(int x, int y)
{
	mImpl->move(x, y);
}

void PtWindow::resize(int width, int height)
{
	mImpl->resize(width, height);
}

void PtWindow::moveAndResize(int x, int y, int width, int height)
{
	mImpl->moveAndResize(x, y, width, height);
}

void PtWindow::attach(PtDisplay *display)
{
	mDisplay = display;
	mImpl->attach(display->impl());
}

void PtWindow::makeup()
{
	mImpl->makeup();
}

PtGc* PtWindow::gc()
{
	return NULL;
}

void PtWindow::draw()
{
	mImpl->draw();
}

bool PtWindow::handleEvent(PtEvent *event)
{
	return mImpl->handleEvent(event->impl());
}

WindowImpl* PtWindow::impl()
{
	return mImpl;
}

}
