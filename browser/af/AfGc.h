#ifndef AFGC_H
#define AFGC_H

namespace af {

class AfGc
{
public:
	AfGc();
	virtual ~AfGc();
public:
	virtual void draw() = 0;
};

}

#endif
