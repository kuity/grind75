#include <vector>
#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
link: https://leetcode.com/problems/path-sum-ii/
difficulty: medium
topics: backtracking, tree, dfs, binary tree
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
    void DFS(int sum, int targetSum, TreeNode * node, vector<vector<int>> &ans, vector<int> &path) {
        if (node == nullptr) return;
        if (node->left == nullptr && node->right == nullptr) {
            if (sum+node->val == targetSum) {
                path.push_back(node->val);
                ans.push_back(path);
                path.pop_back();
            }
            return;
        }
        path.push_back(node->val);
        DFS(sum+node->val, targetSum, node->left, ans, path);
        DFS(sum+node->val, targetSum, node->right, ans, path);
        path.pop_back();
    }

    // It's DFS solution with some backtracking
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<vector<int>> ans;
        vector<int> path;
        DFS(0, targetSum, root, ans, path);
        return ans;
    }
};

int main() {
    TreeNode *l = new TreeNode(4, 
                    new TreeNode(11, new TreeNode(7), new TreeNode(2)), 
                    nullptr);
    TreeNode *r = new TreeNode(8, 
                    new TreeNode(13), 
                    new TreeNode(4, new TreeNode(5), new TreeNode(1)));
    TreeNode *t1 = new TreeNode(5, l, r);
    Solution *S = new Solution();
    vector<vector<int>> ans;
    ans = S->pathSum(t1, 22);
    printVecVec(ans);
}
