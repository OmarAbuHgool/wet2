#include "Record.h"
class UnionFind
{
private:
    Record **parent;
    Record **recordsArr;
    int *size;
    int *totalHeightOfPile;
    int numOfElements; //(AllTrees)

public:
    int *getSize();
    Record **getParent();
    int *getHeightOfPile();
    UnionFind(int numOfElements, Record *recordsArr[]);
    ~UnionFind();
    Record *find(int x, int *sum = nullptr);
    bool unionSets(int x, int y);
};