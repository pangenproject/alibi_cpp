#include <iostream>
#include "Block.h"


template <class T>
Block<T>::Block(T id, std::string sequence){
        this->id = id;
        this->sequence = sequence;
        this->component = {id};
        this->toroot = id;
        this->shift = 0;
        this->reorder_shift = 0;
        this->orient = 1;
}


template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
    std::set<T> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

template <class T>
T Block<T>::find(std::map<T, Block<T>&> &blocks){
    T rootid = this->id;
    if(this->toroot != rootid){
        rootid = blocks.find(this->toroot)->second.find(blocks);
        this->orient *= blocks.find(toroot)->second.orient;

        this->shift = this->shift* blocks.find(toroot)->second.orient+ blocks.find(toroot)->second.shift;
        this->reorder_shift *= blocks.find(toroot)->second.orient;

        this->toroot = rootid;

    }

    return rootid;

}
template <class T>
void Block<T>::setRoot(T id){
    toroot = id;
}

template <class T>
void Block<T>::setShift(int s){
    shift = s;
}

template <class T>
void Block<T>::unionto(Block other, std::map<T, Block<T>&> blocks, int reverse, int flank){
    T selfid = this->find(blocks);
    T otherid = other.find(blocks);
    Block & selfroot = blocks.find(selfid)->second;
    Block & otheroot = blocks.find(otherid)->second;

    selfroot.orient = reverse;
    selfroot.reorder_shift *= reverse; //

    selfroot.setShift(flank*(otheroot.flanks[flank]+selfroot.flanks[-reverse*flank]+1)); //

    otheroot.flanks[flank] += selfroot.flanks[-1]+selfroot.flanks[1]+1;
    selfroot.setRoot(otherid);

    otheroot.component = getUnion(otheroot.component, selfroot.component);

}

template <class T>
int Block<T>::orientation(std::map<T, Block<T>&> blocks) {
    T selfroot = this->find(blocks);

    return this->orient;
}


template <class T>
int Block<T>::order(std::map<T, Block<T>&> blocks) {
    T selfroot = this->find(blocks);

    return this->shift + this->reorder_shift;
}



template <class T>
void Block<T>::reorder(std::map<T, Block<T>&> blocks, int n) {
    this->reorder_shift += n - this->order(blocks);

}


template <class T>
int Block<T>::size(std::map<T, Block<T>&> blocks) {
    T selfroot = this->find(blocks);
    Block & otherBlock = blocks.find(selfroot)->second;
    return otherBlock.flanks[1] + otherBlock.flanks[-1] + 1;

}

template <class T>
int Block<T>::minimum(std::map<T, Block<T>&> blocks) {
    T selfroot = this->find(blocks);

    Block & otherBlock = blocks.find(selfroot)->second;
    return -1 * otherBlock.flanks[-1];

}


template <class T>
int Block<T>::maximum(std::map<T, Block<T>&> blocks) {
    T selfroot = this->find(blocks);

    Block & otherBlock = blocks.find(selfroot)->second;
    return otherBlock.flanks[1];

}


template <class T>
void Block<T>::uniontoMidst(Block other, std::map<T, Block<T>&> blocks, int reverse, int flank){
    T selfid = this->find(blocks);
    T otherid = other.find(blocks);
    Block & selfroot = blocks.find(selfid)->second;
    Block & otheroot = blocks.find(otherid)->second;

    int n = otheroot.order(blocks);
    int k = selfroot.size(blocks);

    if(flank == 1) {
        for(T id: otheroot.component) {

            if(blocks.find(id)->second.order(blocks) > n){
                blocks.find(id)->second.reorder_shift += k;
            }
        }
    } else {
        for(T id: otheroot.component) {
            if(blocks.find(id)->second.order(blocks) < n){
                blocks.find(id)->second.reorder_shift -= k;
            }
        }
    }

    selfroot.orient = reverse;
    selfroot.reorder_shift *= reverse;
    selfroot.shift = n + flank*(selfroot.flanks[-reverse*flank] + 1);

    if(flank == 1){
        otheroot.flanks[1] += k;
    } else {
        otheroot.flanks[-1] += k;
    }
    selfroot.setRoot(otherid);
    otheroot.component = getUnion(otheroot.component, selfroot.component);

}