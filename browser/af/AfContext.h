#ifndef AFCONTEXT_H
#define AFCONTEXT_H

namespace af {

class AfProxy;

/*
 * context of app foundation
 */
class AfContext
{
public:
	AfContext();
	virtual ~AfContext();
public:
	virtual AfProxy* proxy() = 0;
};

}

#endif
