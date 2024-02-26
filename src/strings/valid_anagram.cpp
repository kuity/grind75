#include <iostream>
#include <unordered_map>

using namespace std;


class Solution {
public:
    bool isAnagram(string s, string t) {
	unordered_map<char, int> cmap;
	for (char c: s) {
	    if (cmap.find(c) != cmap.end()) {
		cmap[c]++;
	    } else {
		cmap[c] = 1;
	    }
	}

	for (char b: t) {
	    if (cmap.find(b) != cmap.end()) {
		cmap[b]--;
		if (cmap[b] == 0) {
		    cmap.erase(b);
		}
	    } else {
		return false;
	    }
	}

	return cmap.size() == 0;
    }
};

int main() {
    string s = "anagram";
    string t = "nagaram";
    Solution *S = new Solution();
    cout << S->isAnagram(s, t) << endl;

    string s1 = "rat";
    string t1 = "car";
    cout << S->isAnagram(s1, t1) << endl;
}
