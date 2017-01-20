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
        for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
            if (UNDISCOVERED == status(u)) {
                status(u) == DISCOVERED; Q.enqueue(u);
                type(v, u) = TREE; parent(u) = v;
            } else {
                type(v, u) = CROSS;
            }
        }
        status(v) = VISITED;
    }
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) {
    reset();
    int clock = 0; int v = s;

    do {
        if (UNDISCOVERED == status(v))
            BFS(v, clock);
    } while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
struct BfsPU
{
    virtual void operator()( Graph<Tv, Te>* g, int uk, int v) {
        if (g->status(v) == UNDISCOVERED) {
            if (g->priority(v) > g->priority(uk) + 1) {
                g->priority(v) = g->priority(uk) + 1;
                g->parent(v) = uk;
            }
        }
    }
};


template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
    dTime(v) = ++clock; status(v) = DISCOVERED;
    // 会遍历每一条边
    for (int u = firstNbr(v); -1 < u; u = nextNbr(v, u)) {
        switch(status(u)) {
            case UNDISCOVERED:   // 构成遍历树（森林）
                type(v, u) = TREE; parent(u) = v; DFS(u, clock);
                break;
            case DISCOVERED:
                type(v, u) = BACKWARD;
                break;
            default:
                type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
                break;
        }
    }
    status(v) = VISITED; fTime(v) = ++clock;
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) {
    reset(); int clock = 0; int v = s;
    do {
        if (UNDISCOVERED == status(v))
            DFS(v, clock);
    } while( s != ( v = ( ++v % n ) ) );
}


#define hca(x) (fTime(x))

template <typename Tv, typename Te>
void Graph<Tv, Te>::BCC(int v, int & clock, Stack<Tv> & S) {
    hca(v) = dTime(v) = ++clock; status(v) = DISCOVERED; S.push(v);
    
}


