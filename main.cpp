#include <iostream>
#include "src/Block.h"
#include "src/Graph.h"
#include "src/linsort.h"
#include "src/read.h"
#include <map>

int main() {
    std::pair<Graph<int>, std::map<int, Block<int>>> result = linSort("../data/test.gfa");

    std::map<int, Block<int>> blocks = result.second;

    std::map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
    }

}