#ifndef __HTMLPARSER_H__
#define __HTMLPARSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <iostream>
#include "browser/dom/DomRoot.h"
using namespace std;

class HtmlParser
{
public:
	HtmlParser();

	DomRoot* parse(string document);
private:
};

#ifdef __cplusplus
}
#endif

#endif
