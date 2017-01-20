//
//  Graph.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/18.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <stdio.h>
#include "Stack.hpp"

typedef enum {UNDISCOVERED, DISCOVERED, VISITED} VStatus;
typedef enum {UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD} EType;

template <typename Tv, typename Te> //
class Graph {
private:
    void reset() {
        for (int i = 0; i < n; ++i) {
            status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1;
            parent(i) = -1; priority(i) = INT_MAX;
            for (int j = 0; j < n; ++j) {
                if (exists(i, j)) type(i, j) = UNDETERMINED;
            }
        }
    }

    void BFS ( int, int&); // 广度优先搜索算法
    void DFS ( int, int& ); // 深度优先搜索算法
    void BCC (int, int& , Stack<Tv>& ); // 基于DFS的双联通分量分解算法
    bool TSort(int, int&); // 基于DFS的拓扑排序算法
    template <typename PU> void PFS (int, PU ); // 优先级搜索框架

public:

    int n; //定点总数
    virtual int insert(Tv const& ) = 0; //插入定点，返回编号
    virtual Tv remove( int ) = 0;       // 删除定点及其关联边， 返回该定点信息
    virtual Tv& vertex ( int ) = 0;      // 定点v的数据
    virtual  int inDegree ( int ) = 0;  // 定点v的入度
    virtual  int firstNbr (int ) = 0;  // 定点v的首个邻接顶点
    virtual int nextNbr ( int, int ) = 0; // 定点v的下一个邻接顶点
    virtual VStatus& status ( int ) = 0;  //定点v的状态
    virtual int& dTime ( int ) = 0; // 定点v的时间标签dTime
    virtual int& fTime ( int ) = 0; //定点v的时间标签fTime
    virtual int& parent ( int ) = 0; // 定点v在遍历树中的父亲
    virtual int& priority (int ) = 0; // 定点v在遍历树众德优先级数

    // 边 无向边均统一转化为方向互逆的一对有向边 从而将无向图视作有向图的特例
    int e; // 边总数
    virtual bool exists(int, int ) = 0; // 边(v,u)是否存在
    virtual void insert(Te const&, int, int, int ) = 0; //在定点v和u之间插入权重为w的边
    virtual Te remove(int, int ) = 0; // 删除定点 u,v之间的变e
    virtual EType& type(int, int ) = 0; // 边 类型
    virtual Te& edge(int, int ) = 0; //边v，u的数据
    virtual int& weight( int, int ) = 0; //边v，u的权重

    // 算法
    void bfs( int ); //广度优先搜索算法
    void dfs (int ); //深度优先搜索算法
    void bcc (int ); //基于DFS的双联通分量分解算法
    Stack<Tv>* tSort(int); //基于DFS的拓扑排序算法
    void prim (int); //最小支撑树Prim算法
    void dijkstra (int ); //最短路径 Dijkstra算法
    template <typename PU> void pfs(int, PU) ; //优先级搜索框架
};


#import "Graph_Implementation.hpp"

#endif /* Graph_hpp */
