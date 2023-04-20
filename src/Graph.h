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

public:
    set<std::pair<std::pair<T, int>, std::pair<T, int>>> fa; // set of feedback arcs
    set<std::pair<std::pair<T, int>, std::pair<T, int>>> rj; //set of reversing joins
    map<T, set<T> > adj_list;
    Graph();
    void addVertex(T val, set<T> edges);
    vector<T> outEdges(T vertex, std::map<T, Block<T>&> blocks, int ub);
    vector<T> inEdges(T vertex, std::map<T, Block<T>&> blocks, int lb);
    vector<T> dfsF(T root, std::map<T, Block<T>&> blocks, int ub);
    vector<T> dfsB(T root, std::map<T, Block<T>&> blocks, int lb);

    set<T> getAdjacent(T vertex);
};

#endif