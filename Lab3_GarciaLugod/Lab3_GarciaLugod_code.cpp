// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.
#include <iostream>
#include "Lab3_GarciaLugod_struct.hpp"
using namespace std;

void linkedListDemo()
{
    cout << "Linked list demo" << endl;
    // create linked list
    cout << "Length of linked list: ";
    int len;
    cin >> len;
    IntNode *prevNode = nullptr;
    for (int i = 0; i < len; i++)
    {
        int val;
        cout << "Value of node " << i + 1 << ": ";
        cin >> val;

        IntNode *node = new IntNode(val, prevNode);
        prevNode = node;
    }

    // traverse linked list
    IntNode *topNode = prevNode;
    if (len > 0)
        cout << "Value of nodes from top of linked list: ";
    while (topNode != nullptr)
    {
        cout << topNode->val << " ";
        // delete current node and get next node
        IntNode *nextNode = topNode->nextNode;
        delete topNode;
        topNode = nullptr;
        topNode = nextNode;
    }
    cout << endl;
}

void stackDemo()
{
    cout << "Stack demo" << endl;
    IntStack *stack = new IntStack();
    string action;
    do
    {
        cout << "Action (push/pop/stop): ";
        cin >> action;
        if (action == "push")
        {
            int val;
            cout << "Value: ";
            cin >> val;
            stack->push(val);
        }
        else if (action == "pop")
        {
            if (stack->head == nullptr)
            {
                cout << "Empty stack" << endl;
            }
            else
            {
                cout << "Popped value: " << stack->pop() << endl;
            }
        }
        else
        {
            cout << "Undefined action" << endl;
        }
    } while (action != "stop");
    delete stack;
}

int main(void)
{
    linkedListDemo();
    stackDemo();
    return 0;
}