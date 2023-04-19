#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <iostream>
#include <list>
#include <set>
#include "Block.h"

using namespace std;

template <class T>
class Graph {

private:
    set<T> fa; // set of feedback arcs
    set<T> rj; //set of reversing joins
public:
    map<T, set<T> > adj_list;
    Graph();
    void addVertex(T val, set<T> edges);
    vector<T> outEdges(T vertex, std::map<T, Block<T>&> blocks, int ub);
    vector<T> inEdges(T vertex, std::map<T, Block<T>&> blocks, int lb);
    set<T> dfsF(T root, std::map<T, Block<T>&> blocks, int ub);
    set<T> dfsB(T root, std::map<T, Block<T>&> blocks, int lb);

    set<T> getAdjacent(T vertex);
};

#endif