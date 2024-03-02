#include <iostream>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: 
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/
Difficulty: Medium
Topics: dfs, bfs, tree, binary tree
*/
class Solution {
public:
    // Recursive solution:
    //
    // If the root node value is either p or q
    // We return the root node 
    // The search no need to continue, because if the unfound p or q 
    // is one of the children, the root node is still the LCA
    //
    // If search node is null, return null (= not found)
    //
    // Otherwise, we recursively search left child and right child
    // If either search rets null, the LCA is the ret value of the other search
    // As both p and q must be on the other side
    //
    // If both are not null, the LCA must be the root
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == NULL) {
            return NULL;
        }

        if (p->val == root->val || q->val == root->val) {
            return root;
        }

        auto leftSearch = lowestCommonAncestor(root->left, p, q);
        auto rightSearch = lowestCommonAncestor(root->right, p, q);

        if (leftSearch == NULL) {
            return rightSearch;
        } else if (rightSearch == NULL) {
            return leftSearch;
        } else {
            return root;
        }
    }
};

int main() {
    TreeNode *p = new TreeNode(5, 
                new TreeNode(6), 
                new TreeNode(2, 
                    new TreeNode(7), 
                    new TreeNode(4)));

    TreeNode *q = new TreeNode(1, 
                new TreeNode(0), 
                new TreeNode(8));

    TreeNode *t1 = new TreeNode(3, p, q);
    Solution *S = new Solution();
    auto ans = S->lowestCommonAncestor(t1, p, q);
    cout << "Answer is " << ans->val << endl;
}
