#include <utility>
#include <unordered_map>
#include <inttypes.h>
#include <functional>
#include <iostream>
#include <map>
#include <cmath>
#include <chrono>
#include <ctime>
#include <iterator>
#include <boost/functional/hash.hpp>

struct pair_hash {
    size_t operator() (const std::pair<int32_t, int32_t>& p) const {
        size_t h = 0;
        boost::hash_combine(h, boost::hash_value(p.first));
        boost::hash_combine(h, boost::hash_value(p.second));
        return h;
    }
};

struct pair_equals {
    size_t operator() (const std::pair<int32_t, int32_t>& p, const std::pair<int32_t, int32_t>& q) const {
        return p.first == q.first && p.second == q.second;
    }
};

int main(int argc, char* argv[]) {
    std::vector<double> create_time;
    std::vector<double> access_time;

    for(size_t N = 1; N < 1000; ++N) {
        std::unordered_map<std::pair<int32_t, int32_t>, std::string, pair_hash, pair_equals> um;    

        auto start = std::chrono::system_clock::now();
        for(int i = 0; i < sqrt(N); ++i) 
            for(int j = 0; j < sqrt(N); ++j)
                um[std::make_pair(i, j)] = "hello world";
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end-start;
        create_time.push_back(elapsed.count());

        start = std::chrono::system_clock::now();
        auto it = um.begin();
        std::advance(it, N / 2);
        //std::cerr << it->first.second << std::endl;
        end = std::chrono::system_clock::now();
        elapsed = end-start;
        access_time.push_back(elapsed.count());
        std::cout << create_time[N-1] << "," << access_time[N-1] << std::endl;
    }

    
}