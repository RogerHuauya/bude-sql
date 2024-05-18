#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "bplus.h"
#include "apple.h"


void loadCSV(const std::string& filename, Bplus& tree) {
    std::ifstream file(filename);
    std::string line;

    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string field;
        AppRecord record;

        std::getline(ss, field, ','); // Skip the first field (index)
        std::getline(ss, field, ',');
        record.id = std::stoi(field);
        std::getline(ss, field, ',');
        strncpy(record.track_name, field.c_str(), sizeof(record.track_name) - 1);
        std::getline(ss, field, ',');
        record.size_bytes = std::stoi(field);
        std::getline(ss, field, ',');
        strncpy(record.currency, field.c_str(), sizeof(record.currency) - 1);
        std::getline(ss, field, ',');
        record.price = std::stof(field);
        std::getline(ss, field, ',');
        record.rating_count_tot = std::stoi(field);
        std::getline(ss, field, ',');
        record.rating_count_ver = std::stoi(field);
        std::getline(ss, field, ',');
        record.user_rating = static_cast<UserRating>(std::stoi(field));
        std::getline(ss, field, ',');
        record.user_rating_ver = std::stof(field);
        std::getline(ss, field, ',');
        strncpy(record.ver, field.c_str(), sizeof(record.ver) - 1);
        std::getline(ss, field, ',');
        strncpy(record.cont_rating, field.c_str(), sizeof(record.cont_rating) - 1);
        std::getline(ss, field, ',');
        strncpy(record.prime_genre, field.c_str(), sizeof(record.prime_genre) - 1);
        std::getline(ss, field, ',');
        record.sup_devices_num = std::stoi(field);
        std::getline(ss, field, ',');
        record.ipadSc_urls_num = std::stoi(field);
        std::getline(ss, field, ',');
        record.lang_num = std::stoi(field);
        std::getline(ss, field, ',');
        record.vpp_lic = std::stoi(field) != 0;

        tree.insert(record);
    }
}

int main() {
    Bplus tree("AppleStore", "AppleStore.csv");
    //loadCSV("AppleStore.csv", tree);
    //tree.display();

    try {
        AppRecord record;
        tree.search(284882215, record);
        std::cout << "Found record: " << record.to_string() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
