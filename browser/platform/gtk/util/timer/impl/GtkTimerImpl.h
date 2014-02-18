#ifndef __GTKTIMERIMPL_H__
#define __GTKTIMERIMPL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <iostream>
#include "browser/util/timer/impl/TimerImpl.h"

class GtkTimerImpl : public TimerImpl
{
public:
	GtkTimerImpl();
};

#ifdef __cplusplus
}
#endif

#endif
