#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/design-add-and-search-words-data-structure/
Difficulty: Medium
Topics: 
*/
class WordDictionary {
public:
    // It's just a slightly modified trie
    // The dict looks like this: { nullptr nullptr nullptr Trie* Trie* nullptr ... }
    // Optimization: cache some searches
    vector<WordDictionary*> children;
    WordDictionary() {
        children = vector<WordDictionary *>(27, nullptr);
    }
    
    void addWord(string word) {
        if (word.length() == 0) {
            if (children[26] == nullptr) children[26] = new WordDictionary();
        } else {
            int val = word[0] - 'a';
            if (children[val] == nullptr) children[val] = new WordDictionary();
            children[val]->addWord(word.substr(1));
        }
    }
    
    bool search(string word) {
        if (word.length() == 0) return children[26] != nullptr;
        auto nextSearch = word.substr(1);
        if (word[0] == '.') {
            for (auto child: children) if (child != nullptr && child->search(nextSearch)) return true;
            return false;
        }
        int val = word[0] - 'a';
        return children[val] == nullptr ? false : children[val]->search(nextSearch);
    }
};

int main() {
    bool found;
    WordDictionary *D = new WordDictionary();
    D->addWord("bad");
    D->addWord("dad");
    D->addWord("mad");
    found = D->search("pad");
    cout << "pad is " << found << endl;

    found = D->search("bad");
    cout << "bad is " << found << endl;

    found = D->search(".ad");
    cout << ".ad is " << found << endl;

    found = D->search("b..");
    cout << "b.. is " << found << endl;
}
