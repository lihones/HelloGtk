#include "AfGtkContext.h"
#include "AfGtkNative.h"

namespace af {

AfGtkContext::AfGtkContext()
{
	mNative = AfGtkNative::instance();
	mNative->gtkSample();
}

AfGtkContext::~AfGtkContext()
{
}

AfProxy* AfGtkContext::proxy()
{
	return mNative;
}

}
