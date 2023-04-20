#include "../src/Block.h"
#include "../src/linsort.cpp"
#include <map>
#include <vector>

#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>

BOOST_AUTO_TEST_CASE(sort_blocks) {
    std::vector<int> R_f = {3, 2, 1};
    std::vector<int> R_b = {};
    Block<int> block1(1, "actg");
    Block<int> block2(2, "actg");
    Block<int> block3(3, "actg");
    std::map<int, Block<int>&> blocks = {{1, block1}, {2, block2}, {3, block3}};

    block3.unionto(block1, blocks, 1, 1);
    block1.unionto(block2, blocks, 1, 1);

    std::vector<int> v = reorder(R_f, R_f, blocks);
    std::vector<int> expected = {1, 2, 3, 1, 2, 3};
    BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(),
                                  expected.begin(), expected.end());
}