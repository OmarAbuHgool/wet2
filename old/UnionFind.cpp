#include "UnionFind.h"

int *UnionFind::getSize()
{
    return this->size;
}

//-------------------------------------------------------

Record **UnionFind::getParent()
{
    return this->parent;
}

//-------------------------------------------------------

int *UnionFind::getHeightOfPile()
{
    return this->totalHeightOfPile;
}

//-------------------------------------------------------

UnionFind::UnionFind(int numOfElements, Record *recordsArr[])
{
    parent = new Record *[numOfElements];
    size = new int[numOfElements];
    totalHeightOfPile = new int[numOfElements];
    this->numOfElements = numOfElements;
    this->recordsArr = recordsArr;

    for (int i = 0; i < numOfElements; ++i)
    {
        recordsArr[i]->setColumn(i);
        parent[i] = recordsArr[i];
        size[i] = 1;
        totalHeightOfPile[i] = recordsArr[i]->getNumInStock();
    }
}

//-------------------------------------------------------

UnionFind::~UnionFind()
{
    delete[] parent;
    delete[] size;
    delete[] totalHeightOfPile;
}

//-------------------------------------------------------

Record *UnionFind::find(int x, int *sum)
{
    Record *res = parent[x];
    if (parent[x]->getId() != x)
    {
        if (sum)
            *sum += recordsArr[x]->getHeight();
        res = find(parent[x]->getId(), sum); // path compression
    }
    if (sum && res && res->getId() == x)
    {
        *sum += recordsArr[x]->getHeight();
    }
    return res;
}

//-------------------------------------------------------

bool UnionFind::unionSets(int x, int y)
{
    Record *rootX = find(x);
    Record *rootY = find(y);

    if (rootX->getId() != rootY->getId())
    {
        if (size[rootX->getId()] < size[rootY->getId()])
        {
            parent[rootX->getId()] = rootY;
            size[rootY->getId()]++;
            totalHeightOfPile[rootY->getColumn()] += totalHeightOfPile[rootX->getColumn()];
            return true;
        }
        else if (size[rootX->getId()] > size[rootY->getId()])
        {
            parent[rootY->getId()] = rootX;
            size[rootY->getId()]++;
            totalHeightOfPile[rootY->getColumn()] += totalHeightOfPile[rootX->getColumn()];
            return false;
        }
        else
        {
            parent[rootY->getId()] = rootX;
            size[rootX->getId()]++;
            totalHeightOfPile[rootY->getColumn()] += totalHeightOfPile[rootX->getColumn()];
            return false;
        }
    }
    return true;
}