#include <iostream>
#include <algorithm>
#include "Block.h"

using namespace std;

template <class T>
Block<T>::Block(T id, string sequence){
        id = id;
        sequence = sequence;
        component = {id};
        toroot = (this);
}


template <typename T>
std::set<T> getUnion(const std::set<T>& a, const std::set<T>& b)
{
    std::set<T> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

template <class T>
Block<T> Block<T>::find(){

    if(toroot != (this)){
        Block root = this->toroot->find();
        this->orient *= this->toroot->orient;
        this->shift  = this->shift * this->toroot->orient + this->toroot->shift;
        this->reorder_shift *= this->toroot->orient;
        this->toroot = &root;

        return root;
    }

    return *this;

}

template <class T>
void Block<T>::unionto(Block other, int reverse, int flank){
    Block selfroot = this->find();
    Block otheroot = other.find();
    selfroot.orient = reverse;
    selfroot.reorder_shift *= reverse;
    selfroot.shift = flank*(otheroot.flanks[flank]+selfroot.flanks[-reverse*flank]+1);
    otheroot.flanks[flank] += selfroot.flanks[-1]+selfroot.flanks[1]+1;
    selfroot.toroot = &otheroot;

    otheroot.component = getUnion(otheroot.component, selfroot.component);
    //delete selfroot.flanks;
    //delete selfroot.component;
}


