#include <iostream>
#include "../../lib/util.h"

using namespace std;

class Solution {
public:
    // Idea. Keep string in a "frequency array" and keep sliding the window
    vector<int> findAnagrams(string s, string p) {
	if (p.size() > s.size()) return {};
	int plen = p.size();
	int head = s.size()-plen;
	int tail = s.size()-1;

        vector<int> ans;
	vector<int> pFreq(26, 0);
	vector<int> sFreq(26, 0);
	for (auto c: p) pFreq[c-'a']++;
	for (auto c: s.substr(head)) sFreq[c-'a']++;
	// printVec(pFreq); cout << endl;

	while(head >= 0) {
	    // printVec(sFreq); cout << endl;
	    if (pFreq == sFreq) ans.push_back(head);
	    head--; if (head < 0) break;
	    sFreq[s[head]-'a']++;
	    sFreq[s[tail]-'a']--;
	    tail--;
	}

	return ans;
    }
};

int main() {
    string s = "cbaebabacd";
    // cout << s << endl;
    Solution *S = new Solution();
    auto ans = S->findAnagrams(s, "abc");
    printVec(ans);
}
