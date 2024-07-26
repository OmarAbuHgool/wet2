#include "Customer.h"
class Node
{
public:
    Node(Customer *object, int key);
    ~Node();
    static void destroy(Node *node, bool withData);
    bool isBalanced();
    int balanceFactor();
    int calcHeight(Node *node);
    void RR();
    void RL();
    void LL();
    void LR();
    Node &operator=(Node other);
    Node *findCommonFather(Node *root, int key1, int key2);
    void updatePrizesRotation(Node *root, int rotationCode);
    int getExpensesHelper(int id);
    static void swapNodes(Node &node1, Node &node2);

    //fields
    int key;
    int height;
    Customer *data;
    Node *leftSon;
    Node *rightSon;
    Node *parent;
};