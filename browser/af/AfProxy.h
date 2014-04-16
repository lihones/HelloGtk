#ifndef AFPROXY_H
#define AFPROXY_H

namespace af {

/*
 * proxy for native
 */
class AfProxy
{
public:
	AfProxy();
	virtual ~AfProxy();
public:
	virtual int connect() = 0;
	virtual int disconnect() = 0;
};

}

#endif
