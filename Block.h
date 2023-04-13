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
    map<int, int> flanks = {{-1, 0}, {1,0}};
    set<T> component = {id};
    Block(T id, string sequence);

};

#endif