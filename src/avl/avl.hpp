#ifndef AVL_FILE_HPP
#define AVL_FILE_HPP

#include "node.hpp"
#include <cstdlib>
#include <functional>
#include <iostream>

template<typename KeyType
        ,typename RecordType
        ,typename Index = std::function<KeyType(RecordType &)>
        ,typename Greater = std::greater<KeyType>
>
class AVLFile{
private:
    long root;
    std::fstream file;

    std::string heap_file_name;
    std::string file_name;
    
    Index index;
    Greater greater;

private: 
    void _insert(KeyType key, long data_pointer){
        long inserted_pos = insert(key, data_pointer, root);
        this-> root = ( root == -1 ? inserted_pos : root );
    }


    long insert(KeyType key, long data_pointer, long rec_pos){
        if (rec_pos == -1) {
            Node<KeyType> node(key, data_pointer);
            file.seekp(0, std::ios::end);
            long pos = file.tellg();
            file << node;
            return pos;
        }
        Node<KeyType> node;
        file.seekp(rec_pos);
        file >> node;
        long inserted_pos;

        if (greater(node.key, key)) {
            inserted_pos = this->insert(key, data_pointer, node.left);
            if ( node.left == -1 ){
                node.left = inserted_pos;
            }
        } else if (greater(key, node.key)) {
            inserted_pos = this->insert(key, data_pointer, node.right);
            if ( node.right == -1 ){
                node.right = inserted_pos;
            }

        } else {
            file.seekp(0, std::ios::end);
            Node<KeyType> insert_node(key, data_pointer);
            insert_node.next = node.next;
            inserted_pos = file.tellg();
            file << insert_node;

            file.seekp(rec_pos);
            node.next = inserted_pos;
            file << node;

            return EXIT_SUCCESS;
        }


        update_height(node, rec_pos);

        balance(node, rec_pos);

        return EXIT_SUCCESS;
    }

    void update_height(Node<KeyType> &node, long rec_pos)
    {
        long r = height(node.right);
        long l = height(node.left);
        node.height = std::max(l,r) + 1;

        file.seekp(rec_pos);
        file << node;
    }

    long height(long pos_node)
    {
        if (pos_node == -1){return -1;}
        file.seekp(pos_node);
        Node<KeyType> node;
        file >> node;
        return node.height;
    }

    void search(KeyType key, long position, std::vector<long>& pointers)
    {
        if (position == -1){
            return;
        }
        Node<KeyType> node;
        file.seekg(position);
        file >> node;
        
        if (greater(node.key, key)) { 
            search(key, node.left, pointers) ;
            return;
        } else if ( greater(key, node.key) ){
            search(key, node.right, pointers) ;
            return;
        }
        depth_search(position, pointers);
    }

    void depth_search(long position, std::vector<long>& pointers)
    {
        Node<KeyType> node;
        while (position != -1) {
            file.seekg(position);
            file >> node;
            pointers.push_back(node.data_pointer);
            position = node.next;
        }
    }

    long balancing_factor(Node<KeyType>& node)
    {
        long lheigth =  height(node.left);
        long rheigth = height(node.right);
        return lheigth - rheigth;
    }

    void balance(Node<KeyType>& node, long position)
    {
        long bf = balancing_factor(node);
        if (bf > 1) {
            Node<KeyType> left_node;
            file.seekp(node.left);
            file >> left_node;
            if ( balancing_factor(left_node) <= -1 ){
                rotate_left(left_node, node.left);
            }
            rotate_right(node, position);
        } else if (bf < -1) {
            Node<KeyType> right_node;
            file.seekp(node.right);
            file >> right_node;
            if ( balancing_factor(right_node) >= 1 ){
                rotate_right(right_node, node.right);
            }
            rotate_left(node, position);
        }
    }

    void rotate_right(Node<KeyType>& node, long position)
    {
        Node<KeyType> left_n;
        long left_p = node.left;

        file.seekp(left_p);
        file >> left_n;

        node.left = left_n.right;
        left_n.right = left_p;

        file.seekp(left_p);
        file << node;
        file.seekp(position);
        file << left_n;

        update_height(node, left_p);
        update_height(left_n, position);
    }

