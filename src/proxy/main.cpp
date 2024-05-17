#include "proxy.h"

int main(){
    Proxy proxy;
    proxy.execute_query("SELECT * FROM table_name;");
    return 0;
}
