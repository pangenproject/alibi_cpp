#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <unordered_map>

template <class T>
class Block {

private:
    std::string sequence;
public:
    T id;
    int shift;
    int reorder_shift;
    int orient;
    T toroot;
    std::unordered_map<int, int> flanks;
    std::set<T> component;
    Block(T id, std::string sequence);
    T find(std::unordered_map<T, Block<T>&> &blocks);
    void unionto(Block other, std::unordered_map<T, Block<T>&> blocks, int reverse, int flank);
    void uniontoMidst(Block other, std::unordered_map<T, Block<T>&> blocks, int reverse, int flank);

    int orientation(std::unordered_map<T, Block<T>&> blocks);
    void setRoot(T id);

    int order(std::unordered_map<T, Block<T>&> blocks);
    void setShift(int s);
    void reorder(std::unordered_map<T, Block<T>&> blocks, int n);
    int size(std::unordered_map<T, Block<T>&> blocks);

    int minimum(std::unordered_map<T, Block<T>&> blocks);
    int maximum(std::unordered_map<T, Block<T>&> blocks);
};


#endif