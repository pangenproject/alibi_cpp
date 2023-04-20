#include "../src/Block.h"
#include "../src/linsort.cpp"
#include <map>
#include <vector>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>

BOOST_AUTO_TEST_CASE(sort_blocks) {
    std::vector<int> R_f = {3};
    std::vector<int> R_b = {2, 5};
    Block<int> b1(1, "actg");
    Block<int> b2(2, "ccaa");
    Block<int> b3(3, "gg");
    Block<int> b4(4, "aa");
    Block<int> b5(5, "aatc");

    std::map<int, Block<int>&> blocks = {{1, b1}, {2, b2}, {3, b3}, {4, b4},  {5, b5}};

    b4.unionto(b1, blocks, 1, 1);
    b3.unionto(b1, blocks, 1, 1);
    b2.unionto(b4, blocks, 1, 1);
    b5.unionto(b2, blocks, 1, 1);


    reorder(R_f, R_b, blocks);
    std::vector<int> orders = {b1.order(blocks), b4.order(blocks), b2.order(blocks), b5.order(blocks), b3.order(blocks)};
    std::vector<int> expected = {0, 1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(orders.begin(), orders.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(sort_blocks_add_edges_within_component) {
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
    std::pair first = std::make_pair(5,1);
    std::pair second = std::make_pair(3,-1);
    std::pair<std::pair<int, int>, std::pair<int, int>> v  = std::make_pair(first, second);
    addEdgeWithinComponent(v, 1, graph1, blocks);

    std::vector<int> orders = {b1.order(blocks), b4.order(blocks), b2.order(blocks), b5.order(blocks), b3.order(blocks)};

    std::vector<int> expected = {0, 1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(orders.begin(), orders.end(),
                                  expected.begin(), expected.end());
}