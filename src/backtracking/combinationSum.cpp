#include <iostream>
#include "../../lib/util.h"

using namespace std;

/*
Link: https://leetcode.com/problems/combination-sum/description/
Difficulty: Medium
Topics: array, backtracking
*/
class Solution {
public:
    // More efficient implementation soln with backtracking
    // No need to copy vector but still cover all possibilities
    //
    // Why this works:
    // We see in the function body in the loop, a number
    // is pushed and popped exactly once, so the math checks out
    //
    // Also, the recursive calls in each iteration do not overlap
    // because index was incremented.
    // eg. candidates=[1, 2, 3, 4, 5]
    // Then index=0 calls will definitely contain 1
    // But index=1 calls will definitely not contain 1
    // Thus they are distinct sets
    // Finally, within each iteration i, the recursive calls will cover
    // all combinations that can possibly include candidates[i]
    void helper2(vector<int>& candidates, int target, int index, 
                vector<int>& partial, vector<vector<int>>& ans) 
    {
        if (target == 0) {ans.push_back(partial); return;}
        while (index < candidates.size()) {
            auto candidate = candidates[index];
            auto newTarget = target-candidate;
            if (newTarget < 0) break;
            partial.push_back(candidate);
            helper2(candidates, newTarget, index, partial, ans);
            partial.pop_back();
            index++;
        }
    }

    // Not very efficient recursive soln as we need to copy the vector
    void helper(vector<int>& candidates, int target, int index, 
                vector<int>& partial, vector<vector<int>>& ans) 
    {
        if (target == 0) {ans.push_back(partial); return;}
        if (index >= candidates.size()) return;

        auto candidate = candidates[index];
        while (target >= 0) {
            vector<int> newPartial = partial;
            helper(candidates, target, index+1, newPartial, ans);
            target -= candidate;
            partial.push_back(candidate);
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> ans;
        vector<int> partial;
        helper2(candidates, target, 0, partial, ans);
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> C = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);


    C = {2, 3, 5};
    target = 8;
    ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);


    C = {2};
    target = 1;
    ans = S->combinationSum(C, target);
    cout << "candidates are: " << endl;
    printVec(C);
    cout << "target is: " << target << endl;
    cout << "ans is: ";
    printVecVec(ans);
}
