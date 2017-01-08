//
//  Vector.hpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/4.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Vector_hpp
#define Vector_hpp

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T>
class Vector
{
protected:
    Rank _size; int _capacity; T* _elem;
    
    void copyFrom(T const* A, Rank lo, Rank hi);
    void expand();
    void shrink();
    
    Rank bubble_fast(Rank lo, Rank hi);
    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    
    Rank max(Rank lo, Rank hi);  // [lo, hi]
    void selectionSort(Rank lo, Rank hi);
    
    void merge(Rank lo, Rank mi, Rank hi);
    void merge_optimized(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    
    Rank partition(Rank lo, Rank hi); // 轴点构造算法
    Rank partitionA(Rank lo, Rank hi); // 轴点构造算法
    Rank partitionA1(Rank lo, Rank hi); // 轴点构造算法
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
    
public:
    
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    Vector(T const* A, Rank n) {copyFrom(A, 0, n); }
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
    Vector(Vector<T> const& v) { copyFrom(v._elem, 0, v._size); }
    Vector(Vector<T> const& v, Rank lo, Rank hi) { copyFrom(v._elem, lo, hi); }
    
    ~Vector() { delete [] _elem; }
    
    // @readonly
    Rank size() const { return _size; }
    bool empty() const { return !_size; }
    Rank disordered() const; // 是否已排序， 返回两两非排序数量
    // 无需向量查找
    Rank find(T const& e) const { return find(e, 0, _size); };
    Rank find(T const& e, Rank lo, Rank hi) const;
    // 有序向量查找
    Rank search(T const& e) const
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const;
    Rank search_binary_a(T const& e, Rank lo, Rank hi) const;
    Rank search_binary_b(T const& e, Rank lo, Rank hi) const;
    Rank search_binary_c(T const& e, Rank lo, Rank hi) const;
    Rank search_fibonaccian_a(T const& e, Rank lo, Rank hi) const;
    Rank search_fibonaccian_b(T const& e, Rank lo, Rank hi) const;
    // @readwrite
    T& operator[] (Rank r) const;
    Vector<T> & operator= (Vector<T> const& );
    T remove(Rank r);
    Rank remove( Rank lo, Rank hi);
    Rank insert( Rank r, T const& e);
    Rank insert(T const& e) { return insert(_size, e); }
    void sort(Rank lo, Rank hi);
    void sort() { sort(0, _size); }
    void unsort(Rank lo, Rank hi);
    void unsort() { unsort(0, _size); }
    
    Rank deduplicate();  // 无须去重
    Rank deduplicate_a();
    Rank deduplicate_b();
    Rank uniquify(); // 有序去重
    
    // 遍历
    void traverse( void(*) (T&)); // 使用函数指针，只读或局部性修改
    template<typename VST> void traverse(VST& ); // 使用函数对象，可全局修改
};

#endif /* Vector_hpp */























