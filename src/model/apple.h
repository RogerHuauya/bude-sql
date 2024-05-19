#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <vector>
#include <array>

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

    std::string to_string() const {
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

    std::string operator[](const std::string &key) const {
        if (key == "id") return std::to_string(id);
        if (key == "track_name") return std::string(app_name);
        if (key == "size_bytes") return std::to_string(size_bytes);
        if (key == "price") return std::to_string(price);
        if (key == "rating_count_tot") return std::to_string(rating_count_tot);
        if (key == "user_rating") return std::to_string(user_rating);
        if (key == "cont_rating") return std::string(cont_rating);
        if (key == "prime_genre") return std::string(prime_genre);
        throw std::invalid_argument("Invalid key");
    }
    AppRecord &operator=(const AppRecord &record) {
        if (this != &record) {
            id = record.id;
            std::copy(std::begin(record.app_name), std::end(record.app_name), std::begin(app_name));
            size_bytes = record.size_bytes;
            price = record.price;
            rating_count_tot = record.rating_count_tot;
            user_rating = record.user_rating;
            std::copy(std::begin(record.cont_rating), std::end(record.cont_rating), std::begin(cont_rating));
            std::copy(std::begin(record.prime_genre), std::end(record.prime_genre), std::begin(prime_genre));
        }
        return *this;
    }
};





vector<AppRecord> get_random_records(int n);




