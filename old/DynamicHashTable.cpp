#include "stdio.h"
#include "DynamicHashTable.h"

DynamicHashTable::DynamicHashTable()
{
    capacity = N;
    size = 0;
    array = new AVLTree *[capacity];

    for (int i = 0; i < capacity; i++)
    {
        array[i] = new AVLTree(nullptr);
    }
}

//-------------------------------------------------------

DynamicHashTable::~DynamicHashTable()
{
    for (int i = 0; i < capacity; i++)
    {
        delete array[i];
    }

    delete[] array;
    size = 0;
    capacity = 0;
}

//-------------------------------------------------------

int DynamicHashTable::hashFunction(int id)
{
    return id % capacity;
}

//-------------------------------------------------------

Customer *DynamicHashTable::find(int id)
{
    if (array!=nullptr && array[hashFunction(id)] && array[hashFunction(id)]->root)
    {
        return array[hashFunction(id)]->Travel(array[hashFunction(id)]->root, id)->data;
    }
    return nullptr;
}

//-------------------------------------------------------

//this function multiply the hash table length
void DynamicHashTable::multiLength()
{
    int newCapacity = capacity * 2;
    AVLTree **newArray = new AVLTree *[newCapacity];

    for (int i = 0; i < newCapacity; i++)
    {
        newArray[i] = new AVLTree(nullptr);
    }

    for (int i = 0; i < capacity; i++)
    {
        Node *root = array[i]->root;
        traverseAndInsert(root, newArray, newCapacity);
        delete array[i];
    }

    delete[] array;

    array = newArray;
    capacity = newCapacity;
}

//-------------------------------------------------------

//a helper function that re-sort each customer to the new hash table
void DynamicHashTable::traverseAndInsert(Node *root, AVLTree **newArray, int newCapacity)
{
    if (root == nullptr)
    {
        return;
    }

    traverseAndInsert(root->leftSon, newArray, newCapacity);
    int newIndex = root->data->getId() % newCapacity;
    newArray[newIndex]->insertNode(root->data, root->data->getId());
    
    traverseAndInsert(root->rightSon, newArray, newCapacity);
}

//-------------------------------------------------------

int DynamicHashTable::insertToHash(Customer *customer)
{
    
    if (size >= capacity)
    {
        multiLength();
    }
    int index = hashFunction(customer->getId());
    int result = array[index]->insertNode(customer, customer->getId());
    if (result != -2)
    {
        size++;
    }
    return result;
}

//-------------------------------------------------------


void DynamicHashTable::iterateOverAllNodesZeroDebt()
{
    for (int i = 0; i < N; i++)
    {
        zeroDebt(array[i]->root);
    }
}

//-------------------------------------------------------

void DynamicHashTable::zeroDebt(Node *root)
{
    if (root == nullptr)
        return;
    zeroDebt(root->leftSon);
    root->data->setDebt(0);
    zeroDebt(root->rightSon);
}
