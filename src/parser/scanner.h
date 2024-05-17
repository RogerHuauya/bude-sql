#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

enum TokenType {
    WORD, STRING, GROUP, OPERATOR, LOGIC, EMPTY, EOT
};

struct Token {
    TokenType type;
    std::string value;
};

class Scanner {
public:
    Scanner(const std::string &source) : source(source), cursor(0) {
        readNextChar();
    }

    Token readNextToken() {
        while (std::isspace(currentChar)) readNextChar();

        if (std::isalnum(currentChar)) return readWord();
        if (currentChar == '"' || currentChar == '\'' ||
            currentChar == '`')
            return readString();
        if (currentChar == '(' || currentChar == ')') return readGroupSymbol();
        if (currentChar == '=' || currentChar == '!' || currentChar == '<' ||
            currentChar == '>')
            return readOperator();

        if (currentChar == '\0') return {EOT, ""};

        readNextChar();
        return {EMPTY, ""};
    }

private:
    std::string source;
    size_t cursor;
    char currentChar;

    void readNextChar() {
        if (cursor < source.size()) {
            currentChar = source[cursor++];
        } else {
            currentChar = '\0';
        }
    }

    Token readWord() {
        std::string tokenValue;
        while (std::isalnum(currentChar) || currentChar == '.' ||
               currentChar == '_') {
            tokenValue += currentChar;
            readNextChar();
        }

        if (tokenValue == "AND" || tokenValue == "OR") {
            return {LOGIC, tokenValue};
        }
        if (tokenValue == "IS" || tokenValue == "NOT") {
            return {OPERATOR, tokenValue};
        }
        return {WORD, tokenValue};
    }

    Token readString() {
        char quote = currentChar;
        std::string tokenValue;
        tokenValue += currentChar;
        readNextChar();

        while (currentChar != quote) {
            tokenValue += currentChar;
            readNextChar();
        }
        tokenValue += currentChar;
        readNextChar();

        return {STRING, tokenValue};
    }

    Token readGroupSymbol() {
        char symbol = currentChar;
        readNextChar();
        return {GROUP, std::string(1, symbol)};
    }

    Token readOperator() {
        std::string tokenValue(1, currentChar);
        readNextChar();

        if (currentChar == '=' || currentChar == '<' || currentChar == '>') {
            tokenValue += currentChar;
            readNextChar();
        }

        return {OPERATOR, tokenValue};
    }
};