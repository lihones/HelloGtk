#include "PtEvent.h"
#include <iostream>
#include "impl/EventImpl.h"
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkEventImpl.h"
#endif

namespace pt {

using namespace std;

PtEvent::PtEvent()
{
	mImpl = NULL;
#ifdef PLATFORM__GTK
	mImpl = new GtkEventImpl();
#endif
}

PtEvent::~PtEvent()
{
	delete mImpl;
}

int PtEvent::type()
{
	return mImpl->type();
}

EventImpl* PtEvent::impl()
{
	return mImpl;
}

}
