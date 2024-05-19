#include "proxy.h"
#include <iostream>

using namespace std;
int main(){
    Proxy proxy;
    QueryResult query_result = proxy.execute_query("CREATE TABLE users FROM FILE 'AppleStore.dat' USING INDEX AVL ('price');");
    cout << query_result << endl;
    query_result = proxy.execute_query("SELECT track_name FROM users WHERE price=0;");
    cout << query_result << endl;
    return 0;
}
