#ifndef __RENDERVIEW_H__
#define __RENDERVIEW_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <iostream>
#include "RenderNode.h"
using namespace std;

class RenderView : public RenderNode
{
public:
	RenderView();
};

#ifdef __cplusplus
}
#endif

#endif
