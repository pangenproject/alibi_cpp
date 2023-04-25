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



template <class T, class T2>
void read_gfa(std::string gfa_file) {
    std::map<T, Block<T>&> blocks;
    std::ifstream f(gfa_file);
    std::unordered_map<int, size_t> s;


    if (!f.is_open()) {
            std::cerr << "Nie można otworzyć pliku!" << std::endl;
    }
    try {

        std::string line;
        int i = 0;

        while (std::getline(f, line)) {
            if (line.substr(0, 1) == "S") {
                std::vector<std::string> r =  split(line, '\t');
                Block<T> block(i, r[2]);
                blocks.insert({i, block});
                i++;
            } else if (line.substr(0, 1) == "P") {
                std::vector<std::string> r =  split(line, '\t');
                std::vector<std::string> line_split = split(r[2], ',');
            }
        }
        f.close();
    } catch (std::exception const& e) {
        std::cerr << "Wystąpił błąd: " << e.what() << std::endl;
    }
}

