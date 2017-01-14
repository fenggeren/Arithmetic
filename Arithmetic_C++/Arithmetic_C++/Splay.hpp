//
//  Splay.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/14.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Splay_hpp
#define Splay_hpp

#include <stdio.h>


#include "BST.hpp"


template <typename T>
class Splay : public BST<T>
{
protected:
    BinNodePosi(T) splay(BinNodePosi(T) v); // 将节点v伸展至根

public:
    BinNodePosi(T) & search(const T& e);
    BinNodePosi(T) insert(const T& e);
    bool remove(const T& e);
};


#endif /* Splay_hpp */
