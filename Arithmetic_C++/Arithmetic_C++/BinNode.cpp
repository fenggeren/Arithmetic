//
//  BinNode.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "BinNode.hpp"
#include "Binnode_macro_BASIC.h"

template <typename T>
int BinNode<T>::size()
{
    int s = 1;
    if (lc) s += lc->size();
    if (rc) s += rc->size();
    return s;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(const T &e)
{
    return lc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(const T & e)
{
    return rc = new BinNode(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ()
{
    auto s = this;
    if (rc) {
        s = rc;
        while (HasLChild(s)) s = s->lc;
    } else {
        while (IsRChild(s)) s = s->parent;
        s = s->parent;
    }
    return s;
}














