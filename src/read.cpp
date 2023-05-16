#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>     // std::cerr
#include <unordered_map>
#include <algorithm>
#include "Block.h"
#include <utility>
#include <map>
#include <functional>

int strand(char x) {
    if (x == '+') return 1;
    else return -1;
}

template <class T>
std::pair<std::pair<T, int>, std::pair<T, int>> connect_gfa_nodes(std::pair<T, int> v1, std::pair<T, int> v2) {
    std::pair<std::pair<T, int>, std::pair<T, int>> e;
    e.first.first = v1.first;
    e.first.second = v1.second;
    e.second.first = v2.first;
    e.second.second = -v2.second;

    if (e.first.first > e.second.first) {
        std::swap(e.first, e.second);
    } else if (e.first.first == e.second.first) {
       e.first.second = std::max(e.first.second, e.second.second);
       e.second.first = e.first.first;
       e.second.second =  std::min(e.first.second, e.second.second);
    }
    return e;
}

std::vector<std::string> split_s(std::string line, char sep){
    std::vector<std::string> result;

    std::stringstream ss(line);

    while( ss.good() )
    {
        std::string substr;
        getline( ss, substr, sep );
        result.push_back( substr );
    }
    return result;
}


template <class T>
void weight_gfa(std::vector<std::string> line, std::map<std::pair<std::pair<T, int>, std::pair<T, int>>, int> &result) {
    for (int i = 0; i < line.size() - 1; i++) {
        std::pair<int, int> v1 = {std::stoi(line[i].substr(0, line[i].size() - 1)), strand(line[i].back())};
        std::pair<int, int> v2 = {std::stoi(line[i+1].substr(0, line[i+1].size() - 1)), strand(line[i+1].back())};
        std::cout << "v1"<< v1.first << "v1" << v1.second << "v2"<< v2.first << "v2" << v2.second << "\n";

        std::pair<std::pair<T, int>, std::pair<T, int>> r = connect_gfa_nodes(v1, v2);


        if(result.find(r) == result.end()){
            result.insert({r, 1});
        } else{
            result[r] += 1;
        }

    }
}

// Komparator do sortowania po wartościach
template<typename K, typename V>
struct ValueComparator
{
    bool operator()(const std::pair<K, V>& a, const std::pair<K, V>& b)
    {
        return a.second > b.second;
    }
};

std::pair<std::map<int, Block<int>>,  std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> read_gfa(std::string gfa_file) {
    std::map<int, Block<int>> blocks;
    std::ifstream f(gfa_file);
    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, int> s;


    if (!f.is_open()) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    try {

        std::string line;

        while (std::getline(f, line)) {
            if (line.substr(0, 1) == "S") {

                std::vector<std::string> r =  split_s(line, '\t');
                Block<int> block(std::stoi(r[1]), r[2]);
                blocks.insert({std::stoi(r[1]), block});


            } else if (line.substr(0, 1) == "P") {
                std::vector<std::string> r =  split_s(line, '\t');
                std::vector<std::string> line_split = split_s(r[2], ',');
                weight_gfa(line_split, s);
            }
        }
        f.close();
    } catch (std::exception const& e) {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
    }
    std::vector<std::pair<std::pair<std::pair<int, int>, std::pair<int, int>>, int>> vector(s.begin(), s.end());
    std::sort(vector.begin(), vector.end(), ValueComparator<std::pair<std::pair<int, int>, std::pair<int, int>>, int>());



    std::map<std::pair<std::pair<int, int>, std::pair<int, int>>, int> sortedMap;

    for (const auto& pair : vector)
    {
        sortedMap.insert({pair.first, pair.second});
    }

    return {blocks, sortedMap};
}

