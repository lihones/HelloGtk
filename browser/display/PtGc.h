#ifndef __PTGC_H__
#define __PTGC_H__

namespace pt {

class GcImpl;

class PtGc
{
public:
	PtGc();
private:
	GcImpl *mImpl;
};

}

#endif
