#include <iostream>
#include <vector>
#include <set>

using namespace std;

/*
Link: https://leetcode.com/problems/implement-trie-prefix-tree/description/
Difficulty: Medium
Topics: hashtable, trie, design, string
*/
class Trie {
public:
    vector<Trie*> children;
    Trie() {
	children = vector<Trie *>(27, nullptr);
    }
    
    void insert(string word) {
	if (word.length() == 0) {
	    children[26] = (children[26] == nullptr) ? new Trie() : children[26];
	} else {
	    int val = word[0] - 'a';
	    if (children[val] == nullptr) {
		children[val] = new Trie();
	    }
	    children[val]->insert(word.substr(1));
	}
    }
    
    bool search(string word) {
	if (word.length() == 0) {
	    return children[26] != nullptr;
	} else {
	    int val = word[0] - 'a';
	    if (children[val] == nullptr) {
		return false;
	    } else {
		return children[val]->search(word.substr(1));
	    }
	}
    }
    
    bool startsWith(string prefix) {
	if (prefix.length() == 0) {
	    return true;
	} else {
	    int val = prefix[0] - 'a';
	    if (children[val] == nullptr) {
		return false;
	    } else {
		return children[val]->startsWith(prefix.substr(1));
	    }
	}
    }
};

int main() {
    Trie *newTrie = new Trie();
    newTrie->insert("eff");
    bool found;
    found = newTrie->search("eff");
    cout << "eff is " << found << endl;
    found = newTrie->search("jeff");
    cout << "jeff is " << found << endl;
    newTrie->insert("effigy");
    found = newTrie->search("eff");
    cout << "eff is " << found << endl;
    found = newTrie->search("effigy");
    cout << "effigy is " << found << endl;
    found = newTrie->startsWith("ef");
    cout << "ef prefix is " << found << endl;
}
