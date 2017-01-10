//
//  BST.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/10.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BST_hpp
#define BST_hpp

#include <stdio.h>
#include "BinTree.hpp"

template <typename T>
class BST : public BinTree<T>
{
protected:
    BinNodePosi(T) _hot;    //命中节点的父亲
    BinNodePosi(T) connect34( // 按照 "3+4" 结构， 链接3各节点及四颗子树, 无论怎么变换垂直位置永远不变
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
            BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
    // 对x及其父亲、祖父 做同意旋转调整
    BinNodePosi(T) rotateAt(BinNodePosi(T) x);

public:
    virtual BinNodePosi(T) & search(const T& e);
    virtual BinNodePosi(T) insert(const T& e);
    virtual bool remove(const T& e);
};


#include "BST_Implementation.hpp"

#endif /* BST_hpp */
