#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// Utility function to subtract two bools and calculate diff 
// and borrow 
bool fullSubtractor(bool b1, bool b2, bool& borrow) { 
    bool diff; 
    if (borrow) { 
        diff = !(b1 ^ b2); 
        borrow = !b1 || (b1 && b2); 
    } 
    else { 
        diff = b1 ^ b2; 
        borrow = !b1 && b2; 
    } 
    return diff; 
} 
// Function to calculate difference between two bitsets 
bitset<3000> bitsetSubtract(bitset<3000> x, bitset<3000> y) { 
    bool borrow = false; 
    // bitset to store the sum of the two bitsets 
    bitset<3000> ans; 
    for (int i = 0; i < 2999; i++) { 
        ans[i] = fullSubtractor(x[i], y[i], borrow); 
    } 
    return ans; 
}

/*
Link: https://leetcode.com/problems/maximum-width-of-binary-tree/description/
Difficulty: Medium
Topics: dfs, bfs, tree, binary tree
*/
class Solution {
    unordered_map<int, vector<string>> M;
public:
    // Kind of a brute-forcy DFS solution because we don't really have a good way to deal with integer overflow
    // Imagine a very skewed tree with only 1 node per level.
    // We ends up with a very long bitstring
    void DFS(TreeNode *N, string &path) {
        if (N == nullptr) return;
        int sz = path.size();
        M[sz].push_back(path);
        path.push_back('0');
        DFS(N->left, path);
        path.pop_back();
        path.push_back('1');
        DFS(N->right, path);
        path.pop_back();
    }

    int widthOfBinaryTree(TreeNode* root) {
        string path;
        DFS(root, path);
        int maxWidth = 1;
        for (auto kv: M) {
            auto v = kv.second;
            if (v.size()==1) continue;
            auto str1 = v[v.size()-1];
            auto str2 = v[0];
            // cout << "str1 is " << str1 << endl;
            // cout << "str2 is " << str2 << endl;
            auto bs1 = std::bitset<3000>(str1);
            auto bs2 = std::bitset<3000>(str2);
            auto bsdiff = bitsetSubtract(bs1, bs2);
            std::bitset<32> bsdiffSmall;
            for (int i = 0; i < 32; ++i) {
                bsdiffSmall[i] = bsdiff[i];
            }

            // Convert the 32-bit bitset to an unsigned long (which is typically 32-bit on many systems, but use static_cast to ensure it's treated as unsigned int)
            unsigned int w = static_cast<unsigned int>(bsdiffSmall.to_ulong()) + 1;
            // cout << "width is " << w << endl;
            if (w > maxWidth) maxWidth = w;
        }
        return maxWidth;
    }

    // Better way to deal with integer overflow 
    // Subtracting the "minimum index" at each level
    int widthOfBinaryTreeBFS(TreeNode* root) {
        if(root == NULL) // if root is null 
            return 0;   // simply return zero
        
        int ans = 0; // variable to store answer
        
        // queue for level order traveral
        queue<pair<TreeNode*, int>> q; // pair contain { node, index}
        q.push({root, 1}); // intially push root node 
        
        // Implementing BFS
        while(q.empty() == false) // until queue is not empty
        {
            int size = q.size(); // take size of the queue
            // tells us minimum index at particular level
            int minAtLevel = q.front().second; 
            // declaring minimum and maximum variable used for finding width
            int mn, mx;
            // traverse from the queue
            for(int i= 0; i < size; i++)
            {
                // changes index of level by decreasing minimum index
                int curr_index = q.front().second - minAtLevel + 1; //+ 1 because we are using 1 based indexing,
                // take out current node
                TreeNode* node = q.front().first;
                q.pop(); // pop from the queue
                //width = (maximum index at level) - (minimum index at level) + 1
                if(i == 0) 
                    mn = curr_index; // minimum index at level
                if(i == size - 1)
                    mx = curr_index; //maximum index at level
                
                // push left and right for further calculation
                if(node -> left != NULL) //2   * i
                    q.push({node -> left, 2LL * curr_index});
                if(node -> right != NULL) //2   * i  + 1
                    q.push({node -> right, 2LL * curr_index + 1});
                   
            }
            ans = max(ans, mx - mn + 1);
        }
        return ans;
    }
};

int main() {
    TreeNode *t1 = new TreeNode(1, 
            new TreeNode(3, new TreeNode(5, new TreeNode(6), nullptr), nullptr), 
            new TreeNode(2, nullptr, new TreeNode(9, new TreeNode(7), nullptr)));
    Solution *S = new Solution();
    auto ans = S->widthOfBinaryTree(t1);
    cout << ans << endl;

    ans = S->widthOfBinaryTreeBFS(t1);
    cout << ans << endl;
}
