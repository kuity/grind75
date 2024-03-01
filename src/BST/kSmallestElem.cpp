#include <iostream>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst
Difficulty: Medium
Topics: Tree, BST, DFS, Binary Tree
*/
class Solution {
public:
    // The idea here is to have a recursive helper function
    // The objective is to return whether or not the node is found
    // If found, return the found value
    // If not, return the number of nodes including the root
    // In the function, we should first find in left, then consider root, then find in right
    // Since we need to count starting from the smallest value node
    pair<bool, int> find(TreeNode *root, int k) {
	if (root == nullptr) return {false, 0};
	// cout << "Calling find with root " << root->val << " and k " << k << endl;
	auto checkLeft = find(root->left, k);
	if (checkLeft.first) return {true, checkLeft.second};
	if (checkLeft.second == k-1) return {true, root->val};
	auto checkRight = find(root->right, k-checkLeft.second-1);
	if (checkRight.first) return {true, checkRight.second};
	return {false, checkLeft.second + checkRight.second + 1};
    }

    int kthSmallest(TreeNode* root, int k) {
	auto ans = find(root, k);
	return ans.second;
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *x = new TreeNode(5, 
			new TreeNode(3, 
			    new TreeNode(2, new TreeNode(1), nullptr), 
			    new TreeNode(4)), 
			new TreeNode(6)
    );

    auto ans = S->kthSmallest(x, 3);
    cout << "3rd smallest is " << ans << endl;
    ans = S->kthSmallest(x, 4);
    cout << "4th smallest is " << ans << endl;
    ans = S->kthSmallest(x, 5);
    cout << "5th smallest is " << ans << endl;
    ans = S->kthSmallest(x, 6);
    cout << "6th smallest is " << ans << endl;

}
