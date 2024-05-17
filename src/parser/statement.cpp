#include "statement.h"
#include <iostream>
using namespace std;


void SelectStatement::execute() {
    cout << "Executing SELECT statement" << endl;
}

/*
void InsertStatement::execute() {
    cout << "Executing INSERT statement" << endl;
}

void CreateStatement::execute() {
    cout << "Executing CREATE statement" << endl;
}

void DeleteStatement::execute() {
    cout << "Executing DELETE statement" << endl;
}
 */