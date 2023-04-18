#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <iostream>
#include <list>
#include <set>
#include <string>


template <class T>
class Block {

private:
    std::string sequence;
public:
    T id;
    int shift = 0;
    int reorder_shift = 0;
    int orient = 1;
    T toroot;
    std::map<int, int> flanks = {{-1, 0}, {1,0}};
    std::set<T> component = {};
    Block(T id, std::string sequence);
    T& find(std::map<T, Block<T>&> &blocks);
    void unionto(Block other, std::map<T, Block<T>&> blocks, int reverse, int flank);
    void uniontoMidst(Block other, std::map<T, Block<T>&> blocks, int reverse, int flank);

    int orientation(std::map<T, Block<T>&> blocks);
    void setRoot(T id);

    int order(std::map<T, Block<T> &> blocks);
    void reorder(std::map<T, Block<T>&> blocks, int n);

    int minimum(std::map<T, Block<T>&> blocks);
    int maximum(std::map<T, Block<T>&> blocks);
};


#endif