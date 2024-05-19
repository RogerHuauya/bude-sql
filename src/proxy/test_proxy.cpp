#include "proxy.h"
#include <iostream>

using namespace std;
int main(){
    Proxy proxy;
    QueryResult query_result = proxy.execute_query("CREATE TABLE users FROM FILE '/Users/roger/git/github/bude-sql/cmake-build-debug/AppleStore.csv' USING INDEX HASH ('id');");
    cout << query_result << endl;
    query_result = proxy.execute_query("SELECT track_name FROM users WHERE id=284882215;");
    cout << query_result << endl;
    return 0;
}
