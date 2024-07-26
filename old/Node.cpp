#include "Node.h"

Node::Node(Customer *object, int key)
{
    this->key = key;
    this->height = 0;
    this->data = object;
    this->leftSon = nullptr;
    this->rightSon = nullptr;
    this->parent = nullptr;
}

//-------------------------------------------------------

Node::~Node()
{
}

//-------------------------------------------------------

void Node::destroy(Node *node, bool withData)
{
    if (node != nullptr)
    {
        destroy(node->leftSon, withData);
        destroy(node->rightSon, withData);
        if (withData && node->data != nullptr)
        {
            delete node->data;
            node->data = nullptr;
        }
        delete node;
        node = nullptr;
    }
}

//-------------------------------------------------------

void Node::swapNodes(Node &node1, Node &node2)
{
    Node temp = node1;
    node1.data = node2.data;
    node1.key = node2.key;
    node2.data = temp.data;
    node2.key = temp.key;
}

//-------------------------------------------------------

int Node::balanceFactor()
{

    if (this->leftSon == nullptr && this->rightSon == nullptr)
    {
        return 0;
    }
    if (this->rightSon == nullptr)
    {
        return this->leftSon->height + 1;
    }
    if (this->leftSon == nullptr)
    {
        return -(this->rightSon->height + 1);
    }
    return (this->leftSon->height - this->rightSon->height);
}

//-------------------------------------------------------

bool Node::isBalanced()
{
    int BF = this->balanceFactor();
    return BF <= 1 && BF >= -1;
}

//-------------------------------------------------------

int Node::calcHeight(Node *node)
{

    if (node->leftSon && node->rightSon)
    {
        if (node->leftSon->height < node->rightSon->height)
            return node->rightSon->height + 1;
        else
            return node->leftSon->height + 1;
    }
    else if (node->leftSon && node->rightSon == NULL)
    {
        return node->leftSon->height + 1;
    }
    else if (node->leftSon == NULL && node->rightSon)
    {
        return node->rightSon->height + 1;
    }
    return 0;
}

//-------------------------------------------------------

void Node::updatePrizesRotation(Node *root, int rotationCode)
{
    int tempLeftPrize = 0, tempRightPrize = 0, tempRootPrize = root->data->getPrizes();
    if (root->leftSon)
        tempLeftPrize = root->leftSon->data->getPrizes();
    if (root->rightSon)
        tempRightPrize = root->rightSon->data->getPrizes();
    switch (rotationCode)
    {
    case 0: // LL

        root->leftSon->data->setPrizes(root->leftSon->data->getPrizes() + root->data->getPrizes());
        root->data->setPrizes(-tempLeftPrize);
        if (root->leftSon && root->leftSon->rightSon)
            root->leftSon->rightSon->data->setPrizes(root->leftSon->rightSon->data->getPrizes() + tempLeftPrize);

        break;
    case 1: // RR
        root->rightSon->data->setPrizes(root->rightSon->data->getPrizes() + root->data->getPrizes());
        root->data->setPrizes(-tempRightPrize);
        if (root->rightSon && root->rightSon->leftSon)
            root->rightSon->leftSon->data->setPrizes(root->rightSon->leftSon->data->getPrizes() + tempRightPrize);
        break;
    case 2: // LR
        if (root->leftSon && root->leftSon->rightSon && root->leftSon->rightSon->leftSon)
            root->leftSon->rightSon->leftSon->data->setPrizes(root->leftSon->rightSon->leftSon->data->getPrizes() + root->leftSon->rightSon->data->getPrizes());
        if (root->leftSon && root->leftSon->rightSon && root->leftSon->rightSon->rightSon)
            root->leftSon->rightSon->rightSon->data->setPrizes(root->leftSon->rightSon->rightSon->data->getPrizes() + root->leftSon->rightSon->data->getPrizes() + tempLeftPrize);
        root->leftSon->data->setPrizes(-root->leftSon->rightSon->data->getPrizes());
        root->data->setPrizes(-root->leftSon->rightSon->data->getPrizes() - tempLeftPrize);
        if (root->leftSon && root->leftSon->rightSon)
            root->leftSon->rightSon->data->setPrizes(root->leftSon->rightSon->data->getPrizes() + tempRootPrize + tempLeftPrize);

        break;
    case 3: // RL
        if (root->rightSon && root->rightSon->leftSon && root->rightSon->leftSon->rightSon)
            root->rightSon->leftSon->rightSon->data->setPrizes(root->rightSon->leftSon->rightSon->data->getPrizes() + root->rightSon->leftSon->data->getPrizes());
        if (root->rightSon && root->rightSon->leftSon && root->rightSon->leftSon->leftSon)
            root->rightSon->leftSon->leftSon->data->setPrizes(root->rightSon->leftSon->leftSon->data->getPrizes() + root->rightSon->leftSon->data->getPrizes() + tempRightPrize);
        root->rightSon->data->setPrizes(-root->rightSon->leftSon->data->getPrizes());
        root->data->setPrizes(-root->rightSon->leftSon->data->getPrizes() - tempRightPrize);
        if (root->rightSon && root->rightSon->leftSon)
            root->rightSon->leftSon->data->setPrizes(root->rightSon->leftSon->data->getPrizes() + tempRootPrize + tempRightPrize);

        break;
    }
}

