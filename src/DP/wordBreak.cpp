#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

/*
Link: https://leetcode.com/problems/word-break/description/
Difficulty: Medium
Topics: array, hashtable, string, dp, trie, memoization
*/
class Solution {
private:
    unordered_map<string, bool> DP;
    set<string> words;

public:
    bool helper(string s) {
        // cout << "Finding " << s << endl;
        if (DP.find(s) != DP.end()) {
            return DP[s];
        }

        if (s.size() == 0) {
            return true;
        }

        string newS = "";
        for (auto i=0; i<s.size(); i++) {
            auto c = s[i];
            newS += c;
            if (words.find(newS) != words.end()) {
                auto nextString = s.substr(i+1);
                auto found = helper(nextString);
                DP[nextString] = found;
                if (found) return true;
            }
        }

        return false;
    }

    // A straightforward DP solution with caching
    // At each position i, if the substring up to i is a word, check for the substring starting from i+1
    bool wordBreak(string s, vector<string>& wordDict) {
        set<string> W(wordDict.begin(), wordDict.end());
        words = W;
        return helper(s);
    }

    // A more efficient reverse DP
    // Starting from i=0, check if the substring up to i passes the check
    // Utilize DP by checking positions j less than i. if j valid, just check if substring from j to i is a word
    // After done, just return check(s.size())
    bool wordBreak2(string s, vector<string>& wordDict) {
        set<string> W(wordDict.begin(), wordDict.end());
        words = W;

        vector<bool> DP(s.size()+1, false);
        DP[0] = true; // interpret DP[i] as whether the substring ending just before position i passes the check

        for (auto i=1; i<=s.size(); i++) { // interpret i as the ending index position of the substring to check
            for (auto j=i-1; j>=0; j--) { // interpret j as the starting index position of the substring to check 
                if (DP[j]) { // only if the substring up to position j passes the check, then we bother to proceed
                    auto nextStr = s.substr(j, i-j);
                    // cout << "nextStr is " << nextStr << endl;
                    if (words.find(nextStr) != words.end()) { // find 1 valid word = position i is valid
                        DP[i] = true;
                        break;
                    }
                }
            }
        }

        return DP[s.size()];
    }
};


int main() {
    Solution *S = new Solution();
    vector<string> dict = {"leet", "code"};
    auto ans = S->wordBreak2("leetcode", dict);
    // vector<string> dict = {"cats", "dogs", "sand", "and", "cat"};
    // auto ans = S->wordBreak2("catsandog", dict);
    cout << "answer is " << ans << endl;
}
