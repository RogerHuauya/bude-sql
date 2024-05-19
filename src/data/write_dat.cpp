#include "../model/apple.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
#include <iomanip>

std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    bool insideQuotes = false;
    std::stringstream tokenStream;

    for (char ch : line) {
        if (ch == '\"') {
            insideQuotes = !insideQuotes;
        } else if (ch == ',' && !insideQuotes) {
            tokens.push_back(tokenStream.str());
            tokenStream.str("");
            tokenStream.clear();
        } else {
            tokenStream << ch;
        }
    }
    tokens.push_back(tokenStream.str());  // add the last token

    return tokens;
}

AppRecord parseUsingSscanf(const std::vector<std::string>& tokens) {
    char app_name[256];
    char content_rating[4];
    char prime_genre[20];
    AppRecord record;
    float temp_rating;

    sscanf(tokens[0].c_str(), "%u", &record.id);
    strncpy(app_name, tokens[1].c_str(), 256);
    sscanf(tokens[2].c_str(), "%u", &record.size_bytes);
    sscanf(tokens[4].c_str(), "%f", &record.price);
    sscanf(tokens[5].c_str(), "%u", &record.rating_count_tot);
    sscanf(tokens[7].c_str(), "%f", &temp_rating);
    strncpy(content_rating, tokens[10].c_str(), 4);
    strncpy(prime_genre, tokens[11].c_str(), 18);

    record.user_rating = static_cast<UserRating>(static_cast<int>(temp_rating * 2)); // enum
    strcpy(record.app_name, app_name);
    strcpy(record.cont_rating, content_rating);
    strcpy(record.prime_genre, prime_genre);
    return record;
}

void write_dat_from_csv(const std::string& f = "../data/AppleStore.csv") {
    std::ifstream file(f);
    if (!file) {
        std::cerr << "Failed to open " << f << std::endl;
        return;
    }

    std::string line;
    std::vector<AppRecord> records;
    std::getline(file, line);  // Skip header line
    int l = 2;
    while (std::getline(file, line)) {
        AppRecord record;
        memset(record.app_name, 0, sizeof(record.app_name));
        memset(record.cont_rating, 0, sizeof(record.cont_rating));
        memset(record.prime_genre, 0, sizeof(record.prime_genre));

        std::vector<std::string> tokens = parseCSVLine(line);
        record = parseUsingSscanf(tokens);
        records.push_back(record);
    }

    file.close();

    std::cout << "\n\n";
    for(const auto& r : records) {
        //std::cout << r.id << " " << r.app_name << " " << r.size_bytes << " " << r.price << " " << r.rating_count_tot << " " << r.user_rating << " " << r.cont_rating << " " << r.prime_genre << std::endl;
    }

    std::ofstream out_file("AppleStore.dat", std::ios::binary);
    if (!out_file) {
        std::cerr << "Failed to open AppleStore.dat for writing" << std::endl;
        return;
    }

    for (const auto& record : records) {
        out_file.write(reinterpret_cast<const char*>(&record), sizeof(AppRecord));
    }

    out_file.close();
}

int main(){
    write_dat_from_csv();
    return 0;
}

