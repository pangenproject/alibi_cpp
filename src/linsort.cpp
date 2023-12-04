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
bool addEdgeWithinComponent(std::tuple<int, int, int, int> e, float w, Graph<T> G, std::unordered_map<T, Block<T>&> blocks){
    T x = std::get<0>(e);
    T y = std::get<3>(e);
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
void addEdgeBetweenComponents(std::tuple<int, int, int, int> e, Graph<T> G, std::unordered_map<T, Block<T>&> blocks){
    int reverse = 1;
    int flank = 1;
    int x = std::get<0>(e);
    int y = std::get<2>(e);;


    if( blocks.find(x)->second.size(blocks) <  blocks.find(y)->second.size(blocks)){
        e = std::make_tuple(std::get<2>(e), std::get<3>(e), std::get<0>(e), std::get<1>(e));
    }
    int side1 = std::get<1>(e);
    int side2 = std::get<3>(e);

    Block b1 =  blocks.find(std::get<0>(e))->second;
    Block b2 =  blocks.find(std::get<2>(e))->second;

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

        c_mnist += k * G.getAdjacent(std::get<0>(e)).size();

        if(c_end <= c_mnist){
            b2.unionto(b1, blocks, reverse, flank);
        } else {
            b2.uniontoMidst(b1, blocks, reverse, flank);
        }
    }

}

std::pair<Graph<int>, std::unordered_map<int, Block<int>>> linSort(std::string filename){
    std::pair<std::unordered_map<int, Block<int>>,  std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair>> result = read_gfa(filename);
    std::cout << "done";
    Graph<int> G;
    std::unordered_map<int, Block<int>> blocks = result.first;


    std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair> edges = result.second;

    std::unordered_map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
        G.adj_list.insert({pair.first, {}});
    }
    int count = 0;
    for (auto& el : edges) {
        // Uzyskanie dostępu do klucza i wartości z elementu mapy
        const std::tuple<int, int, int, int>& edgeKey = el.first;
        int edgeValue = el.second;

        // Uzyskanie poszczególnych wartości z krotki
        int v1 = std::get<0>(edgeKey);
        int v2 = std::get<2>(edgeKey);

        int o1 = std::get<1>(edgeKey);
        int o2 = std::get<3>(edgeKey);

        //std::cout <<count <<"\n";
        if(blocks.find(v1)->second.find(blocks_ref) == blocks.find(v2)->second.find(blocks_ref) ){

            if(blocks.find(v1)->second.orientation(blocks_ref) * blocks.find(v2)->second.orientation(blocks_ref) == o1*o2){
                G.rj.insert(el.first);
            } else if (blocks.find(v1)->second.orientation(blocks_ref) * o1 > 0){
                if (!addEdgeWithinComponent(el.first, el.second, G, blocks_ref)){
                    G.fa.insert(el.first);
                }
            } else {
                std::tuple<int, int, int, int> e = {std::get<3>(el.first), std::get<2>(el.first), std::get<0>(el.first), std::get<1>(el.first)};
                if (!addEdgeWithinComponent(e, el.second, G, blocks_ref)){
                    G.fa.insert(el.first);
                }
            }

        } else {
            addEdgeBetweenComponents(el.first, G, blocks_ref);
            G.addVertex(v1, {v2});
        }
        count += 1;
    }

    return {G, blocks};
}