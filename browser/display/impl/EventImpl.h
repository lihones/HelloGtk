#ifndef __EVENTIMPL_H__
#define __EVENTIMPL_H__

namespace pt {

class EventImpl
{
public:
	EventImpl();
	virtual ~EventImpl();
public:
	virtual int type() = 0;
};

}

#endif
