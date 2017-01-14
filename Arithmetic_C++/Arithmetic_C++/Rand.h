//
//  Rand.h
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/14.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Rand_h
#define Rand_h

#include <stdlib.h>
#include <time.h>

static  int dice(int range) { return rand() % range; }
static int dice(int low, int high) { return low + rand() % (high - low) ; }
static  float dice(float range) { return rand() % (1000 * (int) range) / (float)1000; }
static double dice(double range) { return rand() % (1000 * (int)range) / (double)1000; }
static char dice(char range) { return (char)( 32 + rand() % 96);}


#endif /* Rand_h */
