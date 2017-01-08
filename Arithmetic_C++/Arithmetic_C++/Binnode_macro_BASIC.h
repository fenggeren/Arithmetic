//
//  Binnode_macro_BASIC.h
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/8.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Binnode_macro_BASIC_h
#define Binnode_macro_BASIC_h


#define IsRoot(x) ( !((x)->parent))
#define IsLChild(x) ( !IsRoot(x) && ((x).parent->lc == &(x)))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->rc))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x) || HasRChild(x))
#define HasBothChild(x) (HasLChild(x) && HasRChild(x))
#define IsLeaf(x) (!HasChild(x))



// 兄弟节点
#define sibling(p)  \
        (IsLChild(*(p)) ? (p)->parent->rc : (p)->parent->lc)

#define uncle(x) \
        ((x)->parent ? sibling((x)->parent) : nullptr)

#define FromParentTo(x) \
        (IsRoot(x) ? _root : (IsLChild(x) ? (x).parent->lc : (x).parent->rc))





#endif /* Binnode_macro_BASIC_h */
