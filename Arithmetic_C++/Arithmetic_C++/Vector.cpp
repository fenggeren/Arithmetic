//
//  Vector.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/4.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "Vector.hpp"
#include <ios>
#include <stdlib.h>
#include "Fibonacci.hpp"

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
void Vector<T>::expand()
{
    if (_size >= _capacity) {
        T *oldEle = _elem;
        _elem = new T[_capacity <<= 1];
        for (Rank i = 0; i < _size; _elem[i++] = oldEle[i]);
        delete [] oldEle;
    }
}

template <typename T>
void Vector<T>::shrink()
{
    if (_size < _capacity >> 1) {
        T *oldEle = _elem;
        _elem = new T[_capacity >>= 1];
        for (Rank i = 0; i < _size; _elem[i++] = oldEle[i]) ;
        delete [] oldEle;
    }
}

template <typename T>   // [lo, hi)
bool Vector<T>::bubble(Rank lo, Rank hi)
{
    bool sorted = true;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}

template <typename T>
Rank Vector<T>::bubble_fast(Rank lo, Rank hi)
{
    Rank last = lo;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            last = lo;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return last;
}

template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
    while (!bubble(lo, hi--));
    
//    while (lo < hi) {
//        hi = bubble_fast(lo, hi);
//    }
}

template <typename T>  // [lo, hi]
Rank Vector<T>::max ( Rank lo, Rank hi )
{
    Rank max = hi;
//    while (++lo <= hi) {
//        if (_elem[lo - 1] < _elem[lo]) {
//            max = lo;
//        }
//    }
    
    while (lo < hi--) {
        if (_elem[hi] > _elem[max]) {
            max = hi;
        }
    }
    
    return max;
}

template <typename T>  // 选择排序
void Vector<T>::selectionSort(Rank lo, Rank hi)
{
    while (lo < --hi) {
        std::swap(_elem[hi], max(lo, hi));
    }
}

template <typename T>
void Vector<T>::mergeSort ( Rank lo, Rank hi ) //选择排序算法
{
    if (lo < hi) {
        Rank mi = (hi - lo) >> 1;
        mergeSort(lo, mi);
        mergeSort(mi , hi);
        merge(lo, mi, hi);
    }
}

template <typename T>
void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) //归并算法
{
    Rank ld = mi - lo;
    Rank rd = hi - mi;
    T* beg = _elem + lo;
    T* left = new T[ld];
    T* right = _elem + mi;
    for(Rank i = 0; i < ld; left[i++] = beg[i]);
    
    for (Rank i = 0, j = 0, k = 0; j < ld || k < rd; ) {
        if ((j < ld) && (left[j] <= right[k] || k >= rd)) {
            beg[i++] = left[++j];
        }
        
        if ((k < rd) && (left[j] > right[k] || j >= ld)) {
            beg[i++] = right[k++];
        }
    }
    delete [] left;
}

template <typename T>
void Vector<T>::merge_optimized( Rank lo, Rank mi, Rank hi ) //归并优化算法
{
    Rank ld = mi - lo;
    Rank rd = hi - mi;
    T* beg = _elem + lo;
    T* left = new T[ld];
    T* right = _elem + mi;
    for (Rank i = 0; i < ld; left[i++] = beg[i]);
    for (Rank begIndex = 0, leftIndex = 0, rightIndex = 0;
         leftIndex < rd;) {
        if (rightIndex < rd && left[leftIndex] > right[rightIndex]) {
            beg[begIndex++] = right[rightIndex++];
        }
        if (rightIndex >= rd || left[leftIndex] <= right[rightIndex]) {
            beg[begIndex++] = left[leftIndex++];
        }
    }
    delete [] left;
}

template<typename T>  // [lo, hi)
void Vector<T>::quickSort(Rank lo, Rank hi)
{
    if (hi - lo < 2) return; // 单元素区间自然有序
    Rank mi = partition(lo, hi); // mi位置一定是最终的排序位置
    quickSort(lo, mi);  // [lo, mi)
    quickSort(mi + 1, hi); // [mi+1, hi)
}

