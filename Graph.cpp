#include <iostream>
#include "Graph.h"
#include <string>

using namespace std;

template <class T>
Graph<T>:: Graph(){
    ;
}

// add vertex method
template <class T>
void Graph<T>:: addVertex(T val, set<T> edges){
    //if the vertex is already created, the add the list of connections
    //to that vertex, otherwise create a new vertex and create a new set
    //of connections for the vertex
    typename map<T, set<T>>::iterator it = adj_list.find(val);
    if (it != adj_list.end()){
        it->second.insert(edges.begin(), edges.end());
    }
    else{
        adj_list.insert({val, edges});
    }

    // for all the connections, add the vertex to their corresponding
    // connection set
    for (T elem: edges){
        typename map<T, set<T>> :: iterator it1 = adj_list.find(elem);
        if (it1 != adj_list.end()){
            it1->second.insert(val);
        }
        else{
            adj_list.insert({elem, {val}});
        }
    }
}

//get neighbours of given vertex
template <class T>
set<T> Graph<T>:: getNeighbours(T vertex){
    return adj_list[vertex];
}

//override << operator. Display the adjacency list
template <class T>
inline ostream& operator<<(ostream& out, const Graph<T>& H){
    out << "{\n";
    for (typename map<T, set<T>>::const_iterator it = H.adj_list.begin(), end = H.adj_list.end(); it != end;++it){
        out << to_string(it->first) + " : ";
        for (typename set<T>::const_iterator lit = it->second.begin(), lend = it->second.end(); lit!= lend; ++lit){
            if (distance(next(lit), lend) == 0){
                out << to_string(*lit);
            }
            else{
                out << to_string(*lit) + ", ";
            }
        }
        out << "\n";
    }

    out << "}" << endl;
    return out;
}