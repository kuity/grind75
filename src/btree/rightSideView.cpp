#include <iostream>
#include "../../lib/TreeNode.h"
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/binary-tree-right-side-view/description/
Difficulty: Medium
Topics: dfs, bfs, tree, binary tree
*/
class Solution {
public:
    // An iterative solution that slightly modify level order traversal
    // We need a vec to store children for the next level
    vector<int> rightSideView(TreeNode* root) {
	vector<TreeNode *> children;
        vector<int> ans;
	children.push_back(root);

        while(!children.empty()) {
	    auto numNodes = children.size();
	    vector<TreeNode *> nextChildren;

	    int *rightMost = nullptr;
            for (auto i=0; i<numNodes; i++) {
		auto node = children[i];
		if (node != nullptr) {
		    rightMost = &node->val;
		    nextChildren.push_back(node->left);
		    nextChildren.push_back(node->right);
		}
	    }
	    
	    if (rightMost != nullptr) {
		ans.push_back(*rightMost);
	    }
	    children = nextChildren;
        }

	return ans;
    }

    void preOrder(TreeNode *root, int level, vector<int> *ans) {
	if (root == nullptr) return;
	if ((*ans).size() < level) ans->push_back(root->val);
	preOrder(root->right, level+1, ans);
	preOrder(root->left, level+1, ans);
    }

    // Recursively it is also possible using a pre-order traversal from the right subtree
    // There is a clever way to determine to push or not to push
    // And that's to propagate the current level to each function call
    // because we know nodes get traversed from right to left
    // then only push if the size of pushed nums is less than the current level
    // as this node MUST be the rightmost node in this level
    // (if there is a righter node, it would have been visited first)
    // One benefit is that there is no need to store children
    vector<int> rightSideViewR(TreeNode* root) {
	vector<int> rightSide;
	preOrder(root, 1, &rightSide);
	return rightSide;
    }
};

int main() {
    TreeNode *t1 = new TreeNode(1, 
            new TreeNode(2, nullptr, new TreeNode(5)), 
            new TreeNode(3));
    printPreOrder(t1);
    cout << endl;
    Solution *S = new Solution();
    auto ans = S->rightSideViewR(t1);
    printVec(ans);
}
