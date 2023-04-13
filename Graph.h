#ifndef GRAPH_H
#define GRAPH_H

#include <map>
#include <iostream>
#include <list>
#include <set>

using namespace std;

template <class T>
class Graph{

private:
    set<T> fa; // set of feedback arcs
    set<T> rj; //set of reversing joins
public:
    map<T, set<T>> adj_list;
    Graph();
    void addVertex(T val, set<T> edges);
    set<T> getNeighbours(T vertex);
};

#endif