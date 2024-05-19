#include "proxy.h"
#include "parser.h"
#include "scanner.h"
#include "query.h"

QueryResult Proxy::execute_query(string query) {
    QueryResult result;

    Scanner scanner(query.c_str());
    Parser parser(&scanner);
    Statement *stm = parser.parse();
    result = stm->execute();

    return result;
}
