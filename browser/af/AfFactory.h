#ifndef AFFACTORY_H
#define AFFACTORY_H

#include "impl/AfPlatformDefine.h"

namespace af {

class AfContext;

class AfFactory
{
public:
	static AfContext* createContext();
};

}

#endif
