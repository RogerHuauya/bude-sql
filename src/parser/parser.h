#pragma once

#include "scanner.h"
#include "statement.h"

class Parser {
private:
    Scanner *scanner;
    Token *current, *previous;

    bool match(Token::Type ttype);

    bool check(Token::Type ttype);

    bool advance();

    bool isAtEnd();

public:
    Parser(Scanner* scanner);
    Statement *parse();
    Statement *parseSelect();
    /*
    Statement *parseInsert();
    Statement *parseCreate();
    Statement *parseDelete();
     */
};