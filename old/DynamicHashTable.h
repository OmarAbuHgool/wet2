#ifndef DYNAMICHASHTABLE_H
#define DYNAMICHASHTABLE_H
#include "stdio.h"
#include "AVLTree.h"
#include "Record.h"
#define N 11
class DynamicHashTable
{

private:
    AVLTree **array;
    int size;
    int capacity;
    int hashFunction(int id);
    void multiLength();
    void traverseAndInsert(Node *root, AVLTree **newArray, int newCapacity);

public:
    DynamicHashTable();
    ~DynamicHashTable();
    Customer *find(int id);
    int insertToHash(Customer *customer);
    void iterateOverAllNodesZeroDebt();
    static void zeroDebt(Node *root);
};
#endif