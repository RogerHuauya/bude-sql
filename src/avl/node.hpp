#ifndef NODE_HPP
#define NODE_HPP

#include <fstream>
#include <sstream>
#include <cstring>
#define DETACH (-2)
#define NO_DETACH (-3)


// for different types of keys
template<typename KeyType>
void cp(KeyType &k1, KeyType &k2){
    std::memcpy( (char*)&k1, (char*)&k2, sizeof(KeyType) );
}

template<typename KeyType>
void cp(KeyType &k1, const KeyType &k2){
    std::memcpy( (char*)&k1, (char*)&k2, sizeof(KeyType) );
}

template<typename KeyType>
void cp(KeyType &k1, char*& k2){
    std::memcpy( (char*)&k1, k2, sizeof(KeyType) );
}


template<typename KeyType>
struct Node{
    KeyType key{};
    long data_pointer {-1};

    long right {-1};
    long left {-1};
    long height {0};
    long next {-1};

    explicit Node() = default;

    explicit Node(KeyType k, long physical_pos):data_pointer{physical_pos}{
        cp(key, k);
    }

    Node &operator=(const Node &other){
        cp(key, other.key);
        data_pointer = other.data_pointer;
        next = other.next;
        return *this;
    }
};

template<typename T>
std::ostream& operator<<( std::ostream& ofs, Node<T> &node ) {
    ofs.write( (char*)&node, sizeof(node) );
    return ofs;
}

template<typename T>
std::istream& operator>>( std::istream& ifs, Node<T> &node ){
    ifs.read( (char*)&node, sizeof(node) );
    return ifs;
}

#endif
