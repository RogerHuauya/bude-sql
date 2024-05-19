#include "bplus.h"

Bplus::Bplus(const string &table_name, const string &csv_filename) {
    this->table_name = table_name;
    this->csv_filename = csv_filename;
    index_filename = table_name + ".index";
    data_filename = table_name + ".data";

    this->index_file.open(index_filename, ios::in | ios::out | ios::binary);
    this->data_file.open(data_filename, ios::in | ios::out | ios::binary);

    root_offset = 0;
    next_free_index_offset = 0;
    next_free_data_offset = 0;

    if (!index_file) {
        index_file.open(index_filename, ios::out | ios::binary);
        index_file.close();
        index_file.open(index_filename, ios::in | ios::out | ios::binary);
        BplusNode root(true);
        write_index_node(root, next_free_index_offset);
        root_offset = next_free_index_offset;
        next_free_index_offset += sizeof(BplusNode);
    } else {
        index_file.seekg(0, ios::end);
        next_free_index_offset = index_file.tellg();
    }

    if (!data_file) {
        data_file.open(table_name + ".data", ios::out | ios::binary);
        data_file.close();
        data_file.open(table_name + ".data", ios::in | ios::out | ios::binary);
    } else {
        data_file.seekg(0, ios::end);
        next_free_data_offset = data_file.tellg();
    }
}

Bplus::~Bplus() {
    index_file.close();
    data_file.close();

    std::remove(index_filename.c_str());
    std::remove(data_filename.c_str());
}

void Bplus::insert(const AppRecord &record) {
    int data_offset = write_data_record(record);
    BplusNode root;
    read_index_node(root, root_offset);
    if (root.num_keys == MAX_KEYS - 1) {
        int new_root_offset = next_free_index_offset;
        next_free_index_offset += sizeof(BplusNode);
        BplusNode new_root(false);
        new_root.children[0] = root_offset;
        write_index_node(new_root, new_root_offset);
        split_child(new_root_offset, 0, root_offset);
        root_offset = new_root_offset;
    }
    insert_internal(root_offset, record, data_offset);
}

