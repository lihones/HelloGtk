#include "GtkEventImpl.h"
#include <iostream>

namespace pt {

using namespace std;

GtkEventImpl::GtkEventImpl()
{}

GtkEventImpl::~GtkEventImpl()
{
}

int GtkEventImpl::type()
{
	return mNativeEvent.type;
}

XEvent* GtkEventImpl::getNativeEvent()
{
	return &mNativeEvent;
}

}
