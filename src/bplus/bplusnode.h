#pragma once
#include <string>
#include <sstream>

using namespace std;

constexpr int MAX_KEYS = 4;
constexpr int NULL_OFFSET = -1;

struct BplusNode {
    bool is_leaf;
    int num_keys;
    vector<int> keys;
    vector<int> children;
    int next;

    BplusNode(bool leaf = false) : num_keys(0), is_leaf(leaf), next(NULL_OFFSET) {
        keys.resize(MAX_KEYS);
        children.resize(MAX_KEYS + 1, NULL_OFFSET);
    }

    string serialize() {
        stringstream ss;
        ss.write(reinterpret_cast<char*>(&is_leaf), sizeof(is_leaf));
        ss.write(reinterpret_cast<char*>(&num_keys), sizeof(num_keys));
        for (const auto& key : keys) {
            ss.write(reinterpret_cast<const char*>(&key), sizeof(key));
        }
        for (const auto& child : children) {
            ss.write(reinterpret_cast<const char*>(&child), sizeof(child));
        }
        ss.write(reinterpret_cast<char*>(&next), sizeof(next));
        return ss.str();
    }

    void deserialize(const string& data) {
        stringstream ss(data);
        ss.read(reinterpret_cast<char*>(&is_leaf), sizeof(is_leaf));
        ss.read(reinterpret_cast<char*>(&num_keys), sizeof(num_keys));
        for (auto& key : keys) {
            ss.read(reinterpret_cast<char*>(&key), sizeof(key));
        }
        for (auto& child : children) {
            ss.read(reinterpret_cast<char*>(&child), sizeof(child));
        }
        ss.read(reinterpret_cast<char*>(&next), sizeof(next));
    }
};
