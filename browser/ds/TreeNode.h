#ifndef __TREENODE_H__
#define __TREENODE_H__

#include <iostream>
#include <vector>

namespace pt {

using namespace std;

class TreeNode
{
public:
	TreeNode();
	~TreeNode();

public:
	int getCount();
	TreeNode* get(int pos);
	void add(TreeNode* node);
	vector<TreeNode*>& getChildren();

private:
	vector<TreeNode*> children;
};

}

#endif
