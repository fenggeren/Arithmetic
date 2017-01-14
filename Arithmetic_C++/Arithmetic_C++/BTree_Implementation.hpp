//
//  BTree.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include <tkDecls.h>
#include "BTree.hpp"
#include "Release.hpp"
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
    if (v->child.size() >= ((_order + 1 ) >> 1)) return;
    auto p = v->parent;
    if (!p) { // 根节点比较特殊 允许 小于(_order + 1) * 0.5 个关键码
        if (!v->key.size() && v->child[0]) { // v 只有一个孩子 切没有关键码 这就是_root的特性
            _root = v->child[0]; _root->parent = nullptr;
            v->child[0] = nullptr; release(v);
        } // 整树 高度降低一层
        return;
    }

    // 确定 v 是p的第r个孩子   此时v可能不含关键码， 故不能通过关键码查找、
    Rank r = 0; while (p->child[r] != v) r++;

    // 1.向做兄弟借关键码
    if (0 < r) {
        auto ls = p->child[r - 1]; // 左兄弟必存在
        if ( (_order + 1) / 2 < ls->child.size()) { // 左兄弟 有足够的孩子(>=1)
            v->key.insert(0, p->key[r - 1]);
            p->key[r - 1] = ls->key.remove(ls->key.size() - 1); //ls 最大关键码转入p
            v->child.insert(0, ls->child.remove(ls->child.size() - 1));
            if (v->child[0]) v->child[0]->parent = v;
            return;
        }
    }
    // 左兄弟 为空 或者 没有超出的关键码
    // 向有兄弟借关键码
    if (p->child.size() - 1 > r) {  // v的右兄弟必存在
        auto rs = p->child[r + 1];
        if ((_order + 1) / 2 < rs->child.size()) {
            v->key.insert(v->key.size(), p->key[r]);
            p->key[r] = rs->key.remove(0);
            v->child.insert(v->child.size(), rs->child.remove(0));
            if (v->child[v->child.size() - 1])
                v->child[v->child.size() - 1]->parent = v;
            return;
        }
    }

    // 左右节点都不能借  只能父节点 下降 和v和其左/右节点组合成新的节点
    // 需要父节点下降 合并的情况 需要递归向上的解决下溢出
    if (0 < r) { // 和左兄弟合并
        auto ls = p->child[r - 1];
        ls->key.insert(ls->child.size(), p->key.remove(r - 1));
        p->child.remove(r);  // p 移除掉 v孩子.
        ls->child.insert(ls->child.size(), v->child.remove(0));
        if (ls->child[ls->child.size() - 1]) {
            ls->child[ls->child.size() - 1]->parent = ls;
        }

        while (v->key.size()) { // 将v剩余的所有key、child 添加到ls上
            ls->key.insert(ls->key.size(), v->key.remove(0));
            ls->child.insert(ls->child.size(), v->child.remove(0));
            if (ls->child[ls->child.size() - 1]) {
                ls->child[ls->child.size() - 1] = ls;
            }
        }
        release(v); // 释放 v节点
    } else {  // 和右兄弟合并
        auto rs = p->child[r + 1];
        rs->key.insert(0, p->key.remove(r));
        p->child.remove(r);
        rs->child.insert(0, v->key.remove(v->key.size() - 1));
        if (rs->child[0]) {
            rs->child[0]->parent = rs;
        }

        while (!v->key.empty()) {
            rs->key.insert(0, v->key.remove(v->key.size() - 1));
            rs->child.insert(0, v->child.remove(v->child.size() - 1));
            if (rs->child[0]) {
                rs->child[0]->parent = rs;
            }
        }
        release(v);
    }

    solveUnderflow(p);
    return;;
}

template <typename T>
BTNode<T> * BTree<T>::search(const T &e) {
    auto v = _root; _hot = nullptr;
    while(v) {
        Rank r = v->key.search(e);
        if (0 <= r && v->key[r] == e) return v;
        _hot = v; v = v->child[r + 1];
    }
    return nullptr;
}

template <typename T>
bool BTree<T>::insert(const T &e) {
    auto v = search(e);
    if (v) return false;

    Rank r = _hot->key.search(e);
    _hot->key.insert(r + 1, e);
    _hot->child.insert(r + 2, nullptr);
    _size++;
    solveOverflow(_hot);
    return true;
}

template <typename T>
bool BTree<T>::remove(const T &e) {
    auto v = search(e);
    if (!v) return false;

    Rank r = v->key.search(e);
    if (v->child[0]) { // 非叶子，就找到后继交换数据 叶子节点
        auto u = v->child[r + 1];
        while (u) u = u->child[0];
        v->key[r] = u->key[0];
        v = u; r = 0;  // v一直指向 要删除的节点--
    }
    v->key.remove(r);
    v->child.remove(r + 1); // child 都是nullptr 无所谓删除哪一个
    _size--;
    solveUnderflow(v);
    return true;
}