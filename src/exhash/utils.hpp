#ifndef UTILS_HPP
#define UTILS_HPP

#include <bitset>
#include <string>

inline std::string toBinaryString(int x, int d) {
    std::string binaryString = std::bitset<32>(x).to_string();
    return binaryString.substr(32 - d);
}

inline std::string bin_h(int key, int d) {
    int x = key % (1 << d);
    return toBinaryString(x, d);
}

#endif // UTILS_HPP
