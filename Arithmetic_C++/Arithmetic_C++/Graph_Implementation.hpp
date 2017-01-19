//
//  Graph.cpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/18.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#include "Graph.hpp"
#include "Queue.hpp"

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int & clock) {
    Queue_List<int> Q;
    status(v) = DISCOVERED; Q.enqueue(v);
    while (!Q.empty()) {
        int v = Q.dequeue(); dTime(v) = ++clock;
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) { // 枚举v的所有邻居u
            if (UNDISCOVERED == status(u)) {
                status(u) = DISCOVERED; Q.enqueue(u);
                type(v, u) = TREE; parent(u) = v;
            } else {
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

