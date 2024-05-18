#pragma once

#include <vector>
#include <string>

#include "apple.h"
#include "query.h"

using namespace std;


class Proxy {
public:
    std::vector<AppRecord> query_records;

    Proxy() = default;

    ~Proxy() = default;

    static QueryResult execute_query(string query);
};



