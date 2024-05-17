#include <iostream>
#include <string>
#include "parser.h"

int main() {
    std::string query = "SELECT name, age FROM users WHERE age > 30;";

    Parser parser(query);
    auto result = parser.parseSQL();

    for (const auto& pair : result) {
        std::cout << pair.first << ": ";
        for (const auto& value : pair.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}