#ifndef AFGTKGC_H
#define AFGTKGC_H

#include <cairo.h>
#include "AfGc.h"

namespace af {

class AfGtkWindow;

class AfGtkGc : public AfGc
{
public:
	AfGtkGc();
	AfGtkGc(AfGtkWindow *window);
	~AfGtkGc();
public:
	//from parent
	virtual void draw();
private:
	cairo_surface_t *mSurface;
	int mWidth, mHeight;
};

}

#endif
