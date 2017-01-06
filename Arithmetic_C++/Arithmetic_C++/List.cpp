//
//  List.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/6.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "List.hpp"

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(const T &e)
{
    ListNodePosi(T) newNode = new ListNode(e, pred, this);
    pred->succ = newNode;
    pred = newNode;
    return newNode;
}

template <typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(const T &e)
{
    ListNodePosi(T) newNode = new ListNode(e, this, succ);
    succ->pred = newNode;
    succ = newNode;
    return newNode;
}





template <typename T>
void List<T>::init()
{
    header = new ListNode<T>();
    tailer = new ListNode<T>();
    
    header->succ = tailer;
    tailer->pred = header;
    header->pred = tailer->pred = nullptr;
    _size = 0;
}


template <typename T>
Rank List<T>::clear()
{
    Rank oldSize = _size;
    while (_size > 0) {
        remove(first());
    }
    return oldSize;
}

template <typename T>
void List<T>::copyNodes(ListNode<T> *p, Rank n)
{
    init();
    while (n--) {
        insertAtLast(p->data);
        p = p->succ;
    }
}

template <typename T>
void List<T>::merge(ListNode<T> *&p, Rank n, List<T> &L, ListNode<T> *q, Rank m)
{
    auto pp = p->pred;
    while (m > 0) {
        if (n > 0 && p->data <= q->data) {
            if (q == (p = p->succ)) break; n--;
        } else {
            insertB(p, L.remove((q = q->succ)->pred)); m--;
        }
    }
    return pp->succ;
}

template <typename T>
void List<T>::mergeSort(ListNode<T> *&p, Rank n)
{
    if (n < 2) return;
    Rank mid = n >> 1;
    auto q = p;
    for(Rank i = 0; i < mid; i++) q = q->succ;
    mergeSort(p, mid); mergeSort(q, n - mid);
    merge(p, mid, *this, q, n - mid);
}






















