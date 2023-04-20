#include <algorithm>
#include <vector>
#include "Block.h"
#include "Block.cpp"
#include "Graph.h"
#include "Graph.cpp"


template <class T>
std::vector<T> reorder(std::vector<T> R_f, std::vector<T> R_b,  std::map<T, Block<T>&> blocks){

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

    return O;

}