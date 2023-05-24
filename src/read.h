#include "map"
#include "Block.h"

#ifndef TESTS_READ_H
#define TESTS_READ_H


int strand(char x);

template <class T>
std::pair<std::pair<T, int>, std::pair<T, int>> connect_gfa_nodes(std::pair<T, int> v1, std::pair<T, int> v2);

std::vector<std::string> split_s(std::string line, char sep);

template <class T>
void weight_gfa(std::vector<std::string> line, std::unordered_map<std::pair<std::pair<T, int>, std::pair<T, int>>, int> &result);


std::pair<std::unordered_map<int, Block<int>&>,  std::unordered_map<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> read_gfa(std::string gfa_file);

#endif //TESTS_READ_H
