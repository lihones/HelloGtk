#ifndef __TIMER_H__
#define __TIMER_H__

#include "impl/TimerImpl.h"
#include "platform/PlatformDefine.h"

namespace pt {

class Timer
{
public:
	Timer();
private:
	TimerImpl *mImpl;
};

}

#endif
