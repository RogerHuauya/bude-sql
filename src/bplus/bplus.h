#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "apple.h"
#include "bplusnode.h"

using namespace std;

class Bplus {
public:
    Bplus(const string& table_name, const string& csv_filename);
    ~Bplus();

    void insert(const AppRecord& record);
    void remove(int key);
    void search(int key, AppRecord& record);
    void display();

    void load_csv();

private:
    string csv_filename;
    string table_name;

    fstream index_file;
    fstream data_file;

    string index_filename;
    string data_filename;

    int root_offset;
    int next_free_index_offset;
    int next_free_data_offset;

    void insert_internal(int parent_offset, const AppRecord& record, int child_offset);
    void split_child(int parent_offset, int child_index, int child_offset);
    int find_leaf_node(int key, BplusNode& node);
    void display_node(int offset, int level);

    void write_index_node(BplusNode& node, int offset);
    void read_index_node(BplusNode& node, int offset);
    int write_data_record(const AppRecord& record);
    void read_data_record(AppRecord& record, int offset);

    void remove_internal(int parent_offset, int key);
    void merge_nodes(BplusNode& parent, int parent_offset, BplusNode& left_child, int left_offset, BplusNode& right_child, int right_offset);
    void borrow_from_left(BplusNode& parent, int parent_offset, BplusNode& left_child, int left_offset, BplusNode& right_child, int right_offset, int idx);
    void borrow_from_right(BplusNode& parent, int parent_offset, BplusNode& left_child, int left_offset, BplusNode& right_child, int right_offset, int idx);
};