template<typename T>
Rank Vector<T>::partitionA1(Rank lo, Rank hi)
{
    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
    T pivot = _elem[lo];
    
    while (lo < hi) {
        while (lo < hi) {
            if (pivot < _elem[hi]) {
                hi--;
            } else {
                _elem[lo++] = _elem[hi]; // hi 值挪到lo处 即privot处, 然后lo++, 而privot 指向了hi
                break;
            }
        }
        
        while (lo < hi) {
            if (_elem[lo] < pivot) {
                lo++;
            } else {
                _elem[hi--] = _elem[lo]; // privot 指向了 lo
                break;
            }
        }
    }
    _elem[lo] = pivot;
    return lo;
}


template<typename T>
Rank Vector<T>::partitionA(Rank lo, Rank hi)
{
    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
    T pivot = _elem[lo];
    
    while (lo < hi) {
        while (lo < hi && pivot <= _elem[hi]) {
            hi--;
        }
        if(lo < hi) _elem[lo++] = _elem[hi];
        
        while (lo < hi && _elem[lo] <= pivot) {
            lo++;
        }
        if (lo < hi) _elem[hi--] = _elem[lo];
    }
    _elem[lo] = pivot;
    return lo;
}


template<typename T>
Rank Vector<T>::partition(Rank lo, Rank hi)
{
    std::swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);
    T pivot = _elem[lo];
                              //  |   < pivot  |    > pivot   | unvisited|
    Rank mi = lo; // [lo, hi)   lo|------------mi-------------k-----------|hi
    for (Rank k = lo + 1; k < hi; ++k) {
        if (_elem[k] < pivot) {
            std::swap(_elem[++mi], _elem[k]);
        }
    }
    std::swap(_elem[mi], _elem[lo]);
}

template<typename T>
Rank Vector<T>::disordered() const
{
    Rank count = 0;
    for (Rank i = 1; i < _size; ++i) {
        if (_elem[i - 1] > _elem[i]) {
            ++count;
        }
    }
    return count;
}

#pragma mark - 查找 

#pragma mark 无序查找
template<typename T>
Rank Vector<T>::find ( T const& e, Rank lo, Rank hi ) const
{
    while (lo < hi-- && _elem[hi] != e);
    return hi;
}

#pragma mark 有序查找
template<typename T>
Rank Vector<T>::search ( T const& e, Rank lo, Rank hi ) const
{

}

// 没有 返回 -1
template<typename T>
Rank Vector<T>::search_binary_a(T const& e, Rank lo, Rank hi) const
{
    while (lo < hi) {
        Rank mi = (hi - lo) >> 1;
        if (e < _elem[mi]) hi = mi;
        else if (e > _elem[mi]) lo = mi + 1;
        else return mi;
    }
    return -1;
}
// 没有 返回 -1
template<typename T>
Rank Vector<T>::search_binary_b(T const& e, Rank lo, Rank hi) const
{
    while (lo + 1 < hi) { // 少一个判断分支 不能立即判断是否有改元素只能到最后判定
        Rank mi = (hi - lo) >> 1;
        (e < _elem[mi]) ? hi = mi : lo = mi;
    }
    return _elem[lo] == e ? lo : -1; // 最终lo,hi 之间剩余一个元素， 然后进行判断
}

// // 没有 返回失败的秩 而不是-1
template<typename T>
Rank Vector<T>::search_binary_c(T const& e, Rank lo, Rank hi) const
{
    while (lo < hi) {
        Rank mi = (hi - lo) >> 1;
         // [lo mi) (mi, hi)。 如果 _elem[mi]==e  那么会一直循环判断,
        // 这时候lo 是不变的，hi一直在改变, 所以最后可以判断 最终结果，
        (e < _elem[mi]) ? hi = mi : lo = mi + 1;
    }
    return --lo;
}

