#include "AVLTree.h"

bool AVLTree::addPrizesHelper(int c_id1, int c_id2, double amount)
{
    Node *customer1 = AVLTree::Travel(this->root, c_id1);
    if (!customer1)
    {
        return true;
    }
    if (customer1->key < c_id1 && customer1->parent)
    {
        customer1 = customer1->parent;
    }
    Node *customer2 = AVLTree::Travel(this->root, c_id2);
    if (!customer2)
    {
        return true;
    }
    if (customer2 && customer2->key > c_id2 && customer2->parent)
    {
        customer2 = customer2->parent;
    }

    Node *commonFather = this->root->findCommonFather(this->root, customer1->key, customer2->key);
    Node *tempNode = commonFather;
    int sumOfPrizes = 0;

    // ALGORITHM UNTIL C_ID2
    if (tempNode && tempNode->data->getId() >= c_id1 && tempNode->data->getId() <= c_id2)
    {
        while (1)
        {
            if (tempNode == nullptr)
            {
                break;
            }
            if (tempNode->data->getId() < c_id2)
            {
                if (sumOfPrizes == 0)
                {
                    tempNode->data->setPrizes(tempNode->data->getPrizes() + amount);
                    sumOfPrizes += amount;
                }
                tempNode = tempNode->rightSon;
                continue;
            }
            if (sumOfPrizes != 0)
            {
                tempNode->data->setPrizes(tempNode->data->getPrizes() - amount);
                sumOfPrizes -= amount;
            }

            tempNode = tempNode->leftSon;
        }
        tempNode = commonFather;
        sumOfPrizes = 0;
        while (tempNode != nullptr)
        {
            if (tempNode->data->getId() < c_id1)
            {
                if (sumOfPrizes == 0)
                {
                    tempNode->data->setPrizes(tempNode->data->getPrizes() - amount);
                    sumOfPrizes -= amount;
                }

                tempNode = tempNode->rightSon;
                continue;
            }
            else
            {
                if (sumOfPrizes == amount * -1)
                {
                    sumOfPrizes += amount;
                    tempNode->data->setPrizes(tempNode->data->getPrizes() + amount);
                }
            }
            tempNode = tempNode->leftSon;
        }
    }

    return true;
}

//-------------------------------------------------------

AVLTree::AVLTree(Node *root) : root(root) {}

//-------------------------------------------------------

AVLTree::~AVLTree()
{
    if (root)
    {
        Node::destroy(root, true);
        this->root = nullptr;
    }
    else
    {
        Node::destroy(root, false);
        delete this->root;
        this->root = nullptr;
    }
}

//-------------------------------------------------------

int AVLTree::insertNode(Customer *object, int key)
{
    if (this->root == nullptr)
    {
        this->root = new Node(new Customer(object), key);
        return true;
    }
    if (this->root->key == -1)
    {
        this->root->data = new Customer(object);
        this->root->key = key;
        return true;
    }
    Node *tempNode = root;
    tempNode = Travel(tempNode, key);
    if (tempNode->key == key)
    {
        return -2;
    }
    Node *newNode = new Node(new Customer(object), key);
    if (newNode == nullptr)
    {
        throw std::bad_alloc();
    }
    if (key > tempNode->key)
    {
        tempNode->rightSon = newNode;
    }
    else if (key < tempNode->key)
    {
        tempNode->leftSon = newNode;
    }
    else
    {
        delete newNode;
        delete object;
        return -2;
    }
    newNode->parent = tempNode;
    // rotation
    Node *parentNode = newNode->parent;
    int rotation = -1;
    while (newNode != root)
    {
        parentNode = newNode->parent;
        if (parentNode->height > newNode->height)
        {
            break;
        }
        parentNode->height = newNode->height + 1;
        if (!parentNode->isBalanced())
        {
            rotation = Rotate(parentNode);
        }
        newNode = parentNode;
    }
    return rotation;
}

//-------------------------------------------------------

