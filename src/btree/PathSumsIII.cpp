#include <iostream>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: https://leetcode.com/problems/path-sum-iii/
Difficulty: Medium
Topics: dfs, tree, binary tree
*/
class Solution {
public:
    // This will always deduct the value of the node
    int helper(TreeNode* node, long targetSum) {
        if (node == nullptr) return 0;
        long rem = targetSum-node->val;
        return (rem==0)
            + helper(node->left, rem) 
            + helper(node->right, rem);
    }

    // Find Paths excluding node plus Paths including node
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return 0;       
        return pathSum(root->left, targetSum) 
            + pathSum(root->right, targetSum)
            + helper(root, targetSum);
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *T = new TreeNode(10);
    T->left = new TreeNode(5);
    T->right = new TreeNode(-3);

    T->left->left = new TreeNode(3);
    T->left->right = new TreeNode(2);
    T->right->right = new TreeNode(11);

    T->left->left->left = new TreeNode(3);
    T->left->left->right = new TreeNode(-2);
    T->left->right->right = new TreeNode(1);

    printLevelOrder(T);
    cout << endl << "Number of paths = " << S->pathSum(T, 8) << endl;

    // [1,-2,-3,1,3,-2,null,-1]
    T = new TreeNode(1);
    T->left = new TreeNode(-2);
    T->right = new TreeNode(-3);

    T->left->left = new TreeNode(1);
    T->left->right = new TreeNode(3);
    T->right->left = new TreeNode(-2);

    T->left->left->left = new TreeNode(-1);

    printLevelOrder(T);
    cout << endl << "Number of paths = " << S->pathSum(T, 3) << endl;

}