// 完美分割比例
template<typename T>  // [0, _size)
Rank Vector<T>::search_fibonaccian_a(T const& e, Rank lo, Rank hi) const
{
    Fib fib(hi - lo);
    //  |-lo--------|fib|---hi-|
    while (lo < hi) {
        // 选个最接近fib的数字如fib(12)=144, 而hi-lo=100，
        // 选择 那么fib.get() = fib(11) = 89          0       89-1    100
        //                                      结构 |lo-----fib---hi|
        while (hi - lo < fib.get()) {
            fib.prev();
        }
        Rank mi = lo + fib.get() - 1;
        if (e < _elem[mi]) hi = mi;
        else if (_elem[mi] > e) lo = mi;
        else return mi;
    }
    return -1;
}

template<typename T>
Rank Vector<T>::search_fibonaccian_b(T const& e, Rank lo, Rank hi) const
{
    Fib fib(hi - lo);
    while (lo < hi) {
        while (hi - lo < fib.get()) {
            fib.prev();
        }
        Rank mi = lo + fib.get() - 1;
        ( e < _elem[mi]) ? hi = mi : lo = mi + 1;   // [lo, mi) (mi, hi)
    }
    return --lo;
}


template<typename T>
T& Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}

template<typename T>
T Vector<T>::remove(Rank r)
{
    T tmp = _elem[r];
    remove(r, r + 1);
    return tmp;
}


template<typename T>
Rank Vector<T>::remove(Rank lo, Rank hi)
{
    if (hi <= lo) return 0;
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo;
    shrink();
    return hi - lo;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e)
{
    expand();
    Rank size = _size++;
    while (size-- > r) {
        _elem[size + 1] = _elem[size];
    }
    _elem[r] = e;
    return r;
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T *ele = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i) {
        std::swap(_elem[i], _elem[rand() % i]);
    }
}

template<typename T>
Rank Vector<T>::deduplicate()
{
    Rank oldSize = _size;
    for (Rank i = 1; i < _size; ++i) {
        for (Rank j = i - 1; j >= 0; --j) {
            if (_elem[i] == _elem[j]) {
                remove(j); break;
            }
        }
    }
    
//    Rank trav = 1;
//    while (trav < _size) {
//        find(_elem[trav], 0, trav) < 0 ? trav++ : remove(trav);
//    }
    
    return oldSize - _size;
}

template<typename T>
Rank Vector<T>::deduplicate_a()
{
    Rank oldSize = _size;
    Rank i = -1;
    while (++i < _size - 1) {
        for (Rank j = i + 1; j < _size;) {
            _elem[i] == _elem[j] ? remove(j) : j++;
        }
    }
    return oldSize - _size;
}

// 不进行移除操作， i遍历向量下表，[0,k)无重复区间, [i,hi)为遍历区间  [k, i)重复区间
// i元素和[0,k)不重复，将i赋值给k 始终保证[0, k)不重复
//              |----k-------------i--------------|
template<typename T>
Rank Vector<T>::deduplicate_b()
{
    Rank k = 1;
    for (Rank i = 1; i < _size; ++i) {
        bool duplicate = false;
        for (Rank j = k - 1; j >= 0; --j) {
            if (_elem[i] == _elem[j]) {
                duplicate = true; break;
            }
        }
        if (!duplicate) {
            _elem[k++] = _elem[i];
        }
    }
    Rank num = _size - k;
    _size = k; shrink();
    return num;
}

template<typename T>
Rank Vector<T>::uniquify()
{
    // |---k----i---|    [lo, k] [k, i) [i, hi)
    Rank i = 0, k = 0;
    while (++i < _size) {
        if (_elem[i] != _elem[k])  _elem[++k] = _elem[i];
    }
    Rank num = _size - k - 1;
    _size -= num; shrink();
    return num;
}