    void rotate_left(Node<KeyType>& node, long position)
    {
        Node<KeyType> right_n;
        long right_p = node.right;

        file.seekp(right_p);
        file >> right_n;

        node.right = right_n.left;
        right_n.left = right_p;

        file.seekp(right_p);
        file << node;
        file.seekp(position);
        file << right_n;

        update_height(node, right_p);
        update_height(right_n, position);
    }

    void inorder(long position, std::vector<long>& pointers){
        if (position == -1){
            return;
        }
        Node<KeyType> node;
        file.seekp(position);
        file >> node;
        
        inorder(node.left, pointers);

        depth_search(position, pointers);

        inorder(node.right, pointers);
        
    }

    int remove(KeyType key, long position, std::vector<long>& pointers)
    {
        if (position == -1){
            file.close();
            throw std::runtime_error("Key not found");
        }
        Node<KeyType> node;
        file.seekp(position);
        file >> node;
        int reallocate = NO_DETACH;
        if (greater(node.key, key)) { 
            reallocate = remove(key, node.left, pointers) ;
            if (reallocate == DETACH){
                node.left = -1;
            }

        } else if ( greater(key, node.key) ){
            reallocate = remove(key, node.right, pointers) ;

            if (reallocate == DETACH){
                node.right = -1;
            }
        } else {
            if ( node.left == -1 && node.right == -1 ){
                if (pointers.empty()) depth_search(position, pointers);
                return DETACH;
            } else if ( node.left == -1 ){
                if (pointers.empty()) depth_search(position, pointers);

                Node<KeyType> right_node;
                file.seekp(node.right);
                file >> right_node;

                node = right_node;
                node.right = right_node.right;
                node.left = right_node.left;

            } else if ( node.right == -1 ){
                if (pointers.empty()) depth_search(position, pointers);
                Node<KeyType> left_node;
                file.seekp(node.left);
                file >> left_node;

                node = left_node;
                node.right = left_node.right;
                node.left = left_node.left;

            } else {
                if (pointers.empty()) depth_search(position, pointers);

                Node<KeyType> successor = get_successor(node.right);
                reallocate = remove(successor.key, node.right, pointers);
                node = successor;
                if (reallocate == DETACH){
                    node.right = -1;
                }
            }
        }
        update_height(node, position);
        balance(node, position);
        return NO_DETACH;
    }

    Node<KeyType> get_successor(long position)
    {
        Node<KeyType> node;
        file.seekp(position);
        file >> node;
        while (node.left != -1) {
            file.seekp(node.left);
            file >> node;
        }
        return node;
    }

    void _print(long position, const std::string& prefix = "", bool isLeft = true)
    {
        if (position == -1) {
            return;
        }

        Node<KeyType> node;
        file.seekp(position);
        file >> node;

        std::cout << prefix;
        std::cout << (isLeft ? "├── " : "└── ");
        std::cout << node.key;
        Node<KeyType> next_node = node;
        while (next_node.next != -1) {
            std::cout << "*";
            file.seekp(next_node.next);
            file >> next_node;
        } std::cout << std::endl;

        _print(node.left, prefix + (isLeft ? "│   " : "    "), true);
        _print(node.right, prefix + (isLeft ? "│   " : "    "), false);
    }

    void range_search(KeyType key1, KeyType key2, long position, std::vector<long>& pointers)
    {
        if (position == -1){
            return;
        }
        Node<KeyType> node;
        file.seekp(position);
        file >> node;
        
        if (greater(node.key, key1)) { 
            range_search(key1, key2, node.left, pointers) ;
        } 
        if (greater(key2, node.key)) {
            range_search(key1, key2, node.right, pointers) ;
        }
        if (!greater(key1, node.key) && !greater(node.key, key2)){
            depth_search(position, pointers);
        }
    }

public:

    AVLFile() = default;

