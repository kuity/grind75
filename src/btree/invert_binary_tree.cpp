#include <iostream>

using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void printPreOrder(TreeNode* root) {
    if (!root) return;          // If current node is nullptr, just return

    std::cout << root->val << " ";  // Print the current node's value
    printPreOrder(root->left);   // Recursively print the left subtree
    printPreOrder(root->right);  // Recursively print the right subtree
}

/*
Link: https://leetcode.com/problems/invert-binary-tree/description/
Difficulty: Easy
Topics: dfs, bfs, tree, binary tree
*/
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
	if (root == nullptr) {
	    return nullptr;
	}
	TreeNode *newLeft = invertTree(root->right);
	root->right = invertTree(root->left);
	root->left = newLeft;
	return root;
    }
};

int main() {
    TreeNode *t1 = new TreeNode(4, 
			new TreeNode(2, new TreeNode(1), new TreeNode(3)), 
			new TreeNode(7, new TreeNode(6), new TreeNode(9)));
    Solution *S = new Solution();
    printPreOrder(t1);
    cout << endl;
    printPreOrder(S->invertTree(t1));
    cout << endl;
}
