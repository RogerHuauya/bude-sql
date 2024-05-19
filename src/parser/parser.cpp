#include "parser.h"
#include "scanner.h"

const char *Token::token_names[29] = {
        "LPAREN", "RPAREN", "NUM", "ID", "PRINT", "SEMICOLON", "ERR", "END",
        "CADENA", "SELECT", "FROM", "WHERE",
        "AND", "OR", "IS", "NOT", "INSERT", "INTO", "VALUES", "CREATE", "TABLE",
        "USING", "INDEX", "HASH", "AVL", "FILE", "DELETE", "ASTERISK", "COMMA"};

bool Parser::match(Token::Type ttype) {
    if (check(ttype)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(Token::Type ttype) {
    if (isAtEnd()) return false;
    return current->type == ttype;
}

bool Parser::advance() {
    if (!isAtEnd()) {
        Token *temp = current;
        if (previous) delete previous;
        current = scanner->nextToken();
        previous = temp;
        if (check(Token::ERR)) {
            cout << "Parse error, unrecognised character: " << current->lexema
                 << endl;
            exit(0);
        }
        return true;
    }
    return false;
}

bool Parser::isAtEnd() {
    return (current->type == Token::END);
}

Parser::Parser(Scanner *sc) : scanner(sc) {
    previous = current = nullptr;
};

Statement *Parser::parse() {
    Statement *sql_stm;
    current = scanner->nextToken();
    if (check(Token::ERR)) {
        cout << "Error en scanner - caracter invalido" << endl;
        exit(0);
    }
    if (match(Token::CREATE)){
        sql_stm = parseCreate();
    }

    else if (match(Token::SELECT)) {
        sql_stm = parseSelect();
    } /*else if (match(Token::INSERT)) {
        sql_stm = parseInsert();
    } else if (match(Token::DELETE)) {
        sql_stm = parseDelete();
    }*/

    else {
        cout << "Error: se esperaba SELECT, INSERT, CREATE o DELETE" << endl;
        exit(0);
    }

    if (current->type != Token::SEMICOLON) {
        cout << "Esperaba fin-de-input, se encontro " << current << endl;
        delete sql_stm;
        sql_stm = nullptr;
    }
    delete current;
    return sql_stm;
}

Statement *Parser::parseCreate(){
auto *create_stm = new CreateStatement();
    if (!match(Token::TABLE)) {
        cout << "Error: se esperaba TABLE" << endl;
        exit(0);
    }
    if (!match(Token::ID)) {
        cout << "Error: se esperaba nombre de tabla" << endl;
        exit(0);
    }
    create_stm->set_table_name(previous->lexema);
    if (!match(Token::FROM)){
        cout << "Error: se esperaba FROM" << endl;
        exit(0);
    }
    if (!match(Token::FILE)) {
        cout << "Error: se esperaba FILE" << endl;
        exit(0);
    }
    if (!match(Token::CADENA)) {
        cout << "Error: se esperaba CADENA" << endl;
        exit(0);
    }
    create_stm->set_file_name(previous->lexema.substr(1, previous->lexema.size() - 2));

    if (match(Token::USING)) {
        if (!match(Token::INDEX)) {
            cout << "Error: se esperaba INDEX" << endl;
            exit(0);
        }
        if (!match(Token::HASH) && !match(Token::AVL)) {
            cout << "Error: se esperaba HASH o AVL" << endl;
            exit(0);
        }
        create_stm->set_index_type(previous->type);
        if (!match(Token::LPAREN)) {
            cout << "Error: se esperaba (" << endl;
            exit(0);
        }
        if (!match(Token::CADENA)) {
            cout << "Error: se esperaba nombre de columna" << endl;
            exit(0);
        }
        create_stm->set_index_column(previous->lexema.substr(1, previous->lexema.size() - 2));
        if (!match(Token::RPAREN)) {
            cout << "Error: se esperaba )" << endl;
            exit(0);
        }
    }
    return create_stm;
}


Statement *Parser::parseSelect() {
    auto *select_stm = new SelectStatement();
    if (match(Token::ASTERISK)) {
        select_stm->set_select_all(true);
    }
    while (match(Token::ID)) {
        select_stm->add_select_column(previous->lexema);
        if (!match(Token::COMMA)) {
            break;
        }
    }

    if (!match(Token::FROM)) {
        cout << "Error: se esperaba FROM" << endl;
        exit(0);
    }
    else {
        if (!match(Token::ID)) {
            cout << "Error: se esperaba nombre de tabla" << endl;
            exit(0);
        }
        select_stm->set_table_name(previous->lexema);
    }

    if (match(Token::WHERE)) {
        if (!match(Token::ID)) {
            cout << "Error: se esperaba nombre de columna" << endl;
            exit(0);
        }
        select_stm->set_where_column(previous->lexema);
        if (!match(Token::IS)) {
            cout << "Error: se esperaba IS" << endl;
            exit(0);
        }
        if (match(Token::NOT)) {
            select_stm->set_where_not(true);
        }
        if (!match(Token::NUM) && !match(Token::CADENA)) {
            cout << "Error: se esperaba valor, obtained: " << current << endl;
            exit(0);
        }
        select_stm->set_where_value(previous->lexema);
    }

    return select_stm;
}
