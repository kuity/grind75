#include <unordered_map>
#include <queue>
#include "../../lib/Node.h"

using namespace std;

/*
Link: https://leetcode.com/problems/clone-graph/description/
Difficulty: Medium
Topics: hashtable, dfs, bfs, graph
*/
class Solution {
private:
    // maybe this need to be a hashmap
    unordered_map<int, Node *> cloneMap;
    queue<Node *> v;

public:
    void cloneNode(Node* node) {
        Node *clone = new Node(node->val);
        cloneMap[node->val] = clone;
        for (auto n: node->neighbors) {
            if (cloneMap.find(n->val) != cloneMap.end()) {
                clone->neighbors.push_back(cloneMap[n->val]);
            } else {
                cloneNode(n);
                clone->neighbors.push_back(cloneMap[n->val]);
            }
        }
    }


    Node* cloneGraph(Node* node) {
        if (node!=nullptr) {
            int rootval = node->val;
            cloneNode(node);
            return cloneMap[rootval];
        } else {
            return nullptr;
        }
    }
};

int main() {
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);
    n1->neighbors = {n2, n4};
    n2->neighbors = {n1, n3};
    n3->neighbors = {n2, n4};
    n4->neighbors = {n1, n3};
    Solution *S = new Solution();
    Node * n1Clone = S->cloneGraph(n1);
    printAdjacency(n1);
    printAdjacency(n1Clone);
}
