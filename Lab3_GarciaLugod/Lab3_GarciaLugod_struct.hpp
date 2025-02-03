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