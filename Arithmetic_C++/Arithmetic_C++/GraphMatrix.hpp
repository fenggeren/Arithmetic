//
//  GraphMatrix.hpp
//  Arithmetic_C++
//
//  Created by fenggeren on 2017/1/18.
//  Copyright © 2017年 HuanaoGroup. All rights reserved.
//

#ifndef GraphMatrix_h
#define GraphMatrix_h


#include "Graph.hpp"
#include "Vector.hpp"

template <typename Tv>
struct Vertex
{
    Tv data; int inDegree, outDegree; VStatus status; // 访问状态
    int dTime, fTime;  // discovered、finished    发现节点、完成访问节点<所有的临界点都已发现>
    int parent; int priority; // 父节点、优先级数

    Vertex(Tv const& d = (Tv) 0):
            data(d), inDegree(0), outDegree(0), status(UNDISCOVERED),
            dTime(-1), fTime(-1), parent(-1), priority(INT_MAX) {}
};

template <typename Te>
struct Edge
{
    Te data; int weight; EType type;
    Edge( Te const& d, int w): data(d), weight(w), type(UNDETERMINED) {}
};


template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te>
{
private:
    Vector<Vertex<Tv>> V;
    Vector<Vector<Edge<Te>*>> E;

public:
    GraphMatrix() { n = e = 0; }
    ~GraphMatrix() {
        for (int j = 0; j < n; j++) {
            for ( int k = 0; k < n; k ++)
                delete E[j][k];
        }
    }

    virtual Tv& vertex(int i) { return V[i].data; }
    virtual int inDegree(int i ) { return V[i].inDegree; }
    virtual int outDegree(int i) { return V[i].outDegree; }
    virtual int firstNbr(int i) { return nextNbr(i, n);}
    virtual int nextNbr(int i, int j) {  // 倒序遍历
        while(-1 < j && (!exists(i, --j))) ;
        return j;
    }

    virtual VStatus& status(int i) { return V[i].status; }
    virtual int& dTime(int i) { return V[i].dTime; }
    virtual int& fTime(int i) { return V[i].fTime; }
    virtual int& parent(int i) { return V[i].parent; }
    virtual int& priority(int i) { return V[i].priority; }

    virtual int insert(Tv const& vertex) {
        for (int j = 0; j < n; j++) E[j].insert(nullptr); n++;
        E.insert(Vector<Edge<Te>*>(n, n, (Edge<Te> *) nullptr));
        return V.insert(Vertex<Tv>(vertex));
    }

    virtual Tv remove(int i) {
        for (int j = 0; j < n; j++) {
            if (exists(i, j)) { delete E[i][j]; V[j].inDegree--; }
        }
        E.remove(i); n--;
        auto vBak = vertex(i); V.remove(i);
        for (int j = 0; j < n; j++) {
            if (auto e = E[j].remove(i)) { delete e; V[j].outDegree--; }
            return vBak;
        }
    }
};

#endif /* GraphMatrix_h */
