#include <string>
#include "parser.h"
#include "scanner.h"

int main() {
    string query = "SELECT name, age, locos, FROM users WHERE age = hola;";
    Scanner scanner(query.c_str());
    Parser parser(&scanner);
    Statement* stm = parser.parse();
    stm->execute();


    string query2 = "CREATE TABLE users FROM FILE usr USING INDEX HASH (id);";
    Scanner scanner2(query2.c_str());
    Parser parser2(&scanner2);
    Statement* stm2 = parser2.parse();
    stm2->execute();

    return 0;
}