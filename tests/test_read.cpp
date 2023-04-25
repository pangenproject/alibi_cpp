#include "../src/read.cpp"
#include <boost/test/data/test_case.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>


BOOST_AUTO_TEST_CASE(split_string) {
    std::vector<std::string> expected = {"L", "11", "+", "12", "-", "4M"};

    std::vector<std::string> returned =  split("L\t11\t+\t12\t-\t4M", '\t');

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), returned.begin(), returned.end());

}

BOOST_AUTO_TEST_CASE(split_string_by_comma) {
    std::vector<std::string> expected = {"11+","12-","13+"};

    std::vector<std::string> returned =  split("11+,12-,13+", ',');

    BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), returned.begin(), returned.end());

}

BOOST_AUTO_TEST_CASE(gfa_read) {

    read_gfa<int, std::pair<int, char>>("../data/test.gfa");

}

