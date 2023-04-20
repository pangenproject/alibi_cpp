#include <iostream>
#include "Graph.h"
#include "Block.h"
#include <string>
#include <stack>

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
    typename map<T, set<T> >::iterator it = adj_list.find(val);
    if (it != adj_list.end()){
        it->second.insert(edges.begin(), edges.end());
    }
    else{
        adj_list.insert({val, edges});
    }

    // for all the connections, add the vertex to their corresponding
    // connection set
    for (T elem: edges){
        typename map<T, set<T> > :: iterator it1 = adj_list.find(elem);
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
set<T> Graph<T>:: getAdjacent(T vertex){
    return adj_list[vertex];
}

template <class T>
vector<T> Graph<T>:: outEdges(T vertex, std::map<T, Block<T>&> blocks, int ub){
    vector<T> v;
    int order = blocks.find(vertex)->second.order(blocks);
    for (auto u: this->getAdjacent(vertex)){
        int order_u = blocks.find(u)->second.order(blocks);
        if((ub >= order_u) && (order_u > order)){
            v.push_back(u);
        }
    }

    return v;
}

template <class T>
vector<T> Graph<T>::inEdges(T vertex, std::map<T, Block<T>&> blocks, int lb){
    vector<T> v;
    int order = blocks.find(vertex)->second.order(blocks);
    for (auto u: this->getAdjacent(vertex)){
        int order_u = blocks.find(u)->second.order(blocks);
        if((lb < order_u) && (order_u < order)){
            v.push_back(u);
        }
    }

    return v;
}

template <class T>
vector<T> Graph<T>::dfsF(T root, std::map<T, Block<T>&> blocks, int ub){
    std::set<T> visited ;
    std::stack<T> my_stack;
    my_stack.push(root);
    while (!my_stack.empty()){

        T node = my_stack.top();
        my_stack.pop();
        if(blocks.find(node)->second.order(blocks) == ub){
            return {};
        }
        if (!visited.count(node)){
            visited.insert(node);
            std::vector<T> v = this->outEdges(node, blocks, ub);
            for (auto el: v){
                if(!visited.count(el)){
                    my_stack.push(el);
                }
            }
        }
    }
    vector<T> vc(visited.size());
    copy(visited.begin(), visited.end(), vc.begin());

    return vc;

}

template <class T>
vector<T> Graph<T>::dfsB(T root, std::map<T, Block<T>&> blocks, int lb){
    std::set<T> visited ;
    std::stack<T> my_stack;
    my_stack.push(root);

    while (!my_stack.empty()){
        T node = my_stack.top();
        my_stack.pop();

        if (!visited.count(node)){
            visited.insert(node);
            std::vector<T> v = this->inEdges(node, blocks, lb);
            for (auto el: v){
                if(!visited.count(el)){
                    my_stack.push(el);
                }
            }
        }
    }
    vector<T> vc(visited.size());
    copy(visited.begin(), visited.end(), vc.begin());

    return vc;

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