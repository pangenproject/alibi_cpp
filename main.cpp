#include <iostream>
#include "Graph.h"
#include "Graph.cpp"
#include "Block.h"
#include "Block.cpp"


using namespace std;



int main(){
    //initialize graph
    Graph<int> graph1;
    Block<int> block1(1, "actg");

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