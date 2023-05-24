#include <iostream>
#include "src/Graph.h"
#include "src/linsort.h"
#include "src/read.h"
#include <map>

int main() {
    std::pair<Graph<int>, std::unordered_map<int, Block<int>>> result = linSort("/Users/amso/CLionProjects/alibi_cpp/tests/data/simData_10_10_1.gfa");

    std::unordered_map<int, Block<int>> blocks = result.second;

    std::unordered_map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
    }
    std::cout << "end";
}