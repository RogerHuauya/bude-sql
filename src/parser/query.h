#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "apple.h"

class QueryResult {
public:
    vector<AppRecord> records;
    vector<string> columns;
    string message;
    bool success{};

    QueryResult() = default;
    friend std::ostream &operator<<(std::ostream &os, const QueryResult &result);
};

