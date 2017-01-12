//
//  avl_macro.h
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/12.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef avl_macro_h
#define avl_macro_h

/**
 左右孩子中取更高者
 */

// 等高时候， 与父亲x同侧者 优先  zig-zig / zag-zag   LL/RR
#define tallerChild(x) ( \
    stature( (x)->lc ) > stature( (x)->rc ) ? x->lc : ( \
    stature( (x)->lc ) < stature( (x)->rc ) ? x->rc : ( \
    IsLChild(* (x) ) ? (x)->lc : (x)->rc                \
    )  \
    )  \
)


#endif /* avl_macro_h */
