#include "scanner.h"

Token::Token(Type type) : type(type) { lexema = ""; }

Token::Token(Type type, const string source) : type(type) {
    lexema = source;
}

std::ostream &operator<<(std::ostream &outs, const Token &tok) {
    if (tok.lexema.empty())
        return outs << Token::token_names[tok.type];
    else
        return outs << Token::token_names[tok.type] << "(" << tok.lexema
                    << ")";
}

std::ostream &operator<<(std::ostream &outs, const Token *tok) {
    return outs << *tok;
}


Scanner::Scanner(const char *s) : input(s), first(0), current(0) {
    reserved["SELECT"] = Token::SELECT;
    reserved["FROM"] = Token::FROM;
    reserved["WHERE"] = Token::WHERE;
    reserved["AND"] = Token::AND;
    reserved["OR"] = Token::OR;
    reserved["IS"] = Token::IS;
    reserved["NOT"] = Token::NOT;
    reserved["INSERT"] = Token::INSERT;
    reserved["INTO"] = Token::INTO;
    reserved["VALUES"] = Token::VALUES;
    reserved["CREATE"] = Token::CREATE;
    reserved["TABLE"] = Token::TABLE;
    reserved["USING"] = Token::USING;
    reserved["INDEX"] = Token::INDEX;
    reserved["FILE"] = Token::FILE;
    reserved["HASH"] = Token::HASH;
    reserved["AVL"] = Token::AVL;
}


Token *Scanner::nextToken() {
    Token *token;
    char c;

    c = nextChar();
    while (c == ' ') c = nextChar();
    if (c == '\0') return new Token(Token::END);
    startLexema();
    if (isdigit(c)) {
        c = nextChar();
        while (isdigit(c)) c = nextChar();
        rollBack();
        token = new Token(Token::NUM, getLexema());
    } else if (isalpha(c)) {
        c = nextChar();
        while (isalpha(c) || isdigit(c) || c == '_') c = nextChar();
        rollBack();
        string lex = getLexema();
        Token::Type ttype = checkReserved(lex);
        if (ttype != Token::ERR)
            token = new Token(ttype);
        else
            token = new Token(Token::ID, getLexema());
    } else if (c == '\'') {
        c = nextChar();
        while (c != '\'') c = nextChar();
        c = nextChar();
        rollBack();
        string lex = getLexema();
        token = new Token(Token::CADENA, getLexema());
    } else if (strchr("();,=*", c)) {
        switch (c) {
            case '(':
                token = new Token(Token::LPAREN);
                break;
            case ')':
                token = new Token(Token::RPAREN);
                break;
            case ';':
                token = new Token(Token::SEMICOLON);
                break;
            case ',':
                token = new Token(Token::COMMA);
                break;
            case '=':
                token = new Token(Token::IS);
                break;
            case '*':
                token = new Token(Token::ASTERISK);
                break;
            default:
                cout << "No deberia llegar aca" << endl;
        }
    } else {
        token = new Token(Token::ERR, getLexema());
    }
    return token;
}

Scanner::~Scanner() {}

char Scanner::nextChar() {
    int c = input[current];
    current++;
    return c;
}

void Scanner::rollBack() { // retract
    current--;
}

void Scanner::startLexema() {
    first = current - 1;
    return;
}

string Scanner::getLexema() {
    return input.substr(first, current - first);
}

Token::Type Scanner::checkReserved(string lexema) {
    std::unordered_map<std::string, Token::Type>::const_iterator it = reserved.find(
            lexema);
    if (it == reserved.end())
        return Token::ERR;
    else
        return it->second;
}