void Bplus::insert_internal(int parent_offset, const AppRecord& record, int child_offset) {
    BplusNode parent;
    read_index_node(parent, parent_offset);
    if (parent.is_leaf) {
        auto it = lower_bound(parent.keys.begin(),
                              parent.keys.begin() + parent.num_keys,
                              record.id);
        int i = it - parent.keys.begin();
        parent.keys.insert(it, record.id);
        parent.children.insert(parent.children.begin() + i, child_offset);
        parent.num_keys++;
        write_index_node(parent, parent_offset);
    } else {
        int i = parent.num_keys;
        while (i > 0 && record.id < parent.keys[i - 1]) {
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
    parent.children.insert(parent.children.begin() + child_index + 1,
                           next_free_index_offset);
    parent.keys.insert(parent.keys.begin() + child_index,
                       child.keys[MAX_KEYS / 2 - 1]);
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
    auto it = lower_bound(node.keys.begin(), node.keys.begin() + node.num_keys,
                          key);
    if (it != node.keys.begin() + node.num_keys && *it == key) {
        int index = it - node.keys.begin();
        read_data_record(record, node.children[index]);
    } else {
        throw std::runtime_error("Record not found");
    }
}

void Bplus::display() {
    display_node(root_offset, 0);
}
/*
void Bplus::load_csv() {
    ifstream file(csv_filename);
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        AppRecord record;
        try {
            getline(ss, field, ',');
            record.id = stoi(field);

            getline(ss, field, ',');
            strncpy(record.app_name, field.c_str(), sizeof(record.track_name) - 1);

            getline(ss, field, ',');
            record.size_bytes = std::stoul(field);

            getline(ss, field, ',');
            strncpy(record.currency, field.c_str(), sizeof(record.currency) - 1);

            getline(ss, field, ',');
            record.price = std::stof(field);

            getline(ss, field, ',');
            record.rating_count_tot = std::stoul(field);

            getline(ss, field, ',');
            record.rating_count_ver = std::stoul(field);

            getline(ss, field, ',');
            record.user_rating = static_cast<UserRating>(std::stof(field) * 2);

            getline(ss, field, ',');
            record.user_rating_ver = std::stof(field);

            getline(ss, field, ',');
            strncpy(record.ver, field.c_str(), sizeof(record.ver) - 1);

            getline(ss, field, ',');
            strncpy(record.cont_rating, field.c_str(), sizeof(record.cont_rating) - 1);

            getline(ss, field, ',');
            strncpy(record.prime_genre, field.c_str(), sizeof(record.prime_genre) - 1);

            getline(ss, field, ',');
            record.sup_devices_num = stoul(field);

            getline(ss, field, ',');
            record.ipadSc_urls_num = stoul(field);

            getline(ss, field, ',');
            record.lang_num = stoul(field);

            getline(ss, field, ',');
            record.vpp_lic = stoi(field) != 0;

            insert(record);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Invalid argument: " << e.what() << " at line: " << line << std::endl;
        } catch (const std::out_of_range &e) {
            std::cerr << "Out of range: " << e.what() << " at line: " << line << std::endl;
        }
    }
}
*/

void Bplus::load_csv() {
    ifstream file(csv_filename, ios::binary);
    AppRecord r;
    int i=0;
    while(file.read((char*)&r, sizeof(AppRecord))){
        cout << i;
        try{
            insert(r);
        } catch (const std::exception& e){
            std::cerr << "Error: " << std::endl;
        }
    }
}

void Bplus::display_node(int offset, int level) {
    BplusNode node;
    if (offset == NULL_OFFSET) {
        return;
    }
    read_index_node(node, offset);
    cout << "Level " << level << ": ";
    for (int i = 0; i < node.num_keys; i++) {
        cout << node.keys[i] << " ";
    }
    cout << endl;
    if (!node.is_leaf) {
        for (int i = 0; i <= node.num_keys; i++) {
            display_node(node.children[i], level + 1);
        }
    }
}

void Bplus::write_index_node(BplusNode &node, int offset) {
    index_file.close();
    index_file.open(index_filename, ios::in | ios::out | ios::binary);
    index_file.seekp(offset, ios::beg);
    string node_data = node.serialize();
    index_file.write(node_data.c_str(), node_data.size());

}

void Bplus::read_index_node(BplusNode &node, int offset) {
    index_file.close();
    index_file.open(index_filename, ios::in | ios::out | ios::binary);
    index_file.seekg(offset, ios::beg);
    char buffer[sizeof(BplusNode)];
    index_file.read(buffer, sizeof(BplusNode));
    string node_data(buffer, sizeof(BplusNode));
    node.deserialize(node_data);

}

int Bplus::write_data_record(const AppRecord &record) {
    data_file.seekp(next_free_data_offset);
    data_file.write(reinterpret_cast<const char *>(&record),
                    sizeof(AppRecord));
    int offset = next_free_data_offset;
    next_free_data_offset += sizeof(AppRecord);
    return offset;
}

void Bplus::read_data_record(AppRecord &record, int offset) {
    data_file.seekg(offset);
    data_file.read(reinterpret_cast<char *>(&record), sizeof(AppRecord));
}

void Bplus::remove(int key) {
    remove_internal(root_offset, key);
}

void Bplus::remove_internal(int parent_offset, int key) {
    BplusNode node;
    read_index_node(node, parent_offset);
    int idx = 0;

    while (idx < node.num_keys && key > node.keys[idx]) {
        idx++;
    }

    if (node.is_leaf) {
        if (idx < node.num_keys && key == node.keys[idx]) {
            node.keys.erase(node.keys.begin() + idx);
            node.children.erase(node.children.begin() + idx);
            node.num_keys--;
            write_index_node(node, parent_offset);
        }
    } else {
        BplusNode child;
        read_index_node(child, node.children[idx]);
        if (child.num_keys == MAX_KEYS / 2 - 1) {
            BplusNode left_sibling, right_sibling;
            if (idx > 0) {
                read_index_node(left_sibling, node.children[idx - 1]);
            }
            if (idx < node.num_keys) {
                read_index_node(right_sibling, node.children[idx + 1]);
            }

            if (idx > 0 && left_sibling.num_keys > MAX_KEYS / 2 - 1) {
                borrow_from_left(node, parent_offset, left_sibling,
                                 node.children[idx - 1], child,
                                 node.children[idx], idx - 1);
            } else if (idx < node.num_keys &&
                       right_sibling.num_keys > MAX_KEYS / 2 - 1) {
                borrow_from_right(node, parent_offset, child,
                                  node.children[idx], right_sibling,
                                  node.children[idx + 1], idx);
            } else if (idx > 0) {
                merge_nodes(node, parent_offset, left_sibling,
                            node.children[idx - 1], child, node.children[idx]);
                idx--;
            } else {
                merge_nodes(node, parent_offset, child, node.children[idx],
                            right_sibling, node.children[idx + 1]);
            }
        }

        remove_internal(node.children[idx], key);
    }
}

void
Bplus::merge_nodes(BplusNode &parent, int parent_offset, BplusNode &left_child,
                   int left_offset, BplusNode &right_child, int right_offset) {
    left_child.keys.push_back(parent.keys[parent_offset]);
    left_child.keys.insert(left_child.keys.end(), right_child.keys.begin(),
                           right_child.keys.end());
    left_child.children.insert(left_child.children.end(),
                               right_child.children.begin(),
                               right_child.children.end());
    left_child.num_keys += right_child.num_keys + 1;

    if (left_child.is_leaf) {
        left_child.next = right_child.next;
    }

    parent.keys.erase(parent.keys.begin() + parent_offset);
    parent.children.erase(parent.children.begin() + parent_offset + 1);
    parent.num_keys--;

    write_index_node(left_child, left_offset);
    write_index_node(parent, parent_offset);
}

void Bplus::borrow_from_left(BplusNode &parent, int parent_offset,
                             BplusNode &left_child, int left_offset,
                             BplusNode &right_child, int right_offset,
                             int idx) {
    right_child.keys.insert(right_child.keys.begin(), parent.keys[idx]);
    right_child.children.insert(right_child.children.begin(),
                                left_child.children.back());
    right_child.num_keys++;

    parent.keys[idx] = left_child.keys.back();
    left_child.keys.pop_back();
    left_child.children.pop_back();
    left_child.num_keys--;

    write_index_node(left_child, left_offset);
    write_index_node(right_child, right_offset);
    write_index_node(parent, parent_offset);
}

void Bplus::borrow_from_right(BplusNode &parent, int parent_offset,
                              BplusNode &left_child, int left_offset,
                              BplusNode &right_child, int right_offset,
                              int idx) {
    left_child.keys.push_back(parent.keys[idx]);
    left_child.children.push_back(right_child.children.front());
    left_child.num_keys++;

    parent.keys[idx] = right_child.keys.front();
    right_child.keys.erase(right_child.keys.begin());
    right_child.children.erase(right_child.children.begin());
    right_child.num_keys--;

    write_index_node(left_child, left_offset);
    write_index_node(right_child, right_offset);
    write_index_node(parent, parent_offset);
}
