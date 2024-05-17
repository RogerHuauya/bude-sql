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

    AppRecord &operator=(const AppRecord &record) {
        id = record.id;
        for (int i = 0; i < 256; ++i) {
            app_name[i] = record.app_name[i];
        }
        size_bytes = record.size_bytes;
        price = record.price;
        rating_count_tot = record.rating_count_tot;
        user_rating = record.user_rating;
        for (int i = 0; i < 4; ++i) {
            cont_rating[i] = record.cont_rating[i];
        }
        for (int i = 0; i < 18; ++i) {
            prime_genre[i] = record.prime_genre[i];
        }
        removed = record.removed;
        return *this;
    }

    std::string operator[](const std::string &key) const {
        if (key == "id") return std::to_string(id);
        if (key == "app_name") return std::string(app_name);
        if (key == "size_bytes") return std::to_string(size_bytes);
        if (key == "price") return std::to_string(price);
        if (key == "rating_count_tot") return std::to_string(rating_count_tot);
        if (key == "user_rating") return std::to_string(user_rating);
        if (key == "cont_rating") return std::string(cont_rating);
        if (key == "prime_genre") return std::string(prime_genre);
        if (key == "removed") return std::to_string(removed);
        throw std::invalid_argument("Invalid key");
    }

};


std::ostream &operator<<(std::ostream &os, const AppRecord &record) {
    os << "id: " << record.id << std::endl;
    os << "app_name: " << record.app_name << std::endl;
    os << "size_bytes: " << record.size_bytes << std::endl;
    os << "price: " << record.price << std::endl;
    os << "rating_count_tot: " << record.rating_count_tot << std::endl;
    os << "user_rating: " << record.user_rating << std::endl;
    os << "cont_rating: " << record.cont_rating << std::endl;
    os << "prime_genre: " << record.prime_genre << std::endl;
    return os;
}


vector<AppRecord> get_random_records(int n) {
    vector<AppRecord> random_records;
    for (int i = 0; i < n; ++i) {
        AppRecord record;
        record.id = i;
        sprintf(record.app_name, "App %d", i);
        record.size_bytes = 1000 * i;
        record.price = 0.99 * i;
        record.rating_count_tot = 100 * i;
        record.user_rating = UserRating_5;
        sprintf(record.cont_rating, "4+");
        sprintf(record.prime_genre, "Games");
        record.removed = false;
        random_records.push_back(record);
    }
    return random_records;
}



