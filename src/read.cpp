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

std::vector<std::string> split(std::string line, char sep){
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
void weight_gfa(std::vector<std::string> line,  std::map<std::pair<std::pair<T, char>, std::pair<T, char>>, size_t> s) {
    for (int i = 0; i < line.size() - 1; i++) {
        std::pair<int, int> v1 = {std::stoi(line[i].substr(0, line[i].size() - 1)) - 1, strand(line[i].back())};
        std::pair<int, int> v2 = {std::stoi(line[i+1].substr(0, line[i+1].size() - 1)) - 1, strand(line[i+1].back())};
        std::cout << v1.first << v1.second;
        std::cout << v2.first << v2.second;

        std::pair<std::pair<T, int>, std::pair<T, int>> r = connect_gfa_nodes(v1, v2);
        std::cout << r.first.first << r.first.second << "\n";
        std::cout << r.first.first << r.first.second << "\n";

        if(s.find(r) == s.end()){
            s[r] = 0;
        } else{
            s[r] += 1;
        }

    }
}

template <class T, class T2>
void read_gfa(std::string gfa_file) {
    std::map<T, Block<T>&> blocks;
    std::ifstream f(gfa_file);
    std::map<std::pair<std::pair<int, char>, std::pair<int, char>>, size_t> s;


    if (!f.is_open()) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    try {

        std::string line;
        int i = 0;

        while (std::getline(f, line)) {
            if (line.substr(0, 1) == "S") {
                std::vector<std::string> r =  split(line, '\0');
                Block<T> block(i, r[2]);
                blocks.insert({i, block});
                i++;
            } else if (line.substr(0, 1) == "P") {
                std::vector<std::string> r =  split(line, '\0');
                std::vector<std::string> line_split = split(r[2], ',');
                weight_gfa(line_split, s);
            }
        }
        f.close();
    } catch (std::exception const& e) {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
    }
    //std::sort(edges.begin(), edges.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        //return a.second > b.second;
    //});
}

