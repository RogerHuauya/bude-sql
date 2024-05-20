#ifndef BUDE_SQL_AVL_QUERIES_HPP
#define BUDE_SQL_AVL_QUERIES_HPP

#include "avl.hpp"
#include "ExHash.hpp"
#include <charconv>
// AVL QUERIES
#define CREATE_INDEX(attribute, type) \
    if (index_column == #attribute) { \
        std::function<type(AppRecord &)> index = [](AppRecord& app) {return app.attribute;}; \
        AVLFile<type, AppRecord> avl("AppleStore.dat", #attribute, index); \
        if (avl) { \
            std::cout << "El índice ya existe" << std::endl; \
        } else { \
            avl.create_index(); \
        } \
    }



#define SELECT_ATTRIBUTE(attribute, type) \
    if (where_column == #attribute) {     \
        std::function<type(AppRecord &)> index = [=](AppRecord& record) { return record.attribute; }; \
        AVLFile<type, AppRecord> avl("AppleStore.dat" ,#attribute, index); \
        if(!avl){std::cout << "index created" << std::endl;avl.create_index();}\
        type search_value{}; \
        std::string str = where_value; \
        auto tmp = std::from_chars(str.data(), str.data() + str.size(), search_value); \
        result.records = std::move(avl.search(search_value));\
    }\
/*
#define SELECT_RANGE(attribute, type) \
    if (query.where_attribute == #attribute) { \
        std::function<type(AppRecord &)> index = [=](AppRecord& record) { return record.attribute; }; \
        AVLFile<type, AppRecord> avl(APP_STORE_FILE ,#attribute, index); \
        if(!avl){std::cout << "index created, range" << std::endl; avl.create_index();} \
        type init{}, ending{}; \
        std::string str_i = query.init; std::string str_e = query.ending; \
        auto resutl1 = std::from_chars(str_i.data(), str_i.data() + str_i.size(), init); \
        auto resutl2 = std::from_chars(str_e.data(), str_e.data() + str_e.size(), ending); \
        records = std::move(avl.range_search(init, ending)); \
    }\
*/

#define CREATE_INDEX_HASH(attribute, type) \
    if (index_column == #attribute) { \
        std::function<type(const AppRecord &)> index = [](const AppRecord& app) {return app.attribute;}; \
        ExtendibleHashing<AppRecord, decltype(index)> eh("hash_idx.dat", "data13.dat", index, "AppleStore.dat");\
        ofstream tmp("xd"); \
        tmp << eh; \
    } \

#define SELECT_ATTRIBUTE_HASH(attribute, type) \
    if (where_column == #attribute) {     \
        std::function<type(const AppRecord &)> index = [](const AppRecord& app) {return app.attribute;}; \
        ExtendibleHashing<AppRecord, decltype(index)> eh("hash_idx.dat", "data13.dat", index, "AppleStore.dat");\
        type search_value{}; \
        std::string str = where_value; \
        auto tmp = std::from_chars(str.data(), str.data() + str.size(), search_value); \
        result.records = std::move(eh.search(search_value));\
    }\

#endif //BUDE_SQL_AVL_QUERIES_HPP
