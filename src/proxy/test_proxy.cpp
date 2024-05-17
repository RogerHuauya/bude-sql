#include "proxy.h"
#include <iostream>
#include <utility>

using namespace std;
int main(){
    Proxy proxy;
    QueryResult query_result = proxy.execute_query("SELECT * FROM table_name;");
    cout << query_result << endl;
    return 0;
}
