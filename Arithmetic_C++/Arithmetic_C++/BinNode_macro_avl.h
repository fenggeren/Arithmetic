//
//  BinNode_macro_avl.h
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef BinNode_macro_avl_h
#define BinNode_macro_avl_h


#define HeightUpdated(x)  \
        ( (x).height == 1 + max (stature((x).lc), stature((x).rc)))

// 理想平衡
#define Balanced(x) (stature(x).lc) == stature(x).rc))

// 平衡因子
#define BalFac(x) (stature((x).lc) - stature((x).rc))

// 平衡条件， 左右子树高度差 <=1
#define AvlBalance(x) ( ( -2 < BalFac(x) ) && (BalFac(x) < 2 ) )

#endif /* BinNode_macro_avl_h */
