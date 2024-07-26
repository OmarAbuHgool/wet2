#ifndef AVLTREE_H
#define AVLTREE_H
#include <stdio.h>
#include <iostream>

#include "Node.h"

class AVLTree
{
public:
    AVLTree(Node *root);
    ~AVLTree();
    int insertNode(Customer *object, int key);
    bool deleteNode(int key, bool deleteData = true);
    bool isEmpty();
    static Node *nextNodeInOrderFunction(Node *tempNode);
    static int Rotate(Node *node);
    static Node *Travel(Node *tempNode, int key);
    static void inorder(Node *t);
    bool addPrizesHelper(int c_id1, int c_id2, double amount);

    Node *root;
};


#endif