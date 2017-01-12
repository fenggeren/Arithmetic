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

template <typename T>
BinNodePosi(T) BST<T>::insert(const T &e) {
    auto node = search(e);
    if (node) return node;
    if (_hot->data < e) node = insertAsRC(_hot, e);
    else node = insertAsLC(_hot, e);

    return node;
}

template <typename T>
bool BST<T>::remove(const T &e) {
    auto node = search(e);
    if (!node) return false;

    auto r = node;
    BinNodePosi(T) succ = nullptr;
    if (!HasLChild((*node))) {
       succ = node = node->rc;
    } else if (!HasRChild(*node)) {
        succ = node = node->lc;
    } else {
        r = node->succ();
        std::swap(node->data, r->data);
        // 判断下  node的后继是否是node的右孩子节点
        (r->parent == node ? r->parent->rc : r->parent->lc) = succ = r->rc;
    }
    _hot = r->parent;
    if (succ) succ->parent = _hot;
    release(r->data); release(r);
    _size--;
    updateHeightAbove(r->parent);
    return true;
}
