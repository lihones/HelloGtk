#ifndef __EVENTIMPL_H__
#define __EVENTIMPL_H__

namespace pt {

class EventImpl
{
public:
	EventImpl();
	virtual ~EventImpl();
	static EventImpl* create();
public:
	virtual int type() = 0;
};

}

#endif
