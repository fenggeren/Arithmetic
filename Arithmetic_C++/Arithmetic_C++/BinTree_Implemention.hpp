//
//  BinTree.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/9.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "BinTree.hpp"
#include "Release.hpp"

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
BinNodePosi(T) BinTree<T>::insertAsLC(BinNode<T> *x, BinTree<T> *&T) {
    if(x->)
    _size += T->size();
    updateHeightAbove(T->root());
    release(T->_root);
    T->_root = nullptr;
    T->_size = 0;
    return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNode<T> *x, BinTree<T> *&T) {
    _size += T->size();
    x->insertAsRC(T->size());
}
