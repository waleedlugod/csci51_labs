// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.
#include <iostream>
#include "Lab3_GarciaLugod_struct.hpp"
using namespace std;

int main(void)
{
    // bug: weird behavior when anything other than int is input (string, float)
    // might not need fix if specified int is required in readme (??)
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // demonstrate creation and traversal
    ////////////////////////////////////////////////////////////////////////////////////////////////

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
    cout << "Value of nodes from top of linked list: ";
    while (topNode != nullptr)
    {
        cout << topNode->val << " ";
        // get next node
        topNode = topNode->nextNode;
    }
}