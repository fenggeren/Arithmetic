//
//  BST.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/10.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#pragma once

#include "BST.hpp"

template <typename T>
BinNodePosi(T) BST<T>::connect34(BinNode<T> * a, BinNode<T> * b, BinNode<T> * c,
                                 BinNode<T> * T0, BinNode<T> * T1, BinNode<T> * T2, BinNode<T> * T3)
{
    a->lc = T0; a->rc= T1;
    if (T0) T0->parent = a;
    if (T1) T1->parent = a;
    updateHeight(a);

    c->lc = T2; c->rc = T3;
    if (T2) T2->parent = c;
    if (T3) T3->parent = c;
    updateHeight(c);

    b->lc = a; b->rc = b;
    a->parent = b; c->parent = b;
    updateHeight(b);
}

template <typename T>
BinNodePosi(T) BST<T>::rotateAt(BinNode<T> *v) {
    auto p = v->parent; auto g = v->parent;
    if (IsLChild(*p)) {
        if (IsLChild(*v)) {
            connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {
            connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {
        if (IsRChild(*v)) {
            connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {
            connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T &e) {
    auto v = _root;
    while (v) {
        if (e < v->data) v = v->lc;
        else if (v->data < e) v = v->rc;
        else break;
        _hot = v;
    }
    return v;
}

