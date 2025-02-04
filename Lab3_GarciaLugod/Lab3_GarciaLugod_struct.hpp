// I hereby attest to the truth of the following facts:
// I have not discussed the c++ code in my program with anyone other than my instructor or the teaching assistants assigned to this course.
// I have not used c++ code obtained from another student, or any other unauthorized source, whether modified or unmodified.
// If any c++ code or documentation used in my program was obtained from another source, it has been clearly noted with citations in the comments of my program.

struct IntNode
{
    int val;
    IntNode *nextNode;

    IntNode(int val, IntNode *nextNode)
    {
        this->val = val;
        this->nextNode = nextNode;
    }
};