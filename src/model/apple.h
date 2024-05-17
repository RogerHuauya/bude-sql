#pragma once
#include <iostream>
#include <sstream>

using namespace std;

enum UserRating {
    UserRating_0 = 0,
    UserRating_0_5 = 1,
    UserRating_1 = 2,
    UserRating_1_5 = 3,
    UserRating_2 = 4,
    UserRating_2_5 = 5,
    UserRating_3 = 6,
    UserRating_3_5 = 7,
    UserRating_4 = 8,
    UserRating_4_5 = 9,
    UserRating_5 = 10
};


struct AppRecord {
    unsigned int id{};
    char app_name[256]{'\0'};
    unsigned int size_bytes;
    float price{};
    unsigned int rating_count_tot{};
    UserRating user_rating{};
    char cont_rating[4]{'\0'};
    char prime_genre[18]{'\0'};
    bool removed{};

    std::string to_string() {
        std::stringstream ss;
        ss << "id: " << id << std::endl;
        ss << "app_name: " << app_name << std::endl;
        ss << "size_bytes: " << size_bytes << std::endl;
        ss << "price: " << price << std::endl;
        ss << "rating_count_tot: " << rating_count_tot << std::endl;
        ss << "user_rating: " << user_rating << std::endl;
        ss << "cont_rating: " << cont_rating << std::endl;
        ss << "prime_genre: " << prime_genre << std::endl;
        return ss.str();
    }

};