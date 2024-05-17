#pragma once

#include <sstream>
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

#include <unordered_map>

using namespace std;

class Token {
public:
    enum Type {
        LPAREN = 0,
        RPAREN,
        NUM,
        ID,
        PRINT,
        SEMICOLON,
        ERR,
        END,
        CADENA,
        SELECT,
        FROM,
        WHERE,
        AND,
        OR,
        IS,
        NOT,
        INSERT,
        INTO,
        VALUES,
        CREATE,
        TABLE,
        USING,
        INDEX,
        HASH,
        AVL,
        FILE,
        DELETE,
        ASTERISK,
        COMMA
    };
    static const char *token_names[29];
    Type type;
    string lexema;

    Token(Type);

    Token(Type, const string source);

    friend std::ostream &operator<<(std::ostream &outs, const Token &tok);
    friend std::ostream &operator<<(std::ostream &outs, const Token *tok);
};


class Scanner {
public:
    Scanner(const char *in_s);

    Token *nextToken();

    ~Scanner();

private:
    string input;
    int first, current;
    unordered_map<string, Token::Type> reserved;

    char nextChar();

    void rollBack();

    void startLexema();

    string getLexema();

    Token::Type checkReserved(string);

};