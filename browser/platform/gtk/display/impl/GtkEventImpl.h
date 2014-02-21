#ifndef __GTKEVENTIMPL_H__
#define __GTKEVENTIMPL_H__

#include "browser/display/impl/EventImpl.h"
#include <X11/Xlib.h>

namespace pt {

class GtkEventImpl : public EventImpl
{
public:
	GtkEventImpl();
	virtual ~GtkEventImpl();
public:
	virtual int type();
	//
	virtual XEvent* getNativeEvent();
public:
	XEvent mNativeEvent;
};

}

#endif
