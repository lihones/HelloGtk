#ifndef __HTMLPARSER_H__
#define __HTMLPARSER_H__

#include <iostream>
#include "browser/dom/DomRoot.h"

namespace pt {

using namespace std;

class HtmlParser
{
public:
	HtmlParser();

	DomRoot* parse(string document);
private:
};

}

#endif
