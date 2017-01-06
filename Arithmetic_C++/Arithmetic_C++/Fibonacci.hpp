//
//  Fibonacci.hpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/6.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Fibonacci_hpp
#define Fibonacci_hpp
#include <iostream>

class Fib
{
private:
    int f, g;
public:
    Fib(int n ) { f = 1; g = 0;
        int num = 0;
        while(g < n) {
            next();
            std::cout << ++num << "       " << g << std::endl;
        }
        std::cout << "\n----------over----------\n" << std::endl;
    }
    int get() { return g; }
    int next() { g += f; f = g - f; return g; }
    int prev() { f = g - f; g -= f; return g; }
};


#endif /* Fibonacci_hpp */





