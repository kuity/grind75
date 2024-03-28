#include <iostream>
#include "../../lib/TreeNode.h"
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
Difficulty: Medium
Topics: tree, bfs, binary tree
*/
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        vector<TreeNode *> Q;
        bool left2right = true;
        if (root!=nullptr) Q.push_back(root);
        while(!Q.empty()) {
            vector<int> newV;
            vector<TreeNode *> newQ;
            for (int i=Q.size()-1; i>=0; i--) {
                newV.push_back(Q[i]->val);
                if (left2right) {
                    if (Q[i]->left != nullptr) newQ.push_back(Q[i]->left);
                    if (Q[i]->right != nullptr) newQ.push_back(Q[i]->right);
                } else {
                    if (Q[i]->right != nullptr) newQ.push_back(Q[i]->right);
                    if (Q[i]->left != nullptr) newQ.push_back(Q[i]->left);
                }
            }
            Q = newQ;
            ans.push_back(newV);
            left2right = !left2right;
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *x = new TreeNode(3, 
			new TreeNode(9),
			new TreeNode(20, 
			    new TreeNode(15), 
			    new TreeNode(7))
    );

    printPreOrder(x);
    cout << endl;
    auto nodes = S->zigzagLevelOrder(x);
    printVecVec(nodes);
}
