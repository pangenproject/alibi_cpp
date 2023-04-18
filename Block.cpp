#include <iostream>
#include "Block.h"


template <class T>
Block<T>::Block(T id, std::string sequence){
        this->id = id;
        this->sequence = sequence;
        this->component = {id};
        this->toroot = id;
}


template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
    std::set<T> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

template <class T>
T& Block<T>::find(std::map<T, Block<T>&> &blocks){
    T rootid = this->id;
    if(this->toroot != rootid){
        rootid = blocks.find(this->toroot)->second.find(blocks);
        this->toroot = rootid;

    }

    return rootid;

}
template <class T>
void Block<T>::setRoot(T id){
    toroot = id;
}

template <class T>
void Block<T>::unionto(Block other, std::map<T, Block<T>&> blocks, int reverse, int flank){
    T selfroot = this->find(blocks);
    T otheroot = other.find(blocks);
    blocks.find(selfroot)->second.setRoot(otheroot);
}


