//
//  BinNode.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BinNode_hpp
#define BinNode_hpp

#include <stdio.h>

#define BinNodePosi(T) BinNode<T>*  
#define stature(p) ((p) ? (p)->height : -1)  // 节点高度
typedef enum { RB_RED, RB_BLACK } RBColor; // 节点颜色

template <typename T>
struct BinNode
{
    T data;
    BinNodePosi(T) parent;
    BinNodePosi(T) lc;
    BinNodePosi(T) rc;
    
    int height;
    int npl; // null path length （作式堆)
    RBColor color; // 红黑树 节点颜色
    
    BinNode():
    parent(nullptr), lc(nullptr), rc(nullptr),
    height(0), npl(1), color(RB_RED) {}
    
    BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr,
            BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED):
    data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c){}
    
    int size();  // 当前节点 后代总数， 亦即以此为根的 子树的规模
    BinNodePosi(T) insertAsLC(T const& );
    BinNodePosi(T) insertAsRC(T const& );
    BinNodePosi(T) succ();  // 直接后继
    
    template<typename VST> void travLevel(VST& ); // 子树层次遍历
    template<typename VST> void travPre(VST& ); // 子树先序遍历
    template<typename VST> void travIn(VST& ); // 中序遍历
    template<typename VST> void travPost(VST& ); //子树后序遍历
    
    bool operator< (BinNode const& bn) { return data < bn.data; }
    bool operator== (BinNode const& bn) { return data == bn.data; }
    
    BinNodePosi(T) zig(); // 顺时针旋转
    BinNodePosi(T) zag(); // 逆时针旋转
};

//#include "BinNode_Implemention.hpp"

#endif /* BinNode_hpp */
