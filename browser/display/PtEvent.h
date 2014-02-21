#ifndef __PTEVENT_H__
#define __PTEVENT_H__

namespace pt {

class EventImpl;

class PtEvent
{
public:
	PtEvent();
	virtual ~PtEvent();
public:
	virtual int type();
	virtual EventImpl* impl();
public:
	static const int TYPE_CLOSE = 1;
private:
	EventImpl *mImpl;
};

}

#endif
