#include "bplus.h"

Bplus::Bplus(const string& table_name, const string& csv_filename) {
    this->table_name = table_name;
    this->csv_filename = csv_filename;
    this->index_file.open(table_name + ".index", ios::in | ios::out | ios::binary);
    this->data_file.open(table_name + ".data", ios::in | ios::out | ios::binary);

    root_offset = NULL_OFFSET;
    next_free_index_offset = 0;
    next_free_data_offset = 0;

    if (!index_file){
        index_file.open(table_name + ".index", ios::out | ios::binary);
        index_file.close();
        index_file.open(table_name + ".index", ios::in | ios::out | ios::binary);
        BplusNode root(true);

    }
    else{
        index_file.seekg(0, ios::end);
        next_free_index_offset = index_file.tellg();
    }

    if (!data_file){
        data_file.open(table_name + ".data", ios::out | ios::binary);
        data_file.close();
        data_file.open(table_name + ".data", ios::in | ios::out | ios::binary);
    }
    else{
        data_file.seekg(0, ios::end);
        next_free_data_offset = data_file.tellg();
    }
}

Bplus::~Bplus() {
    index_file.close();
    data_file.close();
}

void Bplus::insert(const AppRecord& record) {
    int data_offset = write_data_record(record);
    BplusNode root;
    read_index_node(root, root_offset);
    if (root.num_keys == MAX_KEYS - 1) {
        int new_root_offset = next_free_index_offset;
        new_root_offset += sizeof(BplusNode);

        BplusNode new_root(false);
        new_root.children[0] = root_offset;

        split_child(new_root_offset, 0, root_offset);
        root_offset = new_root_offset;
    }
    insert_internal(root_offset, record, data_offset);
}

void Bplus::insert_internal(int parent_offset, const AppRecord &record,
                            int child_offset) {
    BplusNode parent;
    read_index_node(parent, parent_offset);
    if (parent.is_leaf) {
        auto it = lower_bound(parent.keys.begin(), parent.keys.begin() + parent.num_keys, record.id);
        int i = it - parent.keys.begin();
        parent.keys.insert(it, record.id);
        parent.children.insert(parent.children.begin() + i, child_offset);
        parent.num_keys++;
        write_index_node(parent, parent_offset);
    } else {
        // Find the child node to insert the key
        int i = parent.num_keys;
        while (i > 0 && record.id < parent.keys[i-1]) {
            i--;
        }
        BplusNode child;
        read_index_node(child, parent.children[i]);
        if (child.num_keys == MAX_KEYS - 1) {
            split_child(parent_offset, i, parent.children[i]);
            read_index_node(parent, parent_offset);
            if (record.id > parent.keys[i]) {
                i++;
            }
        }
        insert_internal(parent.children[i], record, child_offset);
    }
}

void Bplus::split_child(int parent_offset, int child_index, int child_offset) {
    BplusNode parent;
    read_index_node(parent, parent_offset);
    BplusNode child;
    read_index_node(child, child_offset);

    BplusNode new_child(child.is_leaf);
    new_child.num_keys = MAX_KEYS / 2 - 1;

    for (int j = 0; j < MAX_KEYS / 2 - 1; j++) {
        new_child.keys[j] = child.keys[j + MAX_KEYS / 2];
    }

    if (!child.is_leaf) {
        for (int j = 0; j < MAX_KEYS / 2; j++) {
            new_child.children[j] = child.children[j + MAX_KEYS / 2];
        }
    }

    child.num_keys = MAX_KEYS / 2 - 1;
    parent.children.insert(parent.children.begin() + child_index + 1, next_free_index_offset);
    parent.keys.insert(parent.keys.begin() + child_index, child.keys[MAX_KEYS / 2 - 1]);
    parent.num_keys++;

    write_index_node(child, child_offset);
    write_index_node(new_child, next_free_index_offset);
    next_free_index_offset += sizeof(BplusNode);
    write_index_node(parent, parent_offset);
}

int Bplus::find_leaf_node(int key, BplusNode &node) {
    int offset = root_offset;
    while (true) {
        read_index_node(node, offset);
        if (node.is_leaf) {
            return offset;
        }
        int i = 0;
        while (i < node.num_keys && key >= node.keys[i]) {
            i++;
        }
        offset = node.children[i];
    }
    return offset;
}

void Bplus::search(int key, AppRecord &record) {
    BplusNode node;
    int offset = find_leaf_node(key, node);
    auto it = lower_bound(node.keys.begin(), node.keys.begin() + node.num_keys, key);
    if (it != node.keys.begin() + node.num_keys && *it == key) {
        int index = it - node.keys.begin();
        read_data_record(record, node.children[index]);
    }
}

void Bplus::write_index_node(BplusNode& node, int offset) {
    index_file.seekp(offset);
    string node_data = node.serialize();
    index_file.write(node_data.c_str(), node_data.size());
}

void Bplus::read_index_node(BplusNode& node, int offset) {
    index_file.seekg(offset);
    vector<char> buffer(sizeof(BplusNode));
    index_file.read(buffer.data(), buffer.size());
    node.deserialize(string(buffer.begin(), buffer.end()));
}

int Bplus::write_data_record(const AppRecord &record) {
    data_file.seekp(next_free_data_offset);
    data_file.write(reinterpret_cast<const char*>(&record), sizeof(AppRecord));
    int offset = next_free_data_offset;
    next_free_data_offset += sizeof(AppRecord);
    return offset;
}

void Bplus::read_data_record(AppRecord &record, int offset) {
    data_file.seekg(offset);
    data_file.read(reinterpret_cast<char*>(&record), sizeof(AppRecord));
}