#include <iostream>
#include "src/Graph.h"
#include "src/linsort.h"
#include "src/read.h"
#include <map>

int main() {
    std::pair<Graph<int>, std::map<int, Block<int>>> result = linSort("/Users/amso/CLionProjects/alibi_cpp/tests/data/1y3b.contigs.gfa");

    std::map<int, Block<int>> blocks = result.second;

    std::map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
    }
    std::cout << "end";
}