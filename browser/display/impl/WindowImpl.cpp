#include "WindowImpl.h"
#include <iostream>
#include "browser/platform/PlatformDefine.h"
#ifdef PLATFORM__GTK
#include "browser/platform/gtk/display/impl/GtkWindowImpl.h"
#endif

namespace pt {

using namespace std;

WindowImpl::WindowImpl()
{}

WindowImpl::~WindowImpl()
{}

WindowImpl* WindowImpl::create()
{
	WindowImpl *impl = NULL;
#ifdef PLATFORM__GTK
	impl = new GtkWindowImpl();
#endif
	return impl;
}

}