//-------------------------------------------------------
//rotations

void Node::RR()
{
    updatePrizesRotation(this, 1);
    Node::swapNodes(*this, *(this->rightSon));
    Node *temp = this->rightSon;
    this->rightSon = temp->rightSon;
    temp->rightSon->parent = this;
    Node *L = this->leftSon;
    this->leftSon = temp;
    temp->parent = this;
    Node *tempL = temp->leftSon;
    temp->leftSon = L;
    if (L)
        L->parent = temp;
    temp->rightSon = tempL;
    if (tempL)
        tempL->parent = temp;
    temp->height = calcHeight(temp);
    this->rightSon->height = calcHeight(this->rightSon);
    this->height = calcHeight(this);
}

//-------------------------------------------------------

void Node::RL()
{
    updatePrizesRotation(this, 3);
    Node *tempR = this->rightSon;
    Node *tempRL = tempR->leftSon;
    tempR->leftSon = tempRL->rightSon;
    if (tempRL->rightSon)
    {
        tempRL->rightSon->parent = tempR;
    }
    Node::swapNodes(*this, *tempRL);
    Node *tempL = this->leftSon;
    this->leftSon = tempRL;
    tempRL->parent = this;
    tempRL->rightSon = tempRL->leftSon;
    if (tempRL->leftSon)
    {
        tempRL->leftSon->parent = tempRL;
    }
    tempRL->leftSon = tempL;
    if (tempL)
    {
        tempL->parent = tempRL;
    }
    tempRL->height = calcHeight(tempRL);
    tempR->height = calcHeight(tempR);
    this->height = calcHeight(this);
}

//-------------------------------------------------------

void Node::LL()
{
    updatePrizesRotation(this, 0);
    Node::swapNodes(*this, *(this->leftSon));
    Node *temp = this->leftSon;
    this->leftSon = temp->leftSon;
    temp->leftSon->parent = this;
    Node *R = this->rightSon;
    this->rightSon = temp;
    temp->parent = this;
    Node *tempR = temp->rightSon;
    temp->rightSon = R;
    if (R)
        R->parent = temp;
    temp->leftSon = tempR;
    if (tempR)
        tempR->parent = temp;
    temp->height = calcHeight(temp);
    this->leftSon->height = calcHeight(this->leftSon);
    this->height = calcHeight(this);
}

//-------------------------------------------------------

void Node::LR()
{
    updatePrizesRotation(this, 2);
    Node *tempL = this->leftSon;       // pointing at A
    Node *tempLR = tempL->rightSon;    // pointing at B
    tempL->rightSon = tempLR->leftSon; // A's right son is Bl
    if (tempLR->leftSon)
    {
        tempLR->leftSon->parent = tempL; // Bl's father is A
    }
    Node::swapNodes(*this, *tempLR);    // changing between C and B
    Node *tempR = this->rightSon;       // pointing at Cr
    this->rightSon = tempLR;            // B's right son is C
    tempLR->parent = this;              // C's father is B
    tempLR->leftSon = tempLR->rightSon; // C's left son is Br
    if (tempLR->rightSon)
    {
        tempLR->rightSon->parent = tempLR; // Br's father is C
    }
    tempLR->rightSon = tempR; // C's right son is Cr
    if (tempR)
    {
        tempR->parent = tempLR; // Cr's parent is C
    }
    tempLR->height = calcHeight(tempLR);
    tempL->height = calcHeight(tempL);
    this->height = calcHeight(this) - 1;
}

//-------------------------------------------------------

int Node::getExpensesHelper(int id)
{
    int sumPrizes = 0;
    if (!this || this->key == -1)
    {
        return -1;
    }
    Node *tempNode = this;
    while (tempNode != nullptr)
    {
        if (tempNode->data->getId() == id)
        {
            break;
        }
        if (id > tempNode->data->getId() && tempNode->rightSon)
        {
            sumPrizes += tempNode->data->getPrizes();
            tempNode = tempNode->rightSon;
            continue;
        }
        if (tempNode->leftSon && id < tempNode->data->getId())
        {
            sumPrizes += tempNode->data->getPrizes();
            tempNode = tempNode->leftSon;
            continue;
        }
        break;
    }
    if (tempNode->data->getId() == id)
    {
        return sumPrizes;
    }
    return -1; // didnt find it
}

//-------------------------------------------------------

Node *Node::findCommonFather(Node *root, int key1, int key2)
{
    if (root == nullptr)
        return nullptr;

    if (key1 < root->key && key2 < root->key)
        return findCommonFather(root->leftSon, key1, key2);

    if (key1 > root->key && key2 > root->key)
        return findCommonFather(root->rightSon, key1, key2);

    return root;
}