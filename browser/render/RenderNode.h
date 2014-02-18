#ifndef __RENDERNODE_H__
#define __RENDERNODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <iostream>
#include "ds/TreeNode.h"
using namespace std;

class RenderNode : public TreeNode
{
public:
	RenderNode();
};

#ifdef __cplusplus
}
#endif

#endif
