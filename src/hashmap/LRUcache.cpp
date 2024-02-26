#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/lru-cache/
Difficulty: Medium
Topics: Hashtable, Linked list
*/
struct cacheNode {
    cacheNode *prev;
    cacheNode *next;
    int key;
    int value;

    cacheNode(int x, int y) : key(x), value(y), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, cacheNode*> C;
    int cap;
    int startKey;
    int endKey;

    // Case 1. updated key is LRU. Update LRU->next->prev, Update MRU->next, value, LRU MRU keys
    // Case 2. updated key is MRU. Update value and MRU key
    // Case 3. updated key is both LRU and MRU. Just update value and quit
    // Case 4. updated key is neither LRU nor MRU.
    void updateCache(int key, int value) {
	// cout << "updateCache key " << key << " value " << value << endl;
	auto foundNode = C[key];
	foundNode->value = value;

	// Case 3
	if (C.size() == 1) return;

	// Case 2: the updated Node is the MRU
	else if (C[key]->key == endKey) endKey = key;

	// Case 1: the updated Node is the LRU
	else if (C[key]->key == startKey) {
	    auto MRUNode = C[endKey];
	    auto nextNode = foundNode->next;
	    nextNode->prev = nullptr;
	    startKey = nextNode->key;
	    MRUNode->next = foundNode;
	    foundNode->prev = MRUNode;
	    foundNode->next = nullptr;
	    endKey = key;
	}

	// Case 4: Neither LRU nor MRU
	else {
	    auto MRUNode = C[endKey];
	    auto prevNode = foundNode->prev;
	    auto nextNode = foundNode->next;
	    prevNode->next = nextNode;
	    nextNode->prev = prevNode;
	    foundNode->prev = MRUNode;
	    foundNode->next = nullptr;
	    MRUNode->next = foundNode;
	    endKey = key;
	}
    }

public:
    LRUCache(int capacity) {
	cap = capacity;
	startKey = -1;
	endKey = -1;
    }
    
    int get(int key) {
	// cout << "getting key " << key << endl;
	if (C.find(key) != C.end()) {
	    auto val = C[key]->value;
	    updateCache(key, val);
	    return val; 
	} else return -1;
    }
    
    void put(int key, int value) {
	// If capacity 1, let's save ourselves some trouble
	if (cap == 1) {
	    C.clear();
	    C[key] = new cacheNode(key, value);
	    return;
	}
	
	// Not found key, add new key
	if (C.find(key) == C.end()) {
	    // cout << "Create new cachenode with value " << value << endl;
	    auto newNode = new cacheNode(key, value);
	    if (endKey > -1) {
		auto mruNode = C[endKey];
		newNode->prev = mruNode;
		mruNode->next = newNode;
	    }
	    endKey = key;
	    C[key] = newNode;

	    if (startKey == -1) startKey = key;

	    // Capacity exceeded, evict the LRU node
	    if (C.size() > cap) {
		auto lruNode = C[startKey];
		C.erase(startKey);
		startKey = lruNode->next->key;
		lruNode->next->prev = nullptr;
	    }
	}

	// Found key, update the found key
	else updateCache(key, value);
    }
};

// From leetcode solutions
// A clean and simple implementation using std list so do not need to re-implement linked list
class LRUCache2 {
    size_t m_capacity;
    unordered_map<int,  list<pair<int, int>>::iterator> m_map; //m_map_iter->first: key, m_map_iter->second: list iterator;
    list<pair<int, int>> m_list;

public:
    LRUCache2(size_t capacity): m_capacity(capacity) {}

    int get(int key) {
        auto found_iter = m_map.find(key);
        if (found_iter == m_map.end()) return -1;

        m_list.splice(m_list.begin(), m_list, found_iter->second); //move the node corresponding to key to front
        return found_iter->second->second; //return value of the node
    }

    void put(int key, int value) {
        auto found_iter = m_map.find(key);
        if (found_iter != m_map.end()) //key exists
        {
            m_list.splice(m_list.begin(), m_list, found_iter->second); //move the node corresponding to key to front
            found_iter->second->second = value;                        //update value of the node
            return;
        }

        if (m_map.size() == m_capacity) //reached capacity
        {
           int key_to_del = m_list.back().first; 
           m_list.pop_back();            //remove node in list;
           m_map.erase(key_to_del);      //remove key in map
        }

        m_list.emplace_front(key, value);  //create new node in list
        m_map[key] = m_list.begin();       //create correspondence between key and node
    }
};

int main() {
    int capacity = 2;
    int value;

    cout << "Testcase 1 " << endl;
    LRUCache* obj = new LRUCache(capacity);
    obj->put(1,1);
    obj->put(2,2);
    value = obj->get(1); cout << "Value is " << value << endl;
    obj->put(3,3);
    value = obj->get(2); cout << "Value is " << value << endl;
    obj->put(4,4);
    value = obj->get(1); cout << "Value is " << value << endl;
    value = obj->get(3); cout << "Value is " << value << endl;
    value = obj->get(4); cout << "Value is " << value << endl;


    cout << "Testcase 2 " << endl;
    LRUCache2 * obj2 = new LRUCache2(capacity);
    obj2->put(1,0);
    obj2->put(2,2);
    value = obj2->get(1); cout << "Value is " << value << endl;
    obj2->put(3,3);
    value = obj2->get(2); cout << "Value is " << value << endl;
    obj2->put(4,4);
    value = obj2->get(1); cout << "Value is " << value << endl;
    value = obj2->get(3); cout << "Value is " << value << endl;
    value = obj2->get(4); cout << "Value is " << value << endl;
}
