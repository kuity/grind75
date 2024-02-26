#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans = {};
        int rowUB = matrix[0].size()-1;
        int rowLB = 0;
        int colUB = matrix.size()-1;
        int colLB = 0;
        int numTotal = (colUB+1)*(rowUB+1);

        while (ans.size() < numTotal) {
            for (int i=rowLB; i<=rowUB; i++) { ans.push_back(matrix[colLB][i]); }
            colLB++;
            if (ans.size() == numTotal) break;
            for (int i=colLB; i<=colUB; i++) { ans.push_back(matrix[i][rowUB]); }
            rowUB--;
            if (ans.size() == numTotal) break;
            for (int i=rowUB; i>=rowLB; i--) { ans.push_back(matrix[colUB][i]); }
            colUB--;
            if (ans.size() == numTotal) break;
            for (int i=colUB; i>=colLB; i--) { ans.push_back(matrix[i][rowLB]); }
            rowLB++;
            if (ans.size() == numTotal) break;
        }

        return ans;
    }
};

int main() {
    vector<vector<int>> v = {{1,2,3},{4,5,6},{7,8,9}};
    Solution *S = new Solution();
    vector<int> ans = S->spiralOrder(v);
    for (auto x: ans) cout << x << ","; cout <<endl;

    v = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    ans = S->spiralOrder(v);
    for (auto x: ans) cout << x << ","; cout <<endl;
}
