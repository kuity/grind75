#include <iostream>
#include <vector>
#include "../lib/TreeNode.h"
#include "../lib/util.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<TreeNode *> children;
        vector<vector<int>> ans;
        if (root != nullptr) {
            children.push_back(root);
        }

        while(!children.empty()) {
            vector<TreeNode *> tmp;
            vector<int> vals;
            for (auto t: children) {
            vals.push_back(t->val);
            if (t->left != nullptr) {
                tmp.push_back(t->left);
            }
            if (t->right != nullptr) {
                tmp.push_back(t->right);
            }
            }
            ans.push_back(vals);
            children = tmp;
        }
        return ans;
    }
};

int main() {
    TreeNode *t1 = new TreeNode(4, 
            new TreeNode(2, new TreeNode(1), new TreeNode(3)), 
            new TreeNode(7, new TreeNode(6), new TreeNode(9)));
    printPreOrder(t1);
    cout << endl;
    Solution *S = new Solution();
    auto ans = S->levelOrder(t1);
    printVecVec(ans);
}
