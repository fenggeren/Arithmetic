//
//  Queue.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

#include "List.hpp"

template <typename T>
class Queue
{
public:
    virtual void enqueue(T& e) = 0;
    virtual T& dequeue() = 0;
    virtual T& front() = 0;
};


template <typename T>
class Queue_List : public List<T>, public Queue<T>
{
public:
    void enqueue(T& e) { this->insertAtLast(e); }
    T& dequeue() { return this->remove(this->first()); }
    T& front() { return this->first()->data; }
};


#endif /* Queue_hpp */
