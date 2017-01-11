//
//  BinTree.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/9.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "BinTree.hpp"
#include "Release.hpp"
//#include <>

template <typename T>
int BinTree<T>::updateHeight(BinNode<T> *x) {
    return x->height +=  std::max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNode<T> *x) {
    while (x) {
        updateHeight(x);
        x = x->parent;
    }
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
    _size = 1;
   _root = new BinNode(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsLC(e);
    updateHeightAbove(x);
    return x->lc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNode<T> *x, T const &e) {
    _size++;
    x->insertAsRC(e);
    updateHeightAbove(x);
    return x->rc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNode<T> *x, BinTree<T> *&T)
{
    if(x->lc = T->_root) x->lc->parent = x;
    _size += T->size();
    updateHeightAbove(x);
    T->_root = nullptr;
    T->_size = 0;
    release(T);
    T = nullptr;
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNode<T> *x, BinTree<T> *&T)
{
    if (x->rc = T->_root) x->lc->parent = x;
    _size += T->size();
    updateHeightAbove(x);
    T->_root = nullptr;
    T->_size = 0;
    release(T);
    T = nullptr;
    return x;
}

template <typename T>
static int removeAt(BinNode<T>* x)
{
    if (!x) return 0;
    int n = 1;
    if (x->lc) n += removeAt(x->lc);
    if (x->rc) n += removeAt(x->rc);
    release(x->data); release(x);
    return n;
}

template <typename T>
int BinTree<T>::remove(BinNode<T> *x) {
    FromParentTo(*x) = nullptr;
    updateHeightAbove(x->parent);
    int n = removeAt(x); // ==> x.size()
    _size -= n;
    return n;
}



template <typename T>
BinTree<T>* BinTree<T>::secede(BinNode<T> *x) {
    if (x->parent) {
        FromParentTo(*x) = nullptr;
        updateHeightAbove(x->parent);
        x->parent = nullptr;
    }

    auto tree = new BinTree<T>();
    tree->_root = x;
    tree->_size = x->size();
    _size -= tree->_size;
    return tree;
}
