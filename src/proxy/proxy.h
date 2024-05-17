#pragma once

#include <vector>
#include <string>

#include "apple.h"

using namespace std;

class QueryResult {
public:
    vector<AppRecord> records;
    vector<string> columns;
    string message;
    bool success{};

    QueryResult() = default;
};

class Proxy {
public:
    std::vector<AppRecord> query_records;
    vector<std::string> parser;

    Proxy() = default;

    ~Proxy() = default;

    QueryResult execute_query(string query);
};

QueryResult Proxy::execute_query(string query) {
    QueryResult result;
    result.success = true;
    result.message = std::move(query);
    result.columns = {"id", "app_name"};
    result.records = get_random_records(10);

    return result;
}


std::ostream &operator<<(std::ostream &os, const QueryResult &result) {
    os << "QueryResult message: " << result.message << std::endl;
    os << "Success: " << result.success << std::endl;
    os << "Records: " << std::endl;
    for (const auto &column : result.columns) {
        os << column << " ";
    }
    os << std::endl;
    for (const auto &record : result.records) {
        for (const auto &column : result.columns) {
            os << record[column] << " ";
        }
        os << std::endl;
    }
    return os;
}
