#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "impl/DisplayImpl.h"

namespace pt {

class Display
{
public:
	Display();
private:
	DisplayImpl *mImpl;
};

}
