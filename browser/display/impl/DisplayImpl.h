#ifndef __DISPLAYIMPL_H__
#define __DISPLAYIMPL_H__

namespace pt {

class EventImpl;

class DisplayImpl
{
public:
	DisplayImpl();
	virtual ~DisplayImpl();
public:
	virtual bool connect() = 0;
	virtual void nextEvent(EventImpl *ev) = 0;
	virtual void close() = 0;
};

}

#endif
