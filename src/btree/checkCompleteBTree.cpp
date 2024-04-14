#include <iostream>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: https://leetcode.com/problems/check-completeness-of-a-binary-tree/
Difficulty: Medium
Topics: bfs, tree, binary tree
*/
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
        if (root == nullptr) return false;
        vector<TreeNode *> children = {root};
        bool hasNull = false;
        while (!children.empty()) {
            int sz = children.size();
            vector<TreeNode *> childrenNew;
            for (auto i=0; i<sz; i++) {
                auto child = children[i];
                if (child == nullptr) {
                    hasNull = true; 
                    continue;
                }
                if (hasNull) return false;
                childrenNew.push_back(child->left);
                childrenNew.push_back(child->right);
            }
            children = childrenNew;
        }
        return true;
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *T = new TreeNode(1);
    T->left = new TreeNode(2);
    T->right = new TreeNode(3);
    T->left->left = new TreeNode(4);
    T->left->right = new TreeNode(5);
    T->right->left = new TreeNode(6);
    printLevelOrder(T);
    cout << "Tree is complete tree? " << S->isCompleteTree(T) << endl;

    T = new TreeNode(1);
    T->left = new TreeNode(2);
    T->right = new TreeNode(3);
    T->left->left = new TreeNode(4);
    T->left->right = new TreeNode(5);
    T->right->right = new TreeNode(7);
    printLevelOrder(T);
    cout << "Tree is complete tree? " << S->isCompleteTree(T) << endl;
}
