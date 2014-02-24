#include "EventImpl.h"
#include <iostream>
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkEventImpl.h"
#endif

namespace pt {

using namespace std;

EventImpl::EventImpl()
{}

EventImpl::~EventImpl()
{}

EventImpl* EventImpl::create()
{
	EventImpl *impl = NULL;
#ifdef PLATFORM__GTK
	impl = new GtkEventImpl();
#endif
	return impl;
}

}
