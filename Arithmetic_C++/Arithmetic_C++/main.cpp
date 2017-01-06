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

int getInt(int a, int b)
{
    static int i = 0;
    std::cout << "--------" << i++ << "-------" << std::endl;
    return a + b;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
//    Fib fib(100);
//    std::cout << fib.get() << std::endl;
    
    for (int i = 0; i < getInt(10, 20); ++i) {
        ;
    }
    
    return 0;
}
