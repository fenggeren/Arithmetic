//
//  Stack.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include "Vector.hpp"
#include "List.hpp"


template<typename T>
class Stack
{
public:
    virtual void push(T const& e) = 0;
    virtual T pop() = 0;
    virtual T& top() = 0;
};


template<typename T>
class Stack_Vector : public Vector<T>, public Stack<T>
{
public:
    void push(T const& e) { this->insert(this->size(), e); }
    T pop() { return this->remove(this->size() - 1); }
    T& top() { return (*this)[this->size() - 1]; }
};


template<typename T>
class Stack_List : public List<T>, public Stack<T>
{
public:
    void push(T const& e) { this->insertAtLast(e); }
    T pop() { return this->remove(this->last()); }
    T& top() { return this->last(); }
};


#endif /* Stack_hpp */
