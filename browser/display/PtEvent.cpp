#include "PtEvent.h"
#include <iostream>
#include "impl/EventImpl.h"

namespace pt {

using namespace std;

PtEvent::PtEvent()
{
	mImpl = EventImpl::create();
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
