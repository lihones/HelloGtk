#ifndef AFGTKCONTEXT_H
#define AFGTKCONTEXT_H

#include "AfContext.h"

namespace af {

class AfGtkNative;

class AfGtkContext : public AfContext
{
public:
	AfGtkContext();
	~AfGtkContext();
public:
	virtual AfProxy* proxy();
private:
	AfGtkNative *mNative;
};

}

#endif
