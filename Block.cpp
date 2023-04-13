#include <iostream>
#include <algorithm>
#include "Block.h"

using namespace std;

template <class T>
Block<T>::Block(T id, string sequence){
        this->id = id;
        this->sequence = sequence;
        this->component = {id};
        this->toroot = (this);
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
    Block root = *this;
    if(this->toroot != (this)){
        root = this->toroot->find();
        this->toroot = &root;

    }

    return root;

}

template <class T>
void Block<T>::unionto(Block other, int reverse, int flank){
    Block selfroot = this->find();
    Block otheroot = other.find();
    cout << " " <<  selfroot.toroot->id << "id" << otheroot.id << ";";
    selfroot.toroot = &otheroot;
    cout << " " <<  selfroot.toroot->id << "id" << otheroot.id << ";";


    //otheroot.component = getUnion(otheroot.component, selfroot.component);
    //delete selfroot.flanks;
    //delete selfroot.component;
}


