#import <map>
#ifndef ALIBI_CPP_SORT_H
#define ALIBI_CPP_SORT_H

template <class T>
std::vector<T> reorder(std::vector<T> R_f, std::vector<T> R_b,  std::map<T, Block<T>&> blocks);

#endif //ALIBI_CPP_SORT_H
