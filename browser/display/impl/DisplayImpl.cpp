#include "DisplayImpl.h"
#include <iostream>
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkDisplayImpl.h"
#endif

namespace pt {

using namespace std;

DisplayImpl::DisplayImpl()
{}

DisplayImpl::~DisplayImpl()
{}

DisplayImpl* DisplayImpl::create()
{
	DisplayImpl *impl = NULL;
#ifdef PLATFORM__GTK
	impl = new GtkDisplayImpl();
#endif
	return impl;
}

}
