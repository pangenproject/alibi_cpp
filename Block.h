#ifndef BLOCK_H
#define BLOCK_H

#include <map>
#include <iostream>
#include <list>
#include <set>
#include <string>

using namespace std;

template <class T>
class Block {

private:
    T id;
    string sequence;
public:
    int shift = 0;
    int reorder_shift = 0;
    int orient = 1;
    Block<T>* toroot;
    map<int, int> flanks = {{-1, 0}, {1,0}};
    set<T> component = {};
    Block(T id, string sequence);
    Block<T> find();
    void unionto(Block other, int reverse, int flank);
};


#endif