#include <iostream>
#include <stack>

using namespace std;

/*
Link: https://leetcode.com/problems/implement-queue-using-stacks/
Difficulty: Easy
Topics: stack, design, queue
*/
class MyQueue {
private:
    stack<int> *ready;
    stack<int> *temp;

public:
    MyQueue() {
	ready = new stack<int>;
	temp = new stack<int>;
    }
    
    void push(int x) {
	while(!ready->empty()) {
	    int y = ready->top();
	    temp->push(y);
	    ready->pop();
	}
	ready->push(x);
	while(!temp->empty()) {
	    int y = temp->top();
	    ready->push(y);
	    temp->pop();
	}
    }
    
    int pop() {
	int x = ready->top();
	ready->pop();
	return x;
    }
    
    int peek() {
	return ready->top();
    }
    
    bool empty() {
	return ready->empty();
    }
};

int main() {
    MyQueue *q = new MyQueue();
    cout << "pushing 1" << endl;
    q->push(1);
    cout << "pushing 2" << endl;
    q->push(2);
    cout << "peeking" << endl;
    cout << "saw: " << q->peek() << endl;
    cout << "popping" << endl;
    cout << "popped " <<  q->pop() << endl;
    cout << "is empty? " << q->empty() << endl;
}
