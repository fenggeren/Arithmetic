//
//  main.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/4.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include <iostream>
#include <ios>
#include "Fibonacci.hpp"
#include "Stack.hpp"

template<typename T>
class A
{
public:
    void aaa(T& e) {
        aaa(e, e);
    }
    void aaa(T& a, T& b) {
//        std::cout << "aa1" << std::endl;
        std::cout << a << "     " << b << std::endl;
    }
};

template<typename T>
class B : public A<T>
{
public:
    void bbb(T& e) { this->aaa(e); }
};


int main(int argc, const char * argv[]) {
 
    
    Stack_Vector<int> ss;
    ss.push(123);
    ss.push(109);
    ss.pop();
    ss.top();
    
    
    return 0;
}
