#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Statement {
private:
    string table_name;
public:
    virtual void execute() = 0;
    void set_table_name(string _table){
        this->table_name = std::move(_table);
    }
    string get_table_name(){
        return table_name;
    }
};

class CreateStatement : public Statement {
    string file_name;
    int index_type;
    string index_column;
public:
    void execute();
    string index_name;
    void set_file_name(string _file_name){
        this->file_name = _file_name;
    }
    void set_index_type(int _index_type){
        this->index_type = _index_type;
    }
    void set_index_column(string _index_column){
        this->index_column = std::move(_index_column);
    }
};

class SelectStatement : public Statement {
    string where_column;
    bool select_all = false;
    bool where_not = false;
    string where_value = "";
    vector<string> select_column;
public:
    void set_where_column(string _where_column){
        this->where_column = _where_column;
    }
    void set_where_value(string _value){
        this->where_value = _value;
    }
    bool set_select_all(bool _select_all){
        this->select_all = _select_all;
    }
    void add_select_column(const string& column){
        this->select_column.push_back(column);
    }
    void set_where_not(bool _where_not){
        this->where_not = _where_not;
    }
    void execute();
};

class InsertStatement : public Statement {
public:
    void execute();
};

class DeleteStatement : public Statement {
public:
    void execute();
};
