#include <iostream>
#include "AfFactory.h"
#include "AfContext.h"
#include "impl/gtk/AfGtkContext.h"

namespace af {

AfContext* AfFactory::createContext()
{
	AfContext *impl;
#ifdef PLATFORM_GTK
	impl = new AfGtkContext();
#endif
	return impl;
}

}
