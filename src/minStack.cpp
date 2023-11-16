#include <iostream>
#include <stack>

using namespace std;

struct Patty {
    Patty* prevPatty;
    int val;

    Patty(Patty* prev, int v) : prevPatty(prev), val(v) {}
};

class MinStack {
public:
    stack<Patty *> stacker;
    Patty * minPatty;

    MinStack() {
	stacker = stack<Patty *>();
	minPatty = nullptr;
    }
    
    void push(int val) {
	Patty *newPatty = new Patty(nullptr, val);
	if (minPatty == nullptr) {
	    minPatty = newPatty;
	} else {
	    if (minPatty->val > newPatty->val) {
		newPatty->prevPatty = minPatty;
		minPatty = newPatty;
	    }
	}

	stacker.push(newPatty);
    }
    
    void pop() {
	Patty* nxt = stacker.top();
	if (nxt == minPatty) {
	    minPatty = minPatty->prevPatty;
	} 
	stacker.pop();
    }
    
    int top() {
	return stacker.top()->val;
    }
    
    int getMin() {
	return minPatty->val;
    }
};

int main() {
    MinStack *m = new MinStack();
    cout << "pushing -2" << endl;
    m->push(-2);
    cout << "pushing 0" << endl;
    m->push(0);
    cout << "pushing -3" << endl;
    m->push(-3);
    cout << "min is " << m->getMin() << endl;
    cout << "popping" << endl;
    m->pop();
    cout << "top is " << m->top() << endl;
    cout << "min is " << m->getMin() << endl;
}
