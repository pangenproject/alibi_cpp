#include <algorithm>
#include "Block.h"
#include "Block.cpp"
#include "Graph.h"
#include "Graph.cpp"


template <class T>
std::vector<T> reorder(std::vector<T> R_f, std::vector<T> R_b,  std::map<T, Block<T>&> blocks){

    std::sort(R_f.begin(), R_f.end(), [&](T x, T y){
        return blocks.find(x)->second.order(blocks) < blocks.find(y)->second.order(blocks);
    });

    for(auto v: R_f){
        std::cout << v << "to na pewno";
    }


    return R_f;

}