#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/top-k-frequent-words/
Difficulty: Medium
Topics: hashtable, string, trie, sorting, heap, bucket sort, counting
*/
class Solution {
public:
    // Although minheap or maxheap is very intuitive solution
    // need to write the custom comparator, which is very troublesome
    // This solution abuses the fact that words vector is capped at 500, 
    // Thus the highest frequency word is no more than 500
    // 
    // We can bucket words into a vector according to their frequency
    // Then sort each bucket if needed and append to the answer
    //
    // Consider: bucket + trie method?
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> M;
        int highest = 0;
        for (auto word: words) {
            M[word]++;
            highest = max(highest, M[word]);
        }
        vector<vector<string>> V(highest+1);
        for (auto kv: M) V[kv.second].push_back(kv.first);

        vector<string> ans;
        for (auto i=highest; i>=0; i--) {
            if (V[i].size() == 0) continue;
            sort(V[i].begin(), V[i].end());
            for (auto w: V[i]) {
                ans.push_back(w);
                if (--k == 0) return ans;
            }
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution;
    vector<string> W = {"i","love","leetcode","i","love","coding"};
    auto ans = S->topKFrequent(W, 2);
    for (auto w: ans) cout << w << ",";
    cout << endl;

    W = {"the","day","is","sunny","the","the","the","sunny","is","is"};
    ans = S->topKFrequent(W, 4);
    for (auto w: ans) cout << w << ",";
    cout << endl;
}
