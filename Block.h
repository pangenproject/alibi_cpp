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
    string sequence;
public:
    T id;
    int shift = 0;
    int reorder_shift = 0;
    int orient = 1;
    Block<T>* toroot;
    map<int, int> flanks = {{-1, 0}, {1,0}};
    set<T> component = {};
    Block(T id, string sequence);
    Block<T> find();
    int getId();
    void unionto(Block other, int reverse, int flank);
};


#endif