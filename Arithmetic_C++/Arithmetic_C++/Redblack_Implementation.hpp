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
void RedBlack<T>::solveDoubleBlack(BinNode<T> *r) {
    auto p = r ? r->parent : _hot; if (!p) return; // 父节点
    auto s = (r == p->lc) ? p->rc : p->lc;  // 兄弟节点

    if (IsBlack(s)) {  // 黑兄弟
        BinNodePosi(T) t = nullptr; // s的红孩子节点
        if (IsRed(s->rc)) t = s->rc;
        if (IsRed(s->lc)) t = s->lc;
        if (t) {   // 黑兄弟有 红儿子    父、兄、<兄儿>  3+4旋转  ==>
            RBColor oldColor = p->color;
            auto b = FromParentTo(*p) = rotateAt(t); // s或s->rc成为旋转后子树根节点
            if (HasLChild(*b)) {
                b->lc->color = RB_BLACK; updateHeight(b->lc);
            }
            if (HasRChild(*b)) {
                b->rc->color = RB_BLACK; updateHeight(b->rc);
            }
            b->color = oldColor; updateHeight(b);
        } else {   // 黑兄弟 没有 红儿子
            s->color = RB_RED; s->height--;
            if (IsRed(p)) {    //  红父亲
                p->color = RB_BLACK;
            } else {        // 黑父亲
                p->height--;
                solveDoubleBlack(p);
            }
        }
    } else {   // 红兄弟
        s->color = RB_BLACK; p->color = RB_RED;
        auto t = IsLChild(*s) ? s->lc : s->rc;
        _hot = p; FromParentTo(*p) = rotateAt(t);
        solveDoubleBlack(r);
    }
}


template <typename T>
int RedBlack<T>::updateHeight(BinNode<T> *x) {
    x->height = std::max(stature(x->lc), stature(x->rc));
    return IsBlack(x) ? x->height++ : x->height;
}

template <typename T>
BinNode<T> * RedBlack<T>::insert(const T &e) {
    auto& x = search(e); if (x) return x;
    x = new BinNode<T>(e,_hot, nullptr, nullptr, -1); _size++;
    solveDoubleRed(x);
    return x ? x : _hot->parent;
}

template <typename T>
bool RedBlack<T>::remove(const T &e) {
    auto & x = search(x); if (!x) return false;
    auto r = BST<T>::remove(x); if (!(--_size)) return true;

    if (!_hot) {
        _root->color = RB_BLACK; updateHeight(_root);
        return true;
    }
    if (BlackHeightUpdated(*_hot)) return true;

}


