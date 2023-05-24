#include <algorithm>
#include <vector>
#include "Block.h"
#include "Block.cpp"
#include "Graph.h"
#include "Graph.cpp"
#include "read.cpp"
#include <functional>

template <class T>
void reorder(std::vector<T> R_f, std::vector<T> R_b,  std::unordered_map<T, Block<T>&> blocks){

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
bool addEdgeWithinComponent(std::pair<std::pair<T, int>, std::pair<T, int>> e, float w, Graph<T> G, std::unordered_map<T, Block<T>&> blocks){
    T x = e.first.first;
    T y = e.second.first;
    int lb = blocks.find(y)->second.order(blocks);
    int ub = blocks.find(x)->second.order(blocks);
    if(lb == ub){
        return false;
    } else if (lb < ub) {
        std::vector<T> R_f = G.dfsF(y, blocks, ub);
        if (!R_f.empty()){
            std::vector<T> R_b = G.dfsB(x, blocks, lb);
            reorder(R_f, R_b, blocks);
            G.addVertex(x, {y});
        } else {
            return false;
        }

    } else {
        G.addVertex(x, {y});
    }
    return true;

}

//Add edge between blocks of different components
template <class T>
void addEdgeBetweenComponents(std::pair<std::pair<T, int>, std::pair<T, int>> e, Graph<T> G, std::unordered_map<T, Block<T>&> blocks){
    int reverse = 1;
    int flank = 1;
    T x = e.first.first;
    T y = e.second.first;


    if( blocks.find(x)->second.size(blocks) <  blocks.find(y)->second.size(blocks)){
        e = std::make_pair(e.second, e.first);
    }
    int side1 = e.first.second;
    int side2 = e.second.second;

    Block b1 =  blocks.find(e.first.first)->second;
    Block b2 =  blocks.find(e.second.first)->second;

    if(b1.orientation(blocks)*b2.orientation(blocks) == side1*side2){
        reverse = -1;
    }

    if(b1.orientation(blocks)*side1 < 0){
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
        } else {
            b2.uniontoMidst(b1, blocks, reverse, flank);
        }
    }

}

std::pair<Graph<int>, std::unordered_map<int, Block<int>>> linSort(std::string filename){
    std::pair<std::unordered_map<int, Block<int>>,  std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, int, hash_pair>> result = read_gfa(filename);
    std::cout << "done";
    Graph<int> G;
    std::unordered_map<int, Block<int>> blocks = result.first;


    std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, int, hash_pair> edges = result.second;

    std::unordered_map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
        G.adj_list.insert({pair.first, {}});
    }

    for (auto el: edges) {
        std::cout << "2";
        int v1 = el.first.first.first;
        int v2 = el.first.second.first;

        int o1 = el.first.first.second;
        int o2 = el.first.second.second;

        if(blocks.find(v1)->second.find(blocks_ref) == blocks.find(v2)->second.find(blocks_ref) ){

            if(blocks.find(v1)->second.orientation(blocks_ref) * blocks.find(v2)->second.orientation(blocks_ref) == o1*o2){
                G.rj.insert(el.first);
            } else if (blocks.find(v1)->second.orientation(blocks_ref) * o1 > 0){
                if (!addEdgeWithinComponent(el.first, el.second, G, blocks_ref)){
                    G.fa.insert(el.first);
                }
            } else {
                std::pair<std::pair<int, int>, std::pair<int, int>> e = std::make_pair(el.first.second, el.first.first);
                if (!addEdgeWithinComponent(e, el.second, G, blocks_ref)){
                    G.fa.insert(el.first);
                }
            }

        } else {
            addEdgeBetweenComponents(el.first, G, blocks_ref);
            G.addVertex(v1, {v2});
        }
    }

    return {G, blocks};
}