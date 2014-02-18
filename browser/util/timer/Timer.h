#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "impl/TimerImpl.h"
#include "platform/PlatformDefine.h"

class Timer
{
public:
	Timer();
private:
	TimerImpl* mImpl;
};

#ifdef __cplusplus
}
#endif

#endif
