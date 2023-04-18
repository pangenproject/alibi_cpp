#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include "Block.h"
#include "Block.cpp"
#include <map>




int main(){
    //initialize graph
    Graph<int> graph1;
    Block<int> block1(1, "actg");
    Block<int> block2(2, "actg");
    Block<int> block3(3, "actg");
    std::map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};
    block3.unionto(block2, blocks, 1, 1);
    block2.unionto(block1, blocks, 1, 1);

    cout << block3.toroot; //
    cout << block2.toroot;
    //block2.unionto(block1, 1, 1);

    //create simple tree
    //          1
    //        /   \
    //       2     3
    //      / \   / \
    //     4   5 6   7
    set<int> connections1 = {2, 3};
    set<int> connections2 = {4, 5};
    set<int> connections3 = {6, 7};

    graph1.addVertex(1, connections1);
    graph1.addVertex(2, connections2);
    graph1.addVertex(3, connections3);

    // perfrom BFS

    Graph<string> graph2;
    set<string> connectionsS1 = {"Two", "Three"};
    set<string> connectionsS2 = {"Four", "Five"};
    set<string> connectionsS3 = {"Six", "Seven"};

    graph2.addVertex("One", connectionsS1);
    graph2.addVertex("Two", connectionsS2);
    graph2.addVertex("Three", connectionsS3);

    //cout << graph1;



    return 0;
}