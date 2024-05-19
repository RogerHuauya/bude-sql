#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <vector>

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
    char track_name[256]{'\0'};
    unsigned int size_bytes;
    char currency[4]{'\0'};
    float price{};
    unsigned int rating_count_tot{};
    unsigned int rating_count_ver{};
    UserRating user_rating{};
    float user_rating_ver{};
    char ver[16]{'\0'};
    char cont_rating[4]{'\0'};
    char prime_genre[18]{'\0'};
    unsigned int sup_devices_num{};
    unsigned int ipadSc_urls_num{};
    unsigned int lang_num{};
    bool vpp_lic{};

    std::string to_string() const {
        std::stringstream ss;
        ss << "id: " << id << std::endl;
        ss << "track_name: " << track_name << std::endl;
        ss << "size_bytes: " << size_bytes << std::endl;
        ss << "currency: " << currency << std::endl;
        ss << "price: " << price << std::endl;
        ss << "rating_count_tot: " << rating_count_tot << std::endl;
        ss << "rating_count_ver: " << rating_count_ver << std::endl;
        ss << "user_rating: " << user_rating << std::endl;
        ss << "user_rating_ver: " << user_rating_ver << std::endl;
        ss << "ver: " << ver << std::endl;
        ss << "cont_rating: " << cont_rating << std::endl;
        ss << "prime_genre: " << prime_genre << std::endl;
        ss << "sup_devices_num: " << sup_devices_num << std::endl;
        ss << "ipadSc_urls_num: " << ipadSc_urls_num << std::endl;
        ss << "lang_num: " << lang_num << std::endl;
        ss << "vpp_lic: " << vpp_lic << std::endl;
        return ss.str();
    }

    AppRecord &operator=(const AppRecord &record) {
        if (this != &record) {
            id = record.id;
            std::copy(std::begin(record.track_name), std::end(record.track_name), std::begin(track_name));
            size_bytes = record.size_bytes;
            std::copy(std::begin(record.currency), std::end(record.currency), std::begin(currency));
            price = record.price;
            rating_count_tot = record.rating_count_tot;
            rating_count_ver = record.rating_count_ver;
            user_rating = record.user_rating;
            user_rating_ver = record.user_rating_ver;
            std::copy(std::begin(record.ver), std::end(record.ver), std::begin(ver));
            std::copy(std::begin(record.cont_rating), std::end(record.cont_rating), std::begin(cont_rating));
            std::copy(std::begin(record.prime_genre), std::end(record.prime_genre), std::begin(prime_genre));
            sup_devices_num = record.sup_devices_num;
            ipadSc_urls_num = record.ipadSc_urls_num;
            lang_num = record.lang_num;
            vpp_lic = record.vpp_lic;
        }
        return *this;
    }

    std::string operator[](const std::string &key) const {
        if (key == "id") return std::to_string(id);
        if (key == "track_name") return std::string(track_name);
        if (key == "size_bytes") return std::to_string(size_bytes);
        if (key == "currency") return std::string(currency);
        if (key == "price") return std::to_string(price);
        if (key == "rating_count_tot") return std::to_string(rating_count_tot);
        if (key == "rating_count_ver") return std::to_string(rating_count_ver);
        if (key == "user_rating") return std::to_string(user_rating);
        if (key == "user_rating_ver") return std::to_string(user_rating_ver);
        if (key == "ver") return std::string(ver);
        if (key == "cont_rating") return std::string(cont_rating);
        if (key == "prime_genre") return std::string(prime_genre);
        if (key == "sup_devices_num") return std::to_string(sup_devices_num);
        if (key == "ipadSc_urls_num") return std::to_string(ipadSc_urls_num);
        if (key == "lang_num") return std::to_string(lang_num);
        if (key == "vpp_lic") return std::to_string(vpp_lic);
        throw std::invalid_argument("Invalid key");
    }
};


vector<AppRecord> get_random_records(int n);




