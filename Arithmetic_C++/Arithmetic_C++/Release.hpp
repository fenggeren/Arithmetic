//
//  Release.h
//  Arithmetic_C++
//
//  Created by HuanaoGroup on 17/1/10.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Release_h
#define Release_h

#include <typeinfo.h>

template <typename T>
struct Cleaner
{
    static void clean(T x)
    {
#ifdef _DEBUG
        static int n = 0;
        if (7 > strlen(typeid(T).name())) {
            printf( "\t<%s>[%d]=", typeid(T).name, ++n);
            print(x);
            printf( " purged\n");
        }
#endif
    }
};

template <typename T>
struct Cleaner<T*>
{
    static void clean(T* x) {
        if (x) { delete x;}
#ifdef _DEBUG
        static int n = 0;
        printf( "\t<%s>[%d] released\n", typeid(T*).name(), ++n);
#endif
    }


};


template <typename T>
        void release(T x)
        {
            Cleaner<T>::clean(x);
        }

#endif /* Release_h */

