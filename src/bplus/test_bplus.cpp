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

        try {
            std::getline(ss, field, ',');
            record.id = std::stoi(field);

            std::getline(ss, field, ',');
            strncpy(record.track_name, field.c_str(), sizeof(record.track_name) - 1);

            std::getline(ss, field, ',');
            record.size_bytes = std::stoul(field);

            std::getline(ss, field, ',');
            strncpy(record.currency, field.c_str(), sizeof(record.currency) - 1);

            std::getline(ss, field, ',');
            record.price = std::stof(field);

            std::getline(ss, field, ',');
            record.rating_count_tot = std::stoul(field);

            std::getline(ss, field, ',');
            record.rating_count_ver = std::stoul(field);

            std::getline(ss, field, ',');
            record.user_rating = static_cast<UserRating>(std::stof(field) * 2);

            std::getline(ss, field, ',');
            record.user_rating_ver = std::stof(field);

            std::getline(ss, field, ',');
            strncpy(record.ver, field.c_str(), sizeof(record.ver) - 1);

            std::getline(ss, field, ',');
            strncpy(record.cont_rating, field.c_str(), sizeof(record.cont_rating) - 1);

            std::getline(ss, field, ',');
            strncpy(record.prime_genre, field.c_str(), sizeof(record.prime_genre) - 1);

            std::getline(ss, field, ',');
            record.sup_devices_num = std::stoul(field);

            std::getline(ss, field, ',');
            record.ipadSc_urls_num = std::stoul(field);

            std::getline(ss, field, ',');
            record.lang_num = std::stoul(field);

            std::getline(ss, field, ',');
            record.vpp_lic = std::stoi(field) != 0;

            tree.insert(record);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << e.what() << " at line: " << line << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: " << e.what() << " at line: " << line << std::endl;
        }
    }
}

int main() {
    Bplus tree("AppleStore", "AppleStore.csv");
    loadCSV("AppleStore.csv", tree);
    tree.display();


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
