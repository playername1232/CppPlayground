#include "BinaryTree.h"

template <typename T>
BinaryTree<T>::BinaryTree() { }

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree* parent, T item)
{
    this->Parent = parent;
    this->Value = item;
}

template <typename T>
void BinaryTree<T>::CountItself(int& counter)
{
    counter += 1;

    if(this->LeftChild != nullptr)
        this->LeftChild->CountItself(counter);
    if(this->RightChild != nullptr)
        this->RightChild->CountItself(counter);
}

template <typename T>
void BinaryTree<T>::AddLeftItem(BinaryTree* item, bool bFreeCurrent)
{
    if(item == nullptr)
        return;

    if(bFreeCurrent == true)
        free_heap(this->LeftChild);

    this->LeftChild = item;
}

template <typename T>
void BinaryTree<T>::AddRightItem(BinaryTree* item, bool bFreeCurrent)
{
    if(item == nullptr)
        return;

    if(bFreeCurrent == true)
        free_heap(this->RightChild);

    this->RightChild = item;
}

template <typename T>
bool BinaryTree<T>::DeleteLeftItem()
{
    if(this->LeftChild == nullptr)
        return false;

    this->LeftChild->DeleteLeftItem();
    this->LeftChild->DeleteRightItem();

    free_heap(this->LeftChild);
    this->LeftChild = nullptr;

    return true;
}

template <typename T>
bool BinaryTree<T>::DeleteRightItem()
{
    if(this->RightChild == nullptr)
        return false;

    this->RightChild->DeleteLeftItem();
    this->RightChild->DeleteRightItem();

    free_heap(this->RightChild);
    this-> RightChild = nullptr;

    return true;
}

template <typename T>
int BinaryTree<T>::ProcessGetDepth(int depth)
{
    depth += 1;
    
    int left  = 0,
        right = 0;

    
    if(this->LeftChild != nullptr)
        left = this->LeftChild->ProcessGetDepth(depth);
    if(this->RightChild != nullptr)
        right = this->RightChild->ProcessGetDepth(depth);

    return left != 0 || right != 0 ? (left > right ? left : right) : depth;
}