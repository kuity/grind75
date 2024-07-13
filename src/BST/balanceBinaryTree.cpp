#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/balance-a-binary-search-tree
Difficulty: Medium
Topics: divide and conquer,greedy,tree,dfs,bst,binary tree
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
    void fillNodes(TreeNode* node, vector<int> &v) {
        if (!node) return;
        fillNodes(node->left, v);
        v.push_back(node->val);
        fillNodes(node->right, v);
    }

    TreeNode* constructTree(vector<int> &v) {
        if (v.size() == 0) return nullptr;
        else if (v.size() == 1) return new TreeNode(v[0]);
        int mid = v.size() / 2;
        vector<int> left(v.begin(), v.begin() + mid);
        // cout << "left size is " << left.size() << endl;
        vector<int> right(v.begin()+mid+1, v.end());
        // cout << "right size is " << right.size() << endl;
        return new TreeNode(v[mid], constructTree(left), constructTree(right));
    }

    TreeNode* balanceBST(TreeNode* root) {
        vector<int> V;
        fillNodes(root, V);
        // cout << V.size() << endl;
        return constructTree(V);
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
