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
class Vector {
protected:
    Rank _size; int _capacity; T* _elem;
    
    void copyFrom(T const* A, Rank lo, Rank hi);
    void expand();
    void shrink();
    
    bool bubble(Rank lo, Rank hi);
    void bubbleSort(Rank lo, Rank hi);
    
    Rank max(Rank lo, Rank hi);
    void selectionSort(Rank lo, Rank hi);
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);
    Rank partition(Rank lo, Rank hi); // 轴点构造算法
    void quickSort(Rank lo, Rank hi);
    void heapSort(Rank lo, Rank hi);
    
public:
    
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
    {
        _elem = new T[_capacity = c];
        for (_size = 0; _size < s; _elem[_size++] = v);
    }
    
};

#endif /* Vector_hpp */























