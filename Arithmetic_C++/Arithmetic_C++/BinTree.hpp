//
//  BinTree.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/9.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BinTree_hpp
#define BinTree_hpp

#include <stdio.h>
#include "BinNode.hpp"

template <typename T>
class BinTree
{
protected:
    int _size; BinNodePosi(T) _root;
    virtual int updateHeight(BinNodePosi(T) x); // 更新节点高度
    void updateHeightAbove(BinNodePosi(T) x); // 更新节点x及其祖先高度

public:
    BinTree(): _size(0), _root(nullptr) {}
    ~BinTree() { if (_size > 0) remove(_root); }


    int size() const  { return _size; }
    bool empty() const { return !_root; }

    BinNodePosi(T) root() const { return _root; }

    BinNodePosi(T) insertAsRoot(T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
    BinNodePosi(T) insertAsLC(BinNodePosi(T) x, BinTree<T>* &T);
    BinNodePosi(T) insertAsRC(BinNodePosi(T) x, BinTree<T>* &T);

    int remove(BinNodePosi(T) x); // 删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede(BinNodePosi(T) x); // 将子树x从当前书中摘除，并将其转换为一个独立子树

    template <typename VST>
            void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }
    template <typename VST>
            void travPre(VST& visit) { if(_root) _root->travPre(visit);}
    template <typename VST>
            void travIn(VST& visit) { if(_root) _root->travIn(visit);}
    template <typename VST>
            void travPost(VST& visit) { if(_root) _root->travPost(visit); }

    bool operator< (BinTree<T> const& t)
    { return _root && t._root && _root < t._root;}
    bool operator==(BinTree<T> const& t)
    { return _root && t._root && _root == t._root; }

    void stretchToLPath();  // 借助zag旋转，转化为左向单链
    void stretchToRPath(); // 借助zig旋转，转化为右向单链
};


#endif /* BinTree_hpp */
