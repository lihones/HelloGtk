#ifndef AFWINDOW_H
#define AFWINDOW_H

namespace af {

class AfWindow
{
public:
	AfWindow();
	virtual ~AfWindow();
public:
	virtual int map() = 0;
	virtual int unmap() = 0;
};

}

#endif
