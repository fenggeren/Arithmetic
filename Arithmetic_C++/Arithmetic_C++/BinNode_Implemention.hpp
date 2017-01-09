//
//  BinNode.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#pragma once

#include "BinNode.hpp"
#include "Binnode_macro_BASIC.h"
#include "Queue.hpp"

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
        while (HasLChild(*s)) s = s->lc;
    } else {
        while (IsRChild(*s)) s = s->parent;
        s = s->parent;
    }
    return s;
}


template <typename T>
template <typename VST>
void BinNode<T>::travLevel(VST& vist)
{
    Queue_List<BinNodePosi(T)> queue;
    queue.enqueue(this);
    while (queue.size()) {
        auto node = queue.dequeue();
        vist(node->data);
        if (HasLChild(*node)) queue.enqueue(node->lc);
        if (HasRChild(*node)) queue.enqueue(node->rc);
    }
}


template <typename T>
template <typename VST>
void BinNode<T>::travPre(VST& visit)
{
    visit(data);
    if (lc) lc->travPre(visit);
    if (rc) rc->travPre(visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travIn(VST& visit)
{
    if (lc) lc->travPre(visit);
    visit(data);
    if (rc) rc->travPre(visit);
}

template <typename T>
template <typename VST>
void BinNode<T>::travPost(VST& visit)
{
    if (lc) lc->travPre(visit);
    if (rc) rc->travPre(visit);
    visit(data);
}

template <typename T>  // LL
BinNodePosi(T) BinNode<T>::zig() {
    auto lChild = lc;
    lChild->parent = this->parent;
    if (lChild->parent) {
        IsRChild(*this) ? lChild->parent->rc = lChild : lChild->parent->lc = lChild;
    }
    lc = lChild->rc; if (lc) lc->parent = this;
    lChild->rc = this; this->parent = lChild;
    return lChild;
}


template <typename T>  // RR
BinNodePosi(T) BinNode<T>::zag() {
    auto rChild = rc;
    rChild->parent = this->parent;
    if (rChild->parent) {
        IsRChild(*this) ? rChild->parent->rc = rChild : rChild->parent->lc = rChild;
    }
    rc = rChild->lc; if (rc) rc->parent = this;
    this->parent = rChild; rChild->lc = this;
    return rChild;
}
