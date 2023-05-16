#import <map>

#ifndef ALIBI_CPP_SORT_H
#define ALIBI_CPP_SORT_H

std::pair<Graph<int>, std::map<int, Block<int>>> linSort(std::string infile);

template <class T>
std::vector<T> reorder(std::vector<T> R_f, std::vector<T> R_b,  std::map<T, Block<T>&> blocks);

#endif //ALIBI_CPP_SORT_H
