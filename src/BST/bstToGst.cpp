#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree
Difficulty: Medium
Topics: tree,dfs,binary search tree,binary tree
*/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 1. This will RETURN the sum of all children inclusive the root
    // 2. Add the value of root to sum of right subtree (X)
    // 3. Propagate X to the left subtree
    // 4. Assign X + accumulated (propagated X in params) to root->val
    int helper(TreeNode *root, int accumulated) {
        if (!root) return 0;
        int rightSum = helper(root->right, accumulated);
        int X = root->val + rightSum;
        int leftSum = helper(root->left, accumulated + X);
        root->val = accumulated + X;
        return leftSum + X;
    }

    TreeNode* bstToGst(TreeNode* root) {
        helper(root, 0);
        return root;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
