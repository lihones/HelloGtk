#ifndef __HTMLPARSER_H__
#define __HTMLPARSER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <iostream>
#include <vector>
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

#ifdef __cplusplus
}
#endif

#endif
