//
//  Splay.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/14.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "Splay.hpp"

template <typename NodePosi>
inline void attachAsLChild(NodePosi p, NodePosi lc)
{
    p->lc = lc;
    if (lc) lc->parent = p;
}

template <typename NodePosi>
inline void attachAsRChild(NodePosi p, NodePosi rc)
{
    p->rc = rc;
    if (rc) rc->parent = p;
}

template <typename T>
BinNode<T> * Splay<T>::splay(BinNode<T> *v) {
    if (!v) return nullptr;
    BinNodePosi(T) p; BinNodePosi(T) g;
    // 自上而下 反复对*v做双层伸展
    while ((p = v->parent) && (g = p->parent)) {
        auto gg = g->parent;
        if (IsLChild(*v)) {
            if (IsLChild(*p)) {  // ll
                attachAsLChild(p, v->rc);
                attachAsLChild(g, p->rc);
                attachAsRChild(p, g);
                attachAsRChild(v, p);
            } else {
                attachAsLChild(g, v->rc);
                attachAsRChild(v, p);
                attachAsRChild(p, v->lc);
                attachAsLChild(v, g);
            }
        } else {
            if (IsRChild(*p)) {
                attachAsLChild(p, g);
                attachAsRChild(g, p->lc);
                attachAsRChild(p, v->lc);
                attachAsLChild(v, p);
            } else {
                attachAsLChild(v, p);
                attachAsRChild(p, v->lc);
                attachAsRChild(v, g);
                attachAsLChild(g, v->rc);
            }
        }
        if (!gg) v->parent = nullptr;
        else
            IsLChild(*g) ? attachAsLChild(g->parent, v) : attachAsRChild(g->parent, v);
        updateHeight(g); updateHeight(p); updateHeight(v);
    } // 双层 伸展结束后  必有g==nullptr, 但p可能为非nullptr

    if (p = v->parent) { // 若p为非空，做一次但旋
        if(IsLChild(*v)) {
            attachAsLChild(p, v->rc);
            attachAsRChild(v, p);
        } else {
            attachAsRChild(p, v->lc);
            attachAsLChild(v, p);
        }
        updateHeight(p);
        updateHeight(v);
    }
    v->parent = nullptr;
    return v;
}

// 查找完毕 将查找的最后一个节点旋转至 根节点
template <typename T>
BinNode<T> * & Splay<T>::search(const T &e) {
    auto p = searchIn(_root, e, _hot);
    _root = splay(p ? p : _hot);
    return _root;
}


// 搜索函数返回  插入节点的父节点(没有找到相等的)
// 并将其 旋转为 根节点。
// 将插入节点作为根节点 插入
template <typename T>
BinNode<T> * Splay<T>::insert(const T &e) {
    if (!_root)  {
        _size ++;
        return _root = new BinNode<T>(e);
    }

    if (e == search(e)->data) return _root;
    _size++; auto t = _root;

    if (e < t->data) {
        t->parent = _root = new BinNode<T>(e, nullptr, t, t->rc);
        if (HasRChild(*t)) {
            t->rc->parent = _root;
            t->rc = nullptr;
        }
    } else {
        t->parent = _root = new BinNode<T>(e, nullptr, t->lc, t);
        if (HasLChild(*t)) {
            t->lc->parent = _root;
            t->lc = nullptr;
        }
    }

    updateHeightAbove(t);
    return _root;
}


template <typename T>
bool Splay<T>::remove(const T &e) {
    if (!_root || (e != search(e)->data)) return false;

//    BST<T>::remove(_root);
    auto w = _root;
    if (!HasLChild(*_root)) {
        _root = _root->rc;
        if (_root) _root->parent = nullptr;
    } else if (!HasRChild(*_root)) {
        _root = _root->lc;
        if(_root) _root->parent = nullptr;
    } else { // 1.斩断 左子树和_root的联系， _root被其后继替换 左子树在复到新的_root上
        auto lTree = _root->lc;
        lTree->parent = nullptr; _root->lc = nullptr;
        _root = _root->rc; _root->parent = nullptr;
        search(w->data); // 必败的搜索， 但是把_root的后继 旋转为_root
        _root->lc = lTree; lTree->parent = _root;
    }
    release(w->data); release(w); _size--;
    if (_root) updateHeight(_root);
    return true;
}