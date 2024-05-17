#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>
# include "scanner.h"
class Parser {
public:
    Parser(const std::string& source) : scanner(source) {
        readNextToken();
    }

    std::map<std::string, std::vector<std::string>> parseSQL() {
        std::map<std::string, std::vector<std::string>> result;
        parseExpressions(result);
        return result;
    }

private:
    Scanner scanner;
    Token currentToken;

    void readNextToken() {
        currentToken = scanner.readNextToken();
    }

    void parseExpressions(std::map<std::string, std::vector<std::string>>& result) {
        while (currentToken.type != EOT) {
            if (currentToken.type == WORD) {
                std::string key = currentToken.value;
                readNextToken();
                std::vector<std::string> values;
                while (currentToken.type != WORD && currentToken.type != EOT) {
                    if (currentToken.type != EMPTY) {
                        values.push_back(currentToken.value);
                    }
                    readNextToken();
                }
                result[key] = values;
            } else {
                readNextToken();
            }
        }
    }
};