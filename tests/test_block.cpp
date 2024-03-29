#include "../src/Block.cpp"
#include <map>
#include <unordered_map>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>


BOOST_AUTO_TEST_CASE(block_union_to_for_tree_blocks) {
            Block<int> block1(1, "actg");
            Block<int> block2(2, "actg");
            Block<int> block3(3, "actg");
            std::unordered_map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};
            block3.uniontoMidst(block2, blocks, 1, 1);
            block2.unionto(block1, blocks, 1, 1);
            block3.find(blocks);

            int id3 = block3.toroot; // 1
            int id2 = block2.toroot; // 1

            BOOST_TEST(id3 == 1);
            BOOST_TEST(id2 == 1);

}

BOOST_AUTO_TEST_CASE(block_union_to_two_blocks) {
    Block<int> block1(1, "actg");
    Block<int> block2(2, "actg");
    std::unordered_map<int, Block<int>&> blocks;
    blocks.insert({1, block1});
    blocks.insert({2, block2});
    int flank = 1;
    int reverse = -1;
    block2.unionto(block1, blocks, reverse, flank);

    BOOST_TEST(block1.orient == 1);
    BOOST_TEST(block2.orient == -1);
}

BOOST_AUTO_TEST_CASE(block_union_mid_to_three_blocks) {
    Block<int> block1(1, "actg");
    Block<int> block2(2, "actg");
    Block<int> block3(3, "actg");
    std::unordered_map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};

    block2.unionto(block1, blocks, 1, 1);
    block3.uniontoMidst(block1, blocks, 1,1);

    BOOST_TEST(block1.order(blocks) == 0);
    BOOST_TEST(block3.order(blocks) == 1);
    BOOST_TEST(block2.order(blocks) == 2);
}

BOOST_AUTO_TEST_CASE(block_union_mid_to_six_blocks) {
    Block<int> block1(1, "ac");
    Block<int> block2(2, "ggt");
    Block<int> block3(3, "ctt");
    Block<int> block4(4, "aat");
    Block<int> block5(5, "gat");
    Block<int> block6(6, "aa");


    std::unordered_map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}, {4, block4}, {5, block5},  {6, block6}};


    block2.unionto(block1, blocks, 1, 1);
    block3.unionto(block2, blocks, 1, 1);
    block4.unionto(block3, blocks, 1, 1);
    block5.unionto(block4, blocks,1, 1);
    block6.uniontoMidst(block1, blocks, 1, 1);



    BOOST_TEST(block1.order(blocks) == 0);
    BOOST_TEST(block6.order(blocks) == 1);
    BOOST_TEST(block2.order(blocks) == 2);
    BOOST_TEST(block3.order(blocks) == 3);
    BOOST_TEST(block4.order(blocks) == 4);
    BOOST_TEST(block5.order(blocks) == 5);
}

BOOST_AUTO_TEST_CASE(block_union_two_to_three_blocks) {
    Block<int> block1(1, "actg");
    Block<int> block2(2, "actg");
    Block<int> block3(3, "actg");
    std::unordered_map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};

    block3.unionto(block1, blocks, 1, 1);
    block1.unionto(block2, blocks, 1, 1);


    BOOST_TEST(block1.order(blocks) == 1);
    BOOST_TEST(block3.order(blocks) == 2);
    BOOST_TEST(block2.order(blocks) == 0);
}