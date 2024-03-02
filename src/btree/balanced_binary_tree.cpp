#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
Link: https://leetcode.com/problems/balanced-binary-tree/description/
Difficulty: Easy
Topics: tree, dfs, binary tree
*/
class Solution {
public:
    pair<int, bool> helper(TreeNode* t) {
	if (t == nullptr) {
	    return {0, true};
	}

	pair<int, bool> pleft = helper(t->left);
	pair<int, bool> pright = helper(t->right);

	return {max(pleft.first, pright.first)+1,  
	    abs(pleft.first - pright.first)<=1
	    && pleft.second && pright.second
	};
    }

    bool isBalanced(TreeNode* root) {
	return helper(root).second;
    }
};

int main() {
    TreeNode *t = new TreeNode(4, 
			new TreeNode(2, new TreeNode(1), new TreeNode(3)), 
			nullptr);
    Solution *S = new Solution();
    cout << S->isBalanced(t) << endl;
    TreeNode *x = new TreeNode(4, 
			new TreeNode(2, 
			    new TreeNode(1, new TreeNode(5), nullptr), 
			    nullptr), 
			new TreeNode(9, 
			    new TreeNode(2), new TreeNode(7))
    );
    cout << S->isBalanced(x) << endl;
    TreeNode *y = new TreeNode(9, new TreeNode(2), new TreeNode(7));
    cout << S->isBalanced(y) << endl;
}
