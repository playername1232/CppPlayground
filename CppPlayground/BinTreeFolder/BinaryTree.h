#pragma once
#include "../Utilities/MacroUtility/CustomMacros.h"

template <typename T>
class BinaryTree
{
private:
    BinaryTree* Parent     = nullptr;
    BinaryTree* LeftChild  = nullptr;
    BinaryTree* RightChild = nullptr;

    T Value;
    
    void AddLeftItem(BinaryTree* item, bool bFreeCurrent);
    void AddRightItem(BinaryTree* item, bool bFreeCurrent);

public:
    BinaryTree();
    BinaryTree(BinaryTree* parent, T item);
    
    void CountItself(int& counter);
    
    bool DeleteLeftItem();
    bool DeleteRightItem();

    int ProcessGetDepth(int depth);
};