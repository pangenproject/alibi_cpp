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
#include <fstream>


int strand(char x) {
    if (x == '+') return 1;
    else return -1;
}

// A hash function used to hash a pair of any kind
struct hash_pair {
    size_t operator()(const std::tuple<int, int, int, int>& p) const
    {
        auto hash1 = std::hash<int>{}(std::get<0>(p));
        auto hash2 = std::hash<int>{}(std::get<1>(p));

        if (hash1 != hash2) {
            return hash1 ^ hash2;
        }

        // If hash1 == hash2, their XOR is zero.
        return hash1;
    }
};


template <class T>
std::tuple<int, int, int, int> connect_gfa_nodes(std::pair<T, int> v1, std::pair<T, int> v2) {
    std::tuple<int, int, int, int> e = std::make_tuple(v1.first, v1.second, v2.first, -v2.second);

    if (std::get<0>(e) > std::get<2>(e)) {
        std::swap(std::get<0>(e), std::get<2>(e));
        std::swap(std::get<1>(e), std::get<3>(e));
    } else if (std::get<0>(e) == std::get<2>(e)) {
        std::get<1>(e) = std::max(std::get<1>(e), std::get<3>(e));
        std::get<2>(e) = std::get<0>(e);
        std::get<3>(e) = std::min(std::get<1>(e), std::get<3>(e));
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


void weight_gfa(std::vector<std::string> line, std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair> &result) {
    for (int i = 0; i < line.size() - 1; i++) {
        std::pair<int, int> v1 = {std::stoi(line[i].substr(0, line[i].size() - 1)), strand(line[i].back())};
        std::pair<int, int> v2 = {std::stoi(line[i+1].substr(0, line[i+1].size() - 1)), strand(line[i+1].back())};

        std::tuple<int, int, int, int> r = connect_gfa_nodes(v1, v2);


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


std::pair<std::unordered_map<int, Block<int>>,  std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair>> read_gfa(std::string gfa_file) {
    std::unordered_map<int, Block<int>> blocks;
    std::ifstream f(gfa_file);
    std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair> s;
    std::map<std::tuple<int, int, int, int>, int> debug;

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
    std::vector<std::pair<std::tuple<int, int, int, int>, int>> vector(s.begin(), s.end());
    //std::sort(vector.begin(), vector.end(), ValueComparator<std::pair<std::tuple<int, int, int, int>, int>());


    std::unordered_map<std::tuple<int, int, int, int>, int, hash_pair> sortedMap;
    std::ofstream plik("../tests/data/moj_plik.txt");

    for (const auto& pair : vector)
    {
        sortedMap.insert({pair.first, pair.second});
        if (plik.is_open()) {
            std::tuple klucz = pair.first;
            int b = debug.find(klucz)->second;
            //plik  << std::get<0>(pair) pair.first.first.first << "\t" << pair.first.first.second <<  "\t" << pair.first.second.first <<  "\t" << pair.first.second.second <<  "\t" << b << std::endl;


        } else {
            std::cerr << "Nie udało się otworzyć pliku do zapisu." << std::endl;
        }
    }
    plik.close();


    return {blocks, sortedMap};
}

