#include <iostream>
#include <cairo-xlib.h>
#include "AfGtkGc.h"
#include "AfGtkNative.h"
#include "AfGtkWindow.h"

namespace af {

AfGtkGc::AfGtkGc()
{
	mSurface = NULL;
	mWidth = 0;
	mHeight = 0;
}

AfGtkGc::AfGtkGc(AfGtkWindow *window)
{
	AfGtkNative *native = window->native();
	Display *display = native->display();
	int screen = native->defaultScreen();
	Window nativeWindow = window->nativeWindow();
	mWidth = window->width();
	mHeight = window->height();
	mSurface = cairo_xlib_surface_create(display, nativeWindow, DefaultVisual(display, screen), mWidth, mHeight);
}

void AfGtkGc::draw()
{
	cairo_t *c;
	c = cairo_create(mSurface);

	cairo_rectangle(c, 0.0, 0.0, mWidth, mHeight);
	cairo_set_source_rgb(c, 0.0, 0.0, 0.5);
	cairo_fill(c);

	cairo_show_page(c);
	cairo_destroy(c);
}

AfGtkGc::~AfGtkGc()
{
	cairo_surface_destroy(mSurface);
}

}
