#pragma once
#include <vector>
#include <string>
#include "apple.h"

using namespace std;

class Proxy {
public:
    std::vector<AppRecord> query_records;
    vector<std::string> parser;

    Proxy() = default;

    ~Proxy() = default;

    vector<AppRecord> execute_query(string query);
};