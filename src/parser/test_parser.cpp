#include <string>
#include "parser.h"
#include "scanner.h"

int main() {
    string query = "CREATE TABLE users FROM FILE 'usr/s' USING INDEX HASH ('id');";
    Scanner scanner(query.c_str());
    Parser parser(&scanner);
    Statement* stm = parser.parse();
    stm->execute();


    string query2 = "SELECT name, age, locos, FROM users WHERE age = 'hola';";
    Scanner scanner2(query2.c_str());
    Parser parser2(&scanner2);
    Statement* stm2 = parser2.parse();
    stm2->execute();

    string query3 = "INSERT INTO users VALUES (1, 'Roger', 20, 'Mexico');";
    Scanner scanner3(query3.c_str());
    Parser parser3(&scanner3);
    Statement* stm3 = parser3.parse();
    stm3->execute();

    return 0;
}