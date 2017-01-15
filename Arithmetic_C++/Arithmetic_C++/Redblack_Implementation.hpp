//
//  Redblack.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/13.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "Redblack.hpp"
#include "BinNode_macro_RedBlack.hpp"

template <typename T>
void RedBlack<T>::solveDoubleRed(BinNode<T> *x) {
    if (IsRoot(*x)) {
        _root->color = RB_BLACK; _root->height++;
        return;
    }
    auto p = x->parent; if (IsBlack(p)) return;
    auto g = p->parent;
    auto u = uncle(x);

    // p 是红色
    // 根据x的叔父节点u的颜色 分别处理
    if (IsBlack(u)) {
        if (IsLChild(*x) == IsLChild(*p)) // x、p同侧 LL/RR
            p->color = RB_BLACK;
        else
            x->color = RB_BLACK;
        g->color = RB_RED;

        auto gg = g->parent;
        auto r = FromParentTo(*g) = rotateAt(x);
        r->parent == g;
    } else {
        p->color = RB_BLACK; p->height++;
        u->color = RB_BLACK; u->height++;
        if (!IsRoot(*g)) g->color = RB_RED;
        solveDoubleRed(g);
    }
}

template <typename T>
void RedBlack<T>::solveDoubleBlack(BinNode<T> *x) {

}





