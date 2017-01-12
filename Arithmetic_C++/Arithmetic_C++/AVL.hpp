//
//  AVL.hpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef AVL_hpp
#define AVL_hpp

#include <stdio.h>
#include "BST.hpp"

template <typename T>
class AVL : public BST<T>
{
public:
    BinNodePosi(T) insert (const T& e);
    bool remove( const T& e);
};


#include "AVL_Implementation.hpp"

#endif /* AVL_hpp */
