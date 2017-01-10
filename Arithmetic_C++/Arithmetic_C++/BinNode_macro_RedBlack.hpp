//
//  BinNode_macro_RedBlack.h
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/10.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BinNode_macro_RedBlack_h
#define BinNode_macro_RedBlack_h

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (! IsBlack(p))

// 黑高更新条件
#define BlackHeightUpdated(x) (  \
    (stature((x).lc) == stature((x).rc)) && \
    ( (x).height == ( IsRed(&x) ? stature( (x).lc) : stature( (x).lc) + 1 )) \
    )



#endif /* BinNode_macro_RedBlack_h */