bool AVLTree::deleteNode(int key, bool deleteData)
{
    if (root->key == key && !root->leftSon && !root->rightSon)
    {
        if (deleteData)
            delete root->data;
        delete root;
        this->root = nullptr;
        return true;
    }
    Node *tempNode = root;
    tempNode = Travel(tempNode, key);
    if (tempNode->key != key)
    {
        return false;
    }
    Node *parentNode = tempNode->parent;
    int tempHeight = 0;
    for (int i = 0; i < 2; i++)
    {
        if (tempNode->leftSon == nullptr && tempNode->rightSon == nullptr)
        {
            if (parentNode == nullptr)
            {
                if (deleteData)
                {
                    delete tempNode->data;
                }
                delete tempNode;
                tempNode = nullptr;
                return true;
            }
            if (tempNode == parentNode->rightSon)
            {
                if (deleteData)
                {
                    delete tempNode->data;
                }
                delete tempNode;
                tempNode = nullptr;
                parentNode->rightSon = nullptr;
            }
            else
            {
                if (deleteData)
                {
                    delete tempNode->data;
                }
                delete tempNode;
                tempNode = nullptr;
                parentNode->leftSon = nullptr;
            }
            break;
        }
        else
        {
            if (tempNode->rightSon == nullptr && parentNode != nullptr)
            {
                if (tempNode == parentNode->rightSon)
                {
                    tempNode->parent->rightSon = tempNode->leftSon;
                    tempNode->leftSon->parent = tempNode->parent;

                    if (deleteData)
                    {
                        delete tempNode->data;
                    }
                    delete tempNode;
                }
                else
                {
                    tempNode->parent->leftSon = tempNode->leftSon;
                    tempNode->leftSon->parent = tempNode->parent;
                    if (deleteData)
                    {
                        delete tempNode->data;
                    }
                    delete tempNode;
                }
                tempNode = nullptr;
                break;
            }
            else if (tempNode->leftSon == nullptr)
            {
                if (parentNode == nullptr)
                {
                    Node::swapNodes(*tempNode, *tempNode->rightSon);
                    if (deleteData)
                    {
                        delete tempNode->rightSon->data;
                    }
                    delete tempNode->rightSon;
                    tempNode->rightSon = nullptr;
                    return true;
                }
                else if (tempNode == parentNode->rightSon)
                {
                    tempNode->parent->rightSon = tempNode->rightSon;
                    tempNode->rightSon->parent = tempNode->parent;
                    if (deleteData)
                    {
                        delete tempNode->data;
                    }
                    delete tempNode;
                }
                else
                {
                    tempNode->parent->leftSon = tempNode->rightSon;
                    tempNode->rightSon->parent = tempNode->parent;
                    if (deleteData)
                    {
                        delete tempNode->data;
                    }
                    delete tempNode;
                }

                tempNode = nullptr;
                break;
            }
            else
            {
                Node *nextNodeInorder = nextNodeInOrderFunction(tempNode);
                Node::swapNodes(*nextNodeInorder, *tempNode);
                parentNode = nextNodeInorder->parent;
                tempNode = nextNodeInorder;
            }
        }
    }
    int rotation = -1;
    while (1)
    {
        tempHeight = parentNode->height;
        parentNode->height = parentNode->calcHeight(parentNode);
        if (!parentNode->isBalanced())
        {
            rotation = Rotate(parentNode);
        }
        if (tempHeight == parentNode->height)
        {
            break;
        }
        if (parentNode == root)
        {
            break;
        }
        parentNode = parentNode->parent;
    }
    return rotation;
}

//-------------------------------------------------------

bool AVLTree::isEmpty()
{
    return root == nullptr || root->key == -1;
}

//-------------------------------------------------------

int AVLTree::Rotate(Node *node)
{
    if (node->balanceFactor() == 2)
    {
        if (node->leftSon->balanceFactor() >= 0)
        {
            node->LL();
            return 0;
        }
        node->LR();
        return 2;
    }
    if (node->balanceFactor() == -2)
    {
        if (node->rightSon->balanceFactor() <= 0)
        {
            node->RR();
            return 1;
        }
        node->RL();
        return 3;
    }
    return -1;
}

//-------------------------------------------------------

Node *AVLTree::Travel(Node *tempNode, int key)
{
    while (tempNode != nullptr)
    {
        if (tempNode->key == key)
        {
            break;
        }
        if (key > tempNode->key && tempNode->rightSon)
        {
            tempNode = tempNode->rightSon;
            continue;
        }
        if (tempNode->leftSon && key < tempNode->key)
        {
            tempNode = tempNode->leftSon;
            continue;
        }
        break;
    }
    return tempNode;
}

//-------------------------------------------------------

Node *AVLTree::nextNodeInOrderFunction(Node *tempNode)
{
    if (tempNode->rightSon)
    {
        tempNode = tempNode->rightSon;
    }
    while (tempNode->leftSon != nullptr)
    {
        tempNode = tempNode->leftSon;
    }
    return tempNode;
}
