//
//  BTree.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "BTree.hpp"

/**
 * [0, s) (s, _order)  s节点上移,   'u' 接管(s, _order) key & child
 * s 上移到v的父节点上
 * */
template <typename T>
void BTree<T>::solveOverflow(BTNode<T> *v) {
    if (v->child.size() <= _order) return;  // 未上溢
    Rank m = v->key.size() >> 1;
    auto u = new BTNode<T>();  // 创建一个新的节点 用于接纳 (s, _order)之间的数据 <key, child>
    for (int i = 0; i < _order - m - 1; ++i) {
        u->key.insert(i, v->key.remove(m + 1));
        u->child.insert(i, v->child.remove(m + 1));
    }
    u->child[_order - m - 1] = v->child.remove(m + 1); // child.size - key.size = 1; 所以不全最后一个child
    if (u->child[0]) {
        for (int i = 0; i < u->child.size(); ++i) {
            u->child[i]->parent = u;
        }
    }

    auto p = v->parent;
    if (!p) {
        _root = p = new BTNode<T>();
        p->child[0] = u; u->parent = p;
    }

    Rank r = 1 + p->key.search(v->key[m]); // m 上移 到p 应该插入的位置
    p->key.insert(r, v->key.remove(m));
    p->child.insert(r, u); u->parent = p;
    solveOverflow(p);
}

// 下溢  左顾右盼/合并
template <typename T>
void BTree<T>::solveUnderflow(BTNode<T> *v)
{

}


