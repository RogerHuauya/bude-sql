#ifndef UTILS_HPP
#define UTILS_HPP

#include <bitset>
#include <string>

using namespace std;

inline string toBinaryString(int x, int d) {
    string binaryString = bitset<32>(x).to_string();
    return binaryString.substr(32 - d);
}

inline string bin_h(int key, int d) {
    int x = key % (1 << d);
    return toBinaryString(x, d);
}

#endif // UTILS_HPP
