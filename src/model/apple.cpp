#include "apple.h"

std::ostream &operator<<(std::ostream &os, const AppRecord &record) {
    os << "id: " << record.id << std::endl;
    os << "track_name: " << record.track_name << std::endl;
    os << "size_bytes: " << record.size_bytes << std::endl;
    os << "currency: " << record.currency << std::endl;
    os << "price: " << record.price << std::endl;
    os << "rating_count_tot: " << record.rating_count_tot << std::endl;
    os << "rating_count_ver: " << record.rating_count_ver << std::endl;
    os << "user_rating: " << record.user_rating << std::endl;
    os << "user_rating_ver: " << record.user_rating_ver << std::endl;
    os << "ver: " << record.ver << std::endl;
    os << "cont_rating: " << record.cont_rating << std::endl;
    os << "prime_genre: " << record.prime_genre << std::endl;
    os << "sup_devices_num: " << record.sup_devices_num << std::endl;
    os << "ipadSc_urls_num: " << record.ipadSc_urls_num << std::endl;
    os << "lang_num: " << record.lang_num << std::endl;
    os << "vpp_lic: " << record.vpp_lic << std::endl;
    return os;
}

vector<AppRecord> get_random_records(int n) {
    vector<AppRecord> random_records;
    for (int i = 0; i < n; ++i) {
        AppRecord record;
        record.id = i;
        sprintf(record.track_name, "track_name %d", i);
        record.size_bytes = 1000 * i;
        record.price = 0.99 * i;
        record.rating_count_tot = 100 * i;
        record.user_rating = UserRating_5;
        sprintf(record.cont_rating, "4+");
        sprintf(record.prime_genre, "Games");
        random_records.push_back(record);
    }
    return random_records;
}
