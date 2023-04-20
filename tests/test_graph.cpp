#include "../src/Graph.h"
#include "../src/Graph.cpp"

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>


BOOST_AUTO_TEST_CASE(creation_of_the_graph_node_int_cycle) {
    Graph<int> graph1;
    //create simple graph
    //          1
    //        /
    //       1

    set<int> connections1 = {1};

    graph1.addVertex(1, connections1);
    set<int> expected = {1};

    BOOST_CHECK_EQUAL_COLLECTIONS(graph1.adj_list.find(1)->second.begin(), graph1.adj_list.find(1)->second.end(),
                                  expected.begin(), expected.end());
}


BOOST_AUTO_TEST_CASE(creation_of_the_tree_node_string) {
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

BOOST_AUTO_TEST_CASE(DFSB_for_blocs){
    Block<int> b1(1, "actg");
    Block<int> b2(2, "ccaa");
    Block<int> b3(3, "ttgg");
    Block<int> b4(4, "aatc");
    Block<int> b5(5, "aatc");
    std::map<int, Block<int>&> blocks = {{1, b1}, {2, b2}, {3, b3}, {4, b4},  {5, b5}};

    b4.unionto(b1, blocks, 1, 1);
    b3.unionto(b1, blocks, 1, 1);
    b2.unionto(b4, blocks, 1, 1);
    b5.unionto(b2, blocks, 1, 1);

    Graph<int> graph1;

    set<int> connections1 = {3, 4};

    graph1.addVertex(1, connections1);
    graph1.addVertex(4, {2});
    graph1.addVertex(2, {5});

    int lb = 2;
    std::vector<int> output = graph1.dfsB(5, blocks, 2);
    std::vector<int> expected = {2, 5};
    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(DFSF_for_blocs){
    Block<int> b1(1, "actg");
    Block<int> b2(2, "ccaa");
    Block<int> b3(3, "ttgg");
    Block<int> b4(4, "aatc");
    Block<int> b5(5, "aatc");
    std::map<int, Block<int>&> blocks = {{1, b1}, {2, b2}, {3, b3}, {4, b4},  {5, b5}};

    b4.unionto(b1, blocks, 1, 1);
    b3.unionto(b1, blocks, 1, 1);
    b2.unionto(b4, blocks, 1, 1);
    b5.unionto(b2, blocks, 1, 1);

    Graph<int> graph1;

    set<int> connections1 = {3, 4};

    graph1.addVertex(1, connections1);
    graph1.addVertex(4, {2});
    graph1.addVertex(2, {5});

    int ub = 4;
    std::vector<int> output = graph1.dfsF(3, blocks, ub);
    std::vector<int> expected = {3};
    BOOST_CHECK_EQUAL_COLLECTIONS(output.begin(), output.end(),
                                  expected.begin(), expected.end());
}