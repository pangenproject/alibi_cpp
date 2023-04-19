#include "../src/Graph.h"
#include "../src/Graph.cpp"

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>


BOOST_AUTO_TEST_CASE(creation_of_the_graph_node_int) {
    Graph<int> graph1;
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


}


BOOST_AUTO_TEST_CASE(creation_of_the_graph_node_string) {
    Graph<int> graph1;
    //create simple tree
    //          a
    //        /   \
    //       b     c
    //      / \   / \
    //     d   e f   g

    Graph<string> graph2;
    set<string> connectionsS1 = {"b", "c"};
    set<string> connectionsS2 = {"d", "e"};
    set<string> connectionsS3 = {"f", "g"};

    graph2.addVertex("One", connectionsS1);
    graph2.addVertex("Two", connectionsS2);
    graph2.addVertex("Three", connectionsS3);
    set<int> connections1 = {2, 3};
    set<int> connections2 = {4, 5};
    set<int> connections3 = {6, 7};

    graph1.addVertex(1, connections1);
    graph1.addVertex(2, connections2);
    graph1.addVertex(3, connections3);

    cout << graph1;

}