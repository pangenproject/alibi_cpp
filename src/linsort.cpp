#include <algorithm>
#include <vector>
#include "Block.h"
#include "Block.cpp"
#include "Graph.h"
#include "Graph.cpp"


template <class T>
void reorder(std::vector<T> R_f, std::vector<T> R_b,  std::map<T, Block<T>&> blocks){

    std::sort(R_f.begin(), R_f.end(), [&](T x, T y){
        return blocks.find(x)->second.order(blocks) < blocks.find(y)->second.order(blocks);
    });

    std::sort(R_b.begin(), R_b.end(), [&](T x, T y){
        return blocks.find(x)->second.order(blocks) < blocks.find(y)->second.order(blocks);
    });


    R_b.insert(R_b.end(), R_f.begin(), R_f.end());


    std::vector<int> O;
    for(auto v: R_b){
       O.push_back(blocks.find(v)->second.order(blocks));
    }
    std::sort(O.begin(), O.end());

    for(int i = 0; i < O.size(); i++){
        blocks.find(R_b[i])->second.reorder(blocks, O[i]);
    }


}

template <class T>
void addEdgeWithinComponent(std::pair<std::pair<T, int>, std::pair<T, int>> e, float w, Graph<T> G, std::map<T, Block<T>&> blocks){
    T x = e.first.first;
    T y = e.second.first;
    int lb = blocks.find(x)->second.order(blocks);
    int ub = blocks.find(y)->second.order(blocks);
    if(lb == ub){
        G.fa.insert(e); //modyfikacja dla krawedzi
    } else if (lb < ub) {
        std::vector<T> R_f = G.dfsF(y, blocks, ub);
        if (!R_f.empty()){
            std::vector<T> R_b = G.dfsB(x, blocks, lb);
            reorder(R_f, R_b, blocks);
            G.addVertex(x, {y});
        } else {
            G.fa.insert(e);
        }

    } else {
        G.addVertex(x, {y});
    }

}

//Add edge between blocks of different components
template <class T>
void addEdgeBetweenComponents(std::pair<std::pair<T, int>, std::pair<T, int>> e, std::map<T, Block<T>&> blocks, Graph<T> G){
    int reverse = 1;
    int flank = 1;
    T x = e.first.first;
    T y = e.second.first;
    int side1 = e.second.first;
    int side2 = e.second.second;

    if( blocks.find(x)->second.size(blocks) <  blocks.find(y)->second.size(blocks)){
        e = std::make_pair(e.second, e.first);
    }

    Block b1 =  blocks.find(x)->second;
    Block b2 =  blocks.find(y)->second;

    if(b1.orentation(blocks)*b2.orientation(blocks) == side1*side2){
        reverse = -1;
    }

    if(b1.orentation(blocks)*side1 < 0){
        flank = - 1;
    }

    if(flank == 1 && b1.order(blocks) == b1.maximum(blocks)){
        b2.unionto(b1, blocks, reverse, flank);
    } else if (flank == -1 && b1.order(blocks) == b1.minimum(blocks)){
        b2.unionto(b1, blocks, reverse, flank);
    } else {
        int c_end = 0;
        int c_mnist = 0;
        if(flank == 1){
            c_end += b1.maximum(blocks) - b1.order(blocks);
        } else {
            c_end += b1.order(blocks) - b1.minimum(blocks);
        }
        int k = b2.size(blocks);

        c_mnist += k * G.getAdjacent(e.first.first).size();

        if(c_end < c_mnist){
            b2.unionto(b1, blocks, reverse, flank);
        } else{
            b2.uniontoMidst(b1, blocks, reverse, flank);
        }
    }

}
