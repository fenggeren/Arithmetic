//
//  BTNode.h
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BTNode_h
#define BTNode_h

#include "Vector.hpp"
#define BTNodePosi(T) BTNode<T>*

template <typename T>
struct BTNode<T>
{
    BTNodePosi(T) parent;
    Vector<T> key;
    Vector<BTNodePosi(T)> child;  // child.count = key.count + 1;

    // 只能作为根节点初始化
    BTNode(){ parent = nullptr; child.insert(0, nullptr); }
    BTNode(T e, BTNodePosi(T) lc = nullptr, BTNodePosi(T) rc = nullptr)
    {
        parent = nullptr;
        key.insert(0, e);
        child.insert(0, lc); child.insert(1, rc);
        if (lc) lc->parent = this; if (rc) rc->parent = this;
    }
};


#endif /* BTNode_h */
