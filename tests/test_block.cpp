#include "../src/Block.h"
#include "../src/Block.cpp"
#include <map>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>


BOOST_AUTO_TEST_CASE(block_union_to_for_tree_blocks) {
            Block<int> block1(1, "actg");
            Block<int> block2(2, "actg");
            Block<int> block3(3, "actg");
            std::map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};
            block3.uniontoMidst(block2, blocks, 1, 1);
            block2.unionto(block1, blocks, 1, 1);
            block3.find(blocks);

            int id3 = block3.toroot; // 1
            int id2 = block2.toroot; // 1

            BOOST_TEST(id3 == 1);
            BOOST_TEST(id2 == 1);

}

