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

class CreateStatement : public Statement {
public:
    void execute();
};

class DeleteStatement : public Statement {
public:
    void execute();
};
