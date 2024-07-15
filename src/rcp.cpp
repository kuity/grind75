#include <iostream>

using namespace std;

struct Operator {
    string operation;
    int num1;
    int num2;
    Operator(string x, int y, int z) : operation(x), num1(y), num2(z) {}
};

class Calculator {
    vector<int> stack;
    vector<Operator *> operations;

public:
    void insert(int x) {
        stack.push_back(x);
        operations.push_back(new Operator("insert", 0, 0));
    }

    void process(string op) {
        cout << "Recevied operation " << op << endl;
        if (op == "add") {
            auto num1 = stack.back();
            stack.pop_back();
            auto num2= stack.back();
            stack.pop_back();
            stack.push_back(num1 + num2);
            operations.push_back(new Operator("add", num2, num1));
        } else if (op == "subtract") {
            auto num2 = stack.back();
            stack.pop_back();
            auto num1= stack.back();
            stack.pop_back();
            stack.push_back(num1 - num2);
            operations.push_back(new Operator("subtract", num1, num2));
        } else if (op == "undo") {
            auto lastOp = operations.back();
            operations.pop_back();
            unprocess(lastOp);
        }
    }

    void unprocess(Operator *op) {
        if (op->operation == "insert") {
            stack.pop_back();
        } else if (op->operation == "add") {
            stack.pop_back();
            stack.push_back(op->num1);
            stack.push_back(op->num2);
        } else if (op->operation == "subtract") {
            stack.pop_back();
            stack.push_back(op->num1);
            stack.push_back(op->num2);
        }
    }

    void display() {
        cout << "Current stack: ";
        for (auto x: stack) {
            cout << x << ",";
        }
        cout << endl;
    }
};


int main() {
    Calculator *S = new Calculator;
    S->insert(1);
    S->insert(2);
    S->insert(3);
    S->insert(4);
    S->display();
    S->process("undo");
    S->display();
    S->process("add");
    S->display();
    S->process("subtract");
    S->display();
    S->process("undo");
    S->display();
    S->process("undo");
    S->display();
    S->process("undo");
    S->display();
}
