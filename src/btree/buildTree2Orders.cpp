#include <iostream>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
Difficulty: Medium
Topics: array, hashtable, divide and conquer, tree, binary tree
*/
class Solution {
public:
    // Simple recursive solution to construct the tree
    // A possible optimization is to write a helper function accepting an index.
    // Then, we don't need to keep copying the vectors and incur unnecessary cost
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.size() == 0) {
            return nullptr;
        }
        auto rootVal = preorder[0];
        auto root = new TreeNode(rootVal);
        if (preorder.size() == 1) {
            return root;
        }

        auto rootPos = 0; // This can be interpreted as index pos of the root in the inorder = num elems in left subtree
        for (auto i=0; i<inorder.size(); i++) {
            auto inVal = inorder[i];
            if (inVal == rootVal) {
                rootPos = i;
                break;
            }
        }

        vector<int> inLeft(inorder.begin(), inorder.begin()+rootPos);
        vector<int> inRight(inorder.begin()+rootPos+1, inorder.end());
        vector<int> preLeft(preorder.begin()+1, preorder.begin()+1+rootPos);
        vector<int> preRight(preorder.begin()+1+rootPos, preorder.end());

        root->left = buildTree(preLeft, inLeft);
        root->right = buildTree(preRight, inRight);
        return root;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> A = {3,9,20,15,7};
    vector<int> B = {9,3,15,20,7};
    auto T = S->buildTree(A, B);
    printPreOrder(T);
    cout << endl;
}
