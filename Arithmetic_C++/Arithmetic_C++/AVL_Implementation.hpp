//
//  AVL.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#pragma once

#include "AVL.hpp"
#include "BinNode_macro_avl.h"
#include "avl_macro.h"

template <typename T>  // 必定插到叶节点
BinNodePosi(T) AVL<T>::insert(const T &e) {
    auto v = BST<T>::insert(e);  // _hot==>v->parent必定是平衡的
    for (auto g = _hot; g; g = g->parent) {
        // 不平衡 通过3+4 旋转 平衡 只一次就ok了，  本质上是让v上移一格， g的最低的叶节点下移一格
        // 通过g 计算出 p v   通过3+4 旋转平衡
        if (!AvlBalance(g)) {
            rotateAt(tallerChild(tallerChild(g)));
            break;
        } else {  // 如果是平衡的  更新下高度， 当_hot节点只有插入的v这一个节点时，高度也会变化
            updateHeight(g);
        }
    }
}

template <typename T>
bool AVL<T>::remove(const T &e) {
    if (!BST<T>::remove(e)) return false;
    for (auto g = _hot; g; g = g->parent) {
        if (!AvlBalance(*g)) {
            g = rotateAt(tallerChild(tallerChild(g)));
        }
        updateHeight(g);
    }
    return true;
}