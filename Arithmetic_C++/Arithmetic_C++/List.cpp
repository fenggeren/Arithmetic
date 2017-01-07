//
//  List.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/6.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "List.hpp"
#include <stdlib.h>
#include <ios>

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

template <typename T>
void List<T>::insertionSort(ListNode<T> *p, Rank n)
{
    p = p->succ;
    for (Rank i = 1; i < n; i++) {
        insertA(search(p->data, i, p), p->data);
        p = p->succ; remove(p->pred);
    }
}

template <typename T>
void List<T>::selectionSort(ListNode<T> *p, Rank n)
{
    for (Rank i = 0; i < n - 1; i++, p = p->succ) {
        auto q = p->succ;
        for (Rank j = i + 1; j < n; j++, q = q->succ) {
            if (p->data > q->data) {
                std::swap(p->data, q->data);
            }
        }
    }
    
//    auto header = p->pred, tailer = p;  // 构建一个假的列表 链接排序好的节点
    //  SECOND::
//    while (n > 0) {
//        insertA(header, remove(selectMax(p, n)));
//        n--;
//        p = p->succ;
//    }
    
    // THIRED::
//    for (Rank i = 0; i < n; i++) tailer = tailer->succ;
//    while (n > 0) {
//        insertB(tailer, remove(selectMax(header->succ, n)));
//        tailer = tailer->pred; --n;
//    }
}


template <typename T>
List<T>::List( List<T> const& L)
{
    copyNodes(L.first(), L.size());
}

template <typename T>
List<T>::List( List<T> const& L, Rank r, Rank n)
{
    copyNodes(L[r], n);
}

template <typename T>
List<T>::List( ListNodePosi(T) p, Rank n)
{
    copyNodes(p, n);
}

template <typename T>
List<T>::~List()
{
    clear();
    delete header;
    delete tailer;
}

template <typename T>
T& List<T>::operator[] (Rank r) const
{
    auto p = first();
    while (r-- > 0) {
        p = p->succ;
    }
    return p->data;
}

template <typename T>
Rank List<T>::disordered() const
{
    Rank count = 0;
    auto p = first();
    for (Rank i = 0; i < _size - 1; i++, p = p->succ) {
        if (p->data > p->succ->data) {
            count++;
        }
    }
    return count;
}

template <typename T>   // p的前n 个node 范围
ListNodePosi(T) List<T>::find(T const& e, Rank n, ListNodePosi(T) p) const
{
    while (n-- > 0) {
        if ((p = p->pred)->data == e) return p;
    }
    return nullptr;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const& e, Rank n, ListNodePosi(T) p) const
{
    while (n-- >= 0) {
        if ((p = p->pred)->data <= e) break;
    }
    return p;
}

template <typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, Rank n)
{
    auto max = p;
    while (n-- > 1) {
        if (max->data <= (p = p->succ )->data) { max = p; }
    }
    return max;
}

template <typename T>
ListNodePosi(T) List<T>::insertAtFirst( T const& e)
{
    insertA(header, e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAtLast( T const &e)
{
    insertB(tailer, e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA (ListNodePosi(T) p, T const& e)
{
    _size++;
    p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB (ListNodePosi(T) p, T const& e)
{
    _size++;
    p->insertAsPred(e);
}

template <typename T>
T List<T>::remove( ListNodePosi(T) p)
{
    auto e = p->data;
    p->pred->succ = p->succ;
    p->succ->pred = p->pred;
    delete p; _size--;
    return e;
}


template <typename T>
Rank List<T>::deduplicate()
{
    if (_size < 2) return 0;
    auto k = first(); Rank oldSize = _size;
    while (k != last()) {
        auto p = k->succ;
        while (p != tailer) {
            (k->data == p->data) ? remove((p = p->succ)) : (p = p->succ);
        }
        k = k->succ;
    }
    return oldSize - _size;
}

template <typename T>
Rank List<T>::deduplicate_a()
{
    if (_size < 2) return 0;
    auto p = header; Rank oldSize = _size, r = 0; // 已经处理好前面的r个无重列表
    while (tailer != (p = p->succ)) {
        auto q = find(p->data, r, p);
        q ? remove(q) : r++;
    }
    return oldSize - _size;
}



template <typename T>
Rank List<T>::uniquify()
{
    if (_size < 2) return 0;
    auto p = first(); auto q = p; Rank oldSize = _size;
    while (tailer != (q = p->succ)) {  // 仅判断 无重有序向量区域最后一个节点和其后续节点data是否相等
        if (p->data != q->data) p = q;
        else remove(q);
    }
    return oldSize - _size;
}

template <typename T>
void List<T>::reverse()
{
    auto p = last()->pred;
    while (header != p) {
        insertAtLast(remove((p = p->pred)->succ));
    }
}

template <typename T>
void List<T>::reverse_a()
{
    auto p = header, q = tailer;
    for (Rank i = 0; i < _size; i += 2) {
        std::swap((p = p->succ)->data, (q = q->pred)->data);
    }
}












