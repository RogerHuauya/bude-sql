#include <string>
#include "parser.h"
#include "scanner.h"

int main() {
    string query = "SELECT name, age, locos, FROM users WHERE age = hola;";
    Scanner scanner(query.c_str());
    Parser parser(&scanner);
    Statement* stm = parser.parse();
    stm->execute();

    return 0;
}