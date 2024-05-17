#ifndef PROXY_H
#define PROXY_H

#include <vector>
#include <string>

#include "apple.h"

using namespace std;

class QueryResult {
public:
    vector<AppRecord> records;
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

    result.records = get_random_records(10);

    return result;
}


std::ostream &operator<<(std::ostream &os, const QueryResult &result) {
    os << "QueryResult message: " << result.message << std::endl;
    os << "Success: " << result.success << std::endl;
    os << "Records: " << std::endl;
    for (const auto &record : result.records) {
        os << record << std::endl;
    }
    return os;
}


#endif //PROXY_H