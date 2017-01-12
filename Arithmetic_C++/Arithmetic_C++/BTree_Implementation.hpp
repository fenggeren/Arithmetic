//
//  BTree.cpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "BTree.hpp"

template <typename T>
void BTree<T>::solveOverflow(BTNode<T> *v) {
    if (_order >= v->child.size()) return; // 当前节点未上溢
    Rank s = _order / 2;   // _order = key.size() = child.size() - 1
    BTNodePosi(T) u = new BTNode<T>();
    
}

template <typename T>
void BTree<T>::solveUnderflow(BTNode<T> *v) {

}


