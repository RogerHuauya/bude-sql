#include "apple.hpp"
#include "ExHash.hpp"  
#include "utils.hpp"   

int main() {
    auto keyExtractor = [](const AppRecord& record) {
        return record.app_name;
    };

    ExtendibleHashing<AppRecord, decltype(keyExtractor)> eh("hash_idx.dat", "data13.dat", keyExtractor);

    AppRecord r1 = {1, "App1", 1000, 0.99, 100, UserRating::UserRating_4, "4+", "Games", false};
    eh.write_record(r1);

    AppRecord r2 = {2, "App2", 2000, 1.99, 200, UserRating::UserRating_3, "9+", "Productivity", false};
    eh.write_record(r2);

    AppRecord r3 = {3, "App3", 3000, 2.99, 300, UserRating::UserRating_5, "12+", "Education", false};
    eh.write_record(r3);

    std::cout << eh << std::endl;

    std::vector<AppRecord> foundRecords = eh.search("App1");
    if (!foundRecords.empty()) {
        std::cout << "Records found: " << std::endl;
        for (const auto& record : foundRecords) {
            std::cout << record.to_string() << std::endl;
        }
    } else {
        std::cout << "Record not found" << std::endl;
    }

    return 0;
}
