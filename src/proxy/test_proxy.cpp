#include "proxy.h"
#include <iostream>

using namespace std;

void testavl(){
    Proxy proxy;
    QueryResult query_result = proxy.execute_query("CREATE TABLE users FROM FILE 'AppleStore.dat' USING INDEX AVL ('price');");
    cout << query_result << endl;
    query_result = proxy.execute_query("SELECT app_name FROM users WHERE price=0;");
    cout << query_result << endl;
}

void testhash(){
    Proxy proxy;
    QueryResult query_result = proxy.execute_query("CREATE TABLE users FROM FILE 'AppleStore.dat' USING INDEX HASH ('app_name');");
    cout << query_result << endl;
    query_result = proxy.execute_query("SELECT app_name FROM users WHERE id=284882215;"); // facebook
    cout << query_result << endl;
}

int main(){
    //testavl();
    testhash();
    return 0;
}
