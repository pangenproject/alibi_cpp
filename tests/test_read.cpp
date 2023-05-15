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
BOOST_AUTO_TEST_CASE(connect_gfa_nodes_test){
    std::pair<std::pair<int, int>, std::pair<int, int>> expected = {{10, 1},{11, 1}};
    std::pair<int, int> v1  = {10, 1};
    std::pair<int, int> v2  = {11, -1};


    std::pair<std::pair<int, int>, std::pair<int, int>> v = connect_gfa_nodes(v1, v2);
    BOOST_TEST(v.first.first == expected.first.first);
    BOOST_TEST(v.first.second == expected.first.second);
    BOOST_TEST(v.second.first == expected.second.first);
    BOOST_TEST(v.second.second == expected.second.second);
}


BOOST_AUTO_TEST_CASE(weight_gfa_read){
    std::vector<std::string> string_input = {"11+", "12-", "13+"};
    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, int> expected;

    std::pair<int, int> v1  = {10, 1};
    std::pair<int, int> v2  = {11, 1};
    std::pair<int, int> v3  = {11, -1};
    std::pair<int, int> v4  = {12, -1};
    expected.insert({{v1, v2}, 1});
    expected.insert({{v3, v4}, 1});

    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, int> output;

    weight_gfa(string_input, output);

    BOOST_TEST(expected.find({v1, v2})->first.first.first == output.find({v1, v2})->first.first.first);
    BOOST_TEST(expected.find({v1, v2})->first.first.second == output.find({v1, v2})->first.first.second);
    BOOST_TEST(expected.find({v3, v4})->first.first.first == output.find({v3, v4})->first.first.first);
    BOOST_TEST(expected.find({v3, v4})->first.first.second == output.find({v3, v4})->first.first.second);
}

BOOST_AUTO_TEST_CASE(gfa_read) {

    read_gfa<int, std::pair<int, char>>("../data/test.gfa");

}

