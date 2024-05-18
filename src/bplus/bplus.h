#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "apple.h"

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

    string serialize(){
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

    string deserialize(const string& data){
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
        return ss.str();
    }
};



class Bplus {
public:
    Bplus(const string& table_name, const string& csv_filename);
    ~Bplus();

    void insert(const AppRecord& record);
    void search(int key, AppRecord& record);
    void display();

    void load_csv();
private:
    string csv_filename;
    string table_name;

    fstream index_file;
    fstream data_file;

    int root_offset;
    int next_free_index_offset;
    int next_free_data_offset;

    void insert_internal(int  parent_offset, const AppRecord& record, int child_offset);
    void split_child(int parent_offset, int child_index, int child_offset);
    int find_leaf_node(int key, BplusNode& node);
    void display_node(int offset, int level);

    void write_index_node(BplusNode& node, int offset);
    void read_index_node(BplusNode& node, int offset);
    int write_data_record(const AppRecord& record);
    void read_data_record(AppRecord& record, int offset);
};


