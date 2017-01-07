//
//  List.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/6.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>

typedef int Rank;

#define ListNodePosi(T) ListNode<T>*

template <typename T> struct ListNode
{
    T data;
    ListNodePosi(T) pred, succ;
    
    ListNode(){}
    ListNode( T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr):
    data(e), pred(p), succ(s){}
    
    ListNodePosi(T) insertAsPred(T const& e);
    ListNodePosi(T) insertAsSucc(T const& e);
};


template <typename T>
class List
{
private:
    int _size;
    ListNodePosi(T) header, tailer;
    
protected:
    void init();
    Rank clear();
    void copyNodes( ListNodePosi(T), Rank); // copy列表中自p起的n项
    void merge(ListNodePosi(T)& p, Rank n, List<T>& L, ListNodePosi(T) q, Rank m);// 合并有序链表
    void mergeSort(ListNodePosi(T)& p, Rank n);
    void insertionSort(ListNodePosi(T) p, Rank n);
    void selectionSort(ListNodePosi(T) p, Rank n);
    
public:
    List() { init(); }
    List( List<T> const& L);
    List( List<T> const& L, Rank r, Rank n);
    List( ListNodePosi(T) p, Rank n);
    
    ~List();
    
    Rank size() const { return _size; }
    bool empty() const { return _size <= 0; }
    T& operator[] (Rank r) const;
    ListNodePosi(T) first() const { return header->succ; }
    ListNodePosi(T) last() const { return tailer->pred; }
    bool valid( ListNodePosi(T) p)
    { return p && (tailer != p) && (header != p); }
    
    Rank disordered() const;
    
    ListNodePosi(T) find (T const& e) const
    { return find(e, _size, tailer); }
    ListNodePosi(T) find(T const& e, Rank n, ListNodePosi(T) p) const;
    
    ListNodePosi(T) search(T const& e) const
    { return search(e, _size, tailer); }
    ListNodePosi(T) search(T const& e, Rank n, ListNodePosi(T) p) const;
    
    ListNodePosi(T) selectMax(ListNodePosi(T) p, Rank n);
    ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }
    
    // readwrite
    ListNodePosi(T) insertAtFirst( T const& e);
    ListNodePosi(T) insertAtLast( T const &e);
    ListNodePosi(T) insertA (ListNodePosi(T) p, T const& e); // p->succ => e
    ListNodePosi(T) insertB (ListNodePosi(T) p, T const& e); // p->pred => e
    
    T remove( ListNodePosi(T) p);
    
    void merge (List<T>& L) { merge(first(), _size, L, L.first(), L.size()); }
    
    void sort( ListNodePosi(T) p, int n);
    void sort() { sort(first(), _size); }
    
    
    Rank deduplicate();  // 无序去重
    Rank deduplicate_a();
    Rank uniquify();     // 有序去重
    void reverse();  // 反转
    void reverse_a();
    void reverse_b();
    void reverse_c();
    void traverse(void (*)( T &));
    template<typename VST>
    void traverse( VST&);
};







#endif /* List_hpp */















