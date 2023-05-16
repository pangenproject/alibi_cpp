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

BOOST_AUTO_TEST_CASE(sort_blocks_addEdgeBetweenComponents) {
    Block<int> b1(1, "ac");
    Block<int> b2(2, "ggt");
    Block<int> b3(3, "ctt");
    Block<int> b4(4, "aa");
    Block<int> b5(5, "gat");


    std::map<int, Block<int>&> blocks = {{1, b1}, {2, b2}, {3, b3}, {4, b4},  {5, b5}};

    b2.unionto(b1, blocks, 1, 1);
    b3.unionto(b2, blocks, 1, 1);
    b5.unionto(b4, blocks, 1, 1);

    Graph<int> graph1;

    graph1.addVertex(1, {2});
    graph1.addVertex(2, {3});
    graph1.addVertex(4, {5});


    std::pair first = std::make_pair(2, 1);
    std::pair second = std::make_pair(4,-1);
    std::pair<std::pair<int, int>, std::pair<int, int>> v  = std::make_pair(first, second);
    addEdgeBetweenComponents(v, graph1, blocks);


    std::vector<int> orders = {b1.order(blocks), b2.order(blocks), b3.order(blocks), b4.order(blocks), b5.order(blocks)};


    std::vector<int> expected = {0, 1, 2, 3, 4};
    BOOST_CHECK_EQUAL_COLLECTIONS(orders.begin(), orders.end(),
                                  expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(sort_blocks_addEdgeBetweenComponents_with_midst) {
    Block<int> b1(1, "ac");
    Block<int> b2(2, "ggt");
    Block<int> b3(3, "ctt");
    Block<int> b4(4, "aat");
    Block<int> b5(5, "gat");
    Block<int> b6(6, "aa");

    std::map<int, Block<int>&> blocks = {{1, b1}, {2, b2}, {3, b3}, {4, b4},  {5, b5}, {6, b6}};

    b2.unionto(b1, blocks, 1, 1);
    b3.unionto(b2, blocks, 1, 1);
    b4.unionto(b3, blocks, 1, 1);
    b5.unionto(b4, blocks, 1, 1);

    Graph<int> graph1;

    graph1.addVertex(1, {2});
    graph1.addVertex(2, {3});
    graph1.addVertex(3, {4});
    graph1.addVertex(4, {5});
    graph1.addVertex(6, {});

    std::pair first = std::make_pair(1, 1);
    std::pair second = std::make_pair(6,-1);

    std::pair<std::pair<int, int>, std::pair<int, int>> v  = std::make_pair(first, second);

    addEdgeBetweenComponents(v, graph1, blocks);


    std::vector<int> orders = {b1.order(blocks), b6.order(blocks), b2.order(blocks), b3.order(blocks), b4.order(blocks), b5.order(blocks)};

    std::vector<int> expected = {0, 1, 2, 3, 4, 5};
    BOOST_TEST(b1.order(blocks) == 0);
    BOOST_TEST(b6.order(blocks) == 1);
    BOOST_TEST(b2.order(blocks) == 2);
    BOOST_TEST(b3.order(blocks) == 3);
    BOOST_TEST(b4.order(blocks) == 4);
    BOOST_TEST(b5.order(blocks) == 5);

}

BOOST_AUTO_TEST_CASE(linsort_main_function) {
    std::pair<Graph<int>, std::map<int, Block<int>>> result = linSort("../data/test.gfa");

    std::map<int, Block<int>> blocks = result.second;

    std::map<int, Block<int>&> blocks_ref;

    // Przepisanie mapy obiektów na mapę referencji
    for (auto& pair : blocks) {
        blocks_ref.insert({pair.first, std::ref(pair.second)});
    }

    BOOST_TEST(blocks.find(11)->second.order(blocks_ref) == 0);
    BOOST_TEST(blocks.find(12)->second.order(blocks_ref) == 1);
    BOOST_TEST(blocks.find(13)->second.order(blocks_ref) == 2);
    BOOST_TEST(blocks.find(11)->second.orientation(blocks_ref)== 1);
    BOOST_TEST(blocks.find(12)->second.orientation(blocks_ref)== -1);
    BOOST_TEST(blocks.find(13)->second.orientation(blocks_ref)== 1);


}

