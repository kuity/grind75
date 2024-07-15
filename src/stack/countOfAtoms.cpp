#include <iostream>
#include <stack>
#include <map>

using namespace std;

/*
Link: https://leetcode.com/problems/number-of-atoms
Difficulty: Hard
Topics: hashtable, string, stack, sorting
*/
class Solution {
public:
    string countOfAtoms(string formula) {
        string atom = "";
        string multiplier = "";
        vector<pair<string, int>> V;
        stack<int> Open;
        int openPar = -1;

        auto processAtom = [&multiplier, &openPar, &atom, &V]() {
            // case 1: there is open parens and multiplier
            if (multiplier.size() > 0 && openPar > -1) {
                for (auto i=openPar; i<V.size(); i++) V[i].second *= stoi(multiplier);
            }
            // case 2: there is multiplier and atom
            else if (multiplier.size() > 0 && atom.size() > 0) {
                V.push_back({atom, stoi(multiplier)});
            } 
            // case 3: there is atom only
            else if (atom.size() > 0) {
                V.push_back({atom, 1});
            }
            // reset everything
            atom = "";
            multiplier = "";
            openPar = -1;
        };

        for (char c: formula) {
            if (isdigit(c)) {
                multiplier += c;
            } else if (islower(c)) {
                atom += c;
            } else if (c == ')') {
                processAtom();
                openPar = Open.top();
                Open.pop();
            } else if (c == '(') {
                processAtom();
                Open.push(V.size());
            } else { // uppercase letter
                processAtom();
                atom += c;
            }
        }
        processAtom();

        map<string, int> M;
        for (auto p: V) M[p.first]+=p.second;
        string ans;
        for (auto e: M) {
            ans += e.first;
            if (e.second > 1) ans += to_string(e.second);
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
