//
//  BTree.hpp
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BTree_hpp
#define BTree_hpp

#include "BTNode.hpp"
#include "Release.hpp"

template <typename T>
class BTree
{
protected:
    int _size;
    int _order;
    BTNodePosi(T) _root;
    BTNodePosi(T) _hot; // search() 最后的非空节点位置
    void solveOverflow(BTNodePosi(T) ); // 因插入而上溢之后的分裂处理
    void solveUnderflow(BTNodePosi(T) ); // 因删除而下溢之后的合并处理

public:
    BTree( int order = 3): _order(order), _size(0)
    { _root = new BTNode<T>(); }
    ~BTree() { if(_root) release(_root); }

    int const order() { return _order; }
    int const size() { return _size; }
    BTNodePosi(T) & root() { return _root; }
    bool  empty() const { return !_root; }
    BTNodePosi(T) search(const T& e);
    bool insert( const T& e);
    bool remove( const T& e);
};

#include "BTree_Implementation.hpp"

#endif /* BTree_hpp */
