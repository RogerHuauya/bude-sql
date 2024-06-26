#include <iostream>
#include "statement.h"
#include "bplus.h"
#include "avl_queries.hpp"
#include "scanner.h"

using namespace std;

Bplus *bplus;


QueryResult CreateStatement::execute() {
    cout << "Executing CREATE statement" << endl;
    cout << "File name: " << file_name << endl;
    cout << "Index type: " << index_type << endl;
    cout << "Index column: " << index_column << endl;
    cout << "Table name: " << get_table_name() << endl;
    QueryResult result;
    result.success = true;
    result.message = "Table created and csv loaded";
    if(index_type == Token::AVL){
        CREATE_INDEX(price, float)
    }else if(index_type == Token::HASH){
        CREATE_INDEX_HASH(id, unsigned int)
    }else{
        bplus = new Bplus(get_table_name(), file_name);
        bplus->load_csv();
    }
    return result;
}

QueryResult SelectStatement::execute() {
    cout << "Executing SELECT statement" << endl;
    cout << "Select column: ";
    for (const auto &column: select_column) {
        cout << column << " ";
    }
    cout << endl;
    cout << "Where column: " << where_column << endl;
    cout << "Where value: " << where_value << endl;
    cout << "Select all: " << select_all << endl;
    cout << "Where not: " << where_not << endl;
    cout << "Table name: " << get_table_name() << endl;

    QueryResult result;
    if (select_all) {
        result.columns = {"id", "track_name", "size_bytes", "currency",
                          "price", "rating_count_tot", "rating_count_ver",
                          "user_rating", "user_rating_ver", "ver",
                          "cont_rating", "prime_genre", "sup_devices.num",
                          "ipadSc_urls.num", "lang.num", "vpp_lic"};

    } else {
        result.columns = select_column;
    }

    if (where_column == "id") {
        //AppRecord record;
        //bplus->search(stoi(where_value), record);
        //result.records.push_back(record);
        SELECT_ATTRIBUTE_HASH(id, unsigned int)
        result.success = true;
        result.message = "Record found";
    } else if (where_column == "price"){
        SELECT_ATTRIBUTE(price, float)
        result.success = true;
        result.message = "Record found";
    } else if (where_column == "app_name"){
        //SELECT_ATTRIBUTE_HASH(app_name)
        result.success = true;
        result.message = "Record found";
    }

    return result;
}

QueryResult InsertStatement::execute() {
    cout << "Executing INSERT statement" << endl;
    cout << "Values: " << endl;
    for (const auto &value: values) {
        cout << value << " ";
    }
    cout << endl;
    cout << "Table name: " << get_table_name() << endl;
}

QueryResult DeleteStatement::execute() {
    cout << "Executing DELETE statement" << endl;
}