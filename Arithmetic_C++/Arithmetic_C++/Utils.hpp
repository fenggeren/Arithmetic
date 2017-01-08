//
//  Utils.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include "Vector.hpp"

template<typename T>
struct CheckOrder
{
    T pred; int& unsortedNum;
    
    CheckOrder(int& unsorted, T& first):
    pred(pred), unsortedNum(unsorted){}
    
    virtual void operator() (T& e)
    {
        if (pred > e) {
            unsortedNum++;
        }
        pred = e;
    }
};

template <typename T>
void checkOrder(Vector<T> & V)
{
    int unsorted = 0;
    V.traverse(CheckOrder<T>(unsorted, V[0]));
    if (0 < unsorted) {
        
    } else {
        
    }
}

 

#endif /* Utils_hpp */