    explicit AVLFile(std::string heap_file_name
            , std::string attribute
            , Index i = Index()
            , Greater g = Greater()
            )
        :heap_file_name{heap_file_name}
        , index{i}
        , greater{g}
        , root{-1}
    {
        int p = heap_file_name.find_last_of(".");
        this->file_name = heap_file_name.substr(0,p) + "_" + attribute + ".avl";
        file.open(file_name, std::ios::app | std::ios::binary);
        file.close();

        if (*this) {
            this->root = 0;
        }
    }

    ~AVLFile() = default;

    explicit operator bool() const 
    {
        std::fstream f(file_name, std::ios::app);
        long end_pos = f.tellg();
        f.close();
        return ( end_pos > 0 );
    }

    void insert(RecordType &record)
    {
        long rec_pos;
        std::fstream heap_file(heap_file_name, std::ios::out | std::ios::binary | std::ios::in);
        heap_file.seekg(0, std::ios::end);
        rec_pos = heap_file.tellg();
        heap_file.write((char*)&record, sizeof(RecordType));
        heap_file << std::flush;
        heap_file.close();
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
        _insert(index(record), rec_pos);
        file.close();
    }

    void create_index()
    {
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::trunc);
        std::ifstream heap_file(heap_file_name, std::ios::binary);

        long seek{0};
        RecordType record;
        root = -1;
        while (heap_file.read((char*)&record, sizeof(RecordType))) {
            if ( !record.removed ) {
                _insert(index(record), seek);
            }
            seek = heap_file.tellg();
        }
        file.close();
        heap_file.close();
    }

    std::vector<RecordType> search(KeyType key)
    {
        std::vector<long> data_pointers;
        file.open(file_name, std::ios::binary | std::ios::in);
        search(key, root, data_pointers);
        file.close();

        std::vector<RecordType> records;
        records.reserve(data_pointers.size());
        RecordType record;

        std::ifstream heap_file(heap_file_name, std::ios::binary);
        for (long pointer : data_pointers) {
            heap_file.seekg(pointer);
            heap_file.read( (char*)&record, sizeof(RecordType) );
            if (!record.removed){
                records.push_back(record);
            }
        }

        heap_file.close();
        return records;
    }

    std::vector<RecordType> inorder()
    {
        std::vector<long> data_pointers;
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
        inorder(root, data_pointers);
        file.close();

        std::vector<RecordType> records;
        records.reserve(data_pointers.size());
        RecordType record;

        std::ifstream heap_file(heap_file_name, std::ios::binary);
        for (long pointer : data_pointers) {
            heap_file.seekg(pointer);
            heap_file.read( (char*)&record, sizeof(RecordType) );
            if (!record.removed){
                records.push_back(record);
            }
        }

        heap_file.close();
        return records;
    }

    void remove(KeyType key)
    {
        std::vector<long> data_pointers;
        file.open(file_name, std::ios::binary | std::ios::in | std::ios::out);
        int root_detached = this->remove(key, root, data_pointers);
        file.close();

        std::fstream heap_file(heap_file_name, std::ios::binary | std::ios::in | std::ios::out);
        RecordType record;
        for (long pointer : data_pointers) {
            heap_file.seekg(pointer);
            heap_file.read( (char*)&record, sizeof(RecordType) );
            record.removed = true;
            heap_file.seekp(pointer);
            heap_file.write( (char*)&record, sizeof(RecordType) );
        }
        heap_file.close();
        if (root_detached == DETACH){
            root = -1;
        }
    }


    void print()
    {
        file.open(file_name, std::ios::binary | std::ios::in);
        _print(root, "", true);
        file.close();
    }

    std::vector<RecordType> range_search(KeyType key1, KeyType key2)
    {
        std::vector<long> data_pointers;
        file.open(file_name, std::ios::binary | std::ios::in);
        range_search(key1, key2, root, data_pointers);
        file.close();

        std::vector<RecordType> records;
        records.reserve(data_pointers.size());
        RecordType record;

        std::ifstream heap_file(heap_file_name, std::ios::binary);
        for (long pointer : data_pointers) {
            heap_file.seekg(pointer);
            heap_file.read( (char*)&record, sizeof(RecordType) );
            if (!record.removed){
                records.push_back(record);
            }
        }

        heap_file.close();
        return records;
    }
};


#endif //AVL_FILE_HPP
