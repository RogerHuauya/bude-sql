#include "query.h"

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