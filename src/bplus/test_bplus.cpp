#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "bplus.h"
#include "apple.h"

void loadCSV(const std::string& filename, Bplus& tree) {
    std::ifstream file(filename, ios::binary);
    AppRecord r;
    while(file.read((char*)&r, sizeof(AppRecord))){
        cout << "xd" << endl;
        try{
            tree.insert(r);
        } catch (const std::exception& e){
            std::cerr << "Error: " << std::endl;
        }

    }
}

int main() {
    Bplus tree("AppleStore", "AppleStore.dat");
    tree.load_csv();
    //tree.display();


    try {
        AppRecord record;
        tree.search(420009108, record);
        std::cout << "Found record: " << record.to_string() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    /*
    try {
        tree.remove(284882215);
        std::cout << "Record removed" << std::endl;
        AppRecord record;
        tree.search(284882215, record);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
     */
    return 0;
}
