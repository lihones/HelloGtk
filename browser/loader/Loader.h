#ifndef __LOADER_H__
#define __LOADER_H__

#include <iostream>

namespace pt {

using namespace std;

class Loader
{
public:
	Loader();

	void loadUrl(string url);
	void setViewport(int w, int h);

private:
	string url;
	int width;
	int height;
};

}

#endif
