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
    
    Rank mi = lo;
    for (Rank k = lo + 1; k < hi; ++k) {
        if (_elem[k] < pivot) {
            std::swap(_elem[++mi], _elem[k]);
        }
    }
}






























