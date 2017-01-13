//
//  Redblack.hpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/13.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Redblack_hpp
#define Redblack_hpp

#include "BST.hpp"


template <typename T>
class RedBlack : public BST<T>
{
protected:
    void solveDoubleRed( BinNodePosi(T) x);
    void solveDoubleBlack( BinNodePosi(T) x);
    int updateHeight (BinNodePosi(T) x);

public:
    BinNodePosi(T) insert(const T& e);
    bool remove (const T& e);

};



#endif /* Redblack_hpp */
