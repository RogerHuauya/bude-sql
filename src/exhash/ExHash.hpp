#ifndef EXTENDIBLE_HASHING_HPP
#define EXTENDIBLE_HASHING_HPP

#include "utils.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <functional>
#include <vector>
#include <type_traits>
#include "utils.hpp"

using namespace std;

const int bf = 20;
const int D = 14;

struct BinHash {
    char bin_id[D];
    long id;
    int next_pos;

    BinHash() {
        memset(bin_id, 0, D);
        id = -1;
        next_pos = -1;
    }

    BinHash(const string& bin_id_str, long id) {
        strncpy(bin_id, bin_id_str.c_str(), D);
        this->id = id;
        this->next_pos = -1;
    }

    void showData() const {
        cout << bin_id << " " << id << " " << next_pos << endl;
    }
};

template<typename Record>
struct Bucket {
    long id;
    long size;
    Record records[bf];
    long nextBucket;

    Bucket() : id(0), size(0), nextBucket(-1) {}

    Bucket(long id_, long size_) : id(id_), size(size_), nextBucket(-1) {}

    bool isFull() const {
        return size >= bf;
    }

    void insertRecord(const Record& record) {
        if (!isFull()) {
            records[size] = record;
            size++;
        }
    }

    void showData() const {
        cout << "[" << endl;
        for (int i = 0; i < size; i++)
            cout << records[i].to_string() << endl;
        cout << "]" << endl;
    }
};

template<typename Record>
Bucket<Record> reBuck(BinHash& bh, fstream& file1, fstream& file2, string& key, int& d) {
    Bucket<Record> bucket;

    if (d > D) {
        file2.seekg(bh.id * sizeof(Bucket<Record>), ios::beg);
        file2.read((char*)(&bucket), sizeof(Bucket<Record>));
        return bucket;
    }

    string bin_str = "";
    for (size_t i = key.size() - 1; i > key.size() - 1 - d; i--) bin_str = key[i] + bin_str;
    if (string(bh.bin_id) == bin_str) {
        if (bh.next_pos != -1) {
            file1.seekg(bh.next_pos * sizeof(BinHash), ios::beg);
            file1.read((char*)(&bh), sizeof(BinHash));
            d++;
            return reBuck<Record>(bh, file1, file2, key, d);
        } else {
            file2.seekg(bh.id * sizeof(Bucket<Record>), ios::beg);
            file2.read((char*)(&bucket), sizeof(Bucket<Record>));
            return bucket;
        }
    } else {
        file1.read((char*)(&bh), sizeof(BinHash));
        if (bh.next_pos != -1) {
            file1.seekg(bh.next_pos * sizeof(BinHash), ios::beg);
            file1.read((char*)(&bh), sizeof(BinHash));
            d++;
            return reBuck<Record>(bh, file1, file2, key, d);
        } else {
            file2.seekg(bh.id * sizeof(Bucket<Record>), ios::beg);
            file2.read((char*)(&bucket), sizeof(Bucket<Record>));
            return bucket;
        }
    }
}

template<typename Record, typename KeyExtractor>
class ExtendibleHashing {
private:
    string filename;
    string filename2;
    int buckets;
    hash<unsigned int> fhash;
    KeyExtractor keyExtractor;

public:
    ExtendibleHashing() : buckets(0) {}

    string fl1() const {
        return filename;
    }
    string fl2() const {
        return filename2;
    }

    ~ExtendibleHashing() = default;

    explicit ExtendibleHashing(const string& fl1, const string& fl2, KeyExtractor keyExtractor, const string& heapfile)
            : filename(fl1), filename2(fl2), buckets(0), keyExtractor(keyExtractor) {
        fstream file1(filename, ios::binary | ios::in | ios::out);
        fstream file2(filename2, ios::binary | ios::in | ios::out);



        if (!file1 || !file2) {
            cout << "No existen los archivos... creándolos..." << endl;
            ofstream file1_out(filename, ios::binary);
            ofstream file2_out(filename2, ios::binary);

            BinHash A("0", 0);
            BinHash B("1", 1);

            file1_out.write((char*)(&A), sizeof(BinHash));
            file1_out.write((char*)(&B), sizeof(BinHash));
            file1_out.close();

            Bucket<Record> C(0, 0);
            Bucket<Record> E(1, 0);
            file2_out.write((char*)(&C), sizeof(Bucket<Record>));
            file2_out.write((char*)(&E), sizeof(Bucket<Record>));
            file2_out.close();

            buckets = 2;

            insert_all_data(heapfile);
        } else {
            cout << "Archivos cargados correctamente" << endl;
            Bucket<Record> ex;
            while (file2.read((char*)(&ex), sizeof(Bucket<Record>))) buckets++;
            file2.close();
        }
    }

    void insert_all_data(const string& heapfile){
        ifstream f(heapfile, ios::binary);
        Record r;
        while(f.read((char*)&r, sizeof(Record))){
            this->write_record(r);
        }
        f.close();
    }

    void write_record(const Record& record) {
        fstream file1(filename, ios::binary | ios::in | ios::out);
        fstream file2(filename2, ios::binary | ios::in | ios::out);
        write_record(record, file1, file2);
        file1.close();
        file2.close();
    }

    void write_record(const Record& record, fstream& file1, fstream& file2) {
        int key_temp = fhash(keyExtractor(record));
        string key = bin_h(key_temp, D); // Ensure bin_h is visible
        //cout << "Key: " << key << endl;

        BinHash bh;

        file1.seekg(0, ios::beg);
        file1.read((char*)(&bh), sizeof(BinHash));

        int level = 1;
        Bucket<Record> bucket_insert = reBuck<Record>(bh, file1, file2, key, level);

        while (bucket_insert.nextBucket != -1) {
            file2.seekg(bucket_insert.nextBucket * sizeof(Bucket<Record>), ios::beg);
            file2.read((char*)(&bucket_insert), sizeof(Bucket<Record>));
        }

        if (!bucket_insert.isFull()) {
            int pos = file2.tellg() / sizeof(Bucket<Record>) - 1;
            bucket_insert.insertRecord(record);
            file2.seekp(pos * sizeof(Bucket<Record>), ios::beg);
            file2.write((char*)(&bucket_insert), sizeof(Bucket<Record>));
            //cout << "Record inserted in bucket ID: " << bh.id << endl;
            return;
        } else if (bucket_insert.isFull() && level < D) {
            //cout << "Bucket is full, time to split" << endl;
            //bucket_insert.showData();
            //cout << endl;

            this->buckets += 2;

            int act_pos = file1.tellg() / sizeof(BinHash) - 1;
            file1.seekg(0, ios::end);
            bh.next_pos = file1.tellg() / sizeof(BinHash);

            string ble = bh.bin_id;
            BinHash bh_left;
            strncpy(bh_left.bin_id, ("0" + ble).c_str(), D);

            Bucket<Record> bucket_left;
            file2.seekg(0, ios::end);
            int id_left = file2.tellg() / sizeof(Bucket<Record>);
            bucket_left.id = id_left;
            bh_left.id = id_left;
            file2.seekp(0, ios::end);
            file2.write((char*)(&bucket_left), sizeof(Bucket<Record>));

            file1.seekp(act_pos * sizeof(BinHash), ios::beg);
            file1.write((char*)(&bh), sizeof(BinHash));
            file1.seekp(0, ios::end);
            file1.write((char*)(&bh_left), sizeof(BinHash));

            BinHash bh_right;
            strncpy(bh_right.bin_id, ("1" + ble).c_str(), D);

            Bucket<Record> bucket_right;
            file2.seekg(0, ios::end);
            int id_right = file2.tellg() / sizeof(Bucket<Record>);
            bucket_right.id = id_right;
            bh_right.id = id_right;
            file2.write((char*)(&bucket_right), sizeof(Bucket<Record>));
            file1.write((char*)(&bh_right), sizeof(BinHash));

            for (int i = 0; i < bucket_insert.size; ++i) {
                string new_key = bin_h(fhash(keyExtractor(bucket_insert.records[i])), D);
                if (new_key.back() == '0') {
                    bucket_left.insertRecord(bucket_insert.records[i]);
                } else {
                    bucket_right.insertRecord(bucket_insert.records[i]);
                }
            }

            file2.seekp(bh_left.id * sizeof(Bucket<Record>), ios::beg);
            file2.write((char*)(&bucket_left), sizeof(Bucket<Record>));
            file2.seekp(bh_right.id * sizeof(Bucket<Record>), ios::beg);
            file2.write((char*)(&bucket_right), sizeof(Bucket<Record>));

            file2 << flush;
            file1 << flush;
            write_record(record, file1, file2);

            file2.seekp(bh.id * sizeof(Bucket<Record>), ios::beg);
            Bucket<Record> bas;
            file2.write((char*)(&bas), sizeof(Bucket<Record>));
        } else if (bucket_insert.isFull() && level == D) {
            //cout << "Bucket is full, D is reach, time to next bucket" << endl;
            buckets++;
            Bucket<Record> new_bucket;
            int pos = file2.tellg() / sizeof(Bucket<Record>) - 1;
            file2.seekg(0, ios::end);
            bucket_insert.nextBucket = file2.tellg() / sizeof(Bucket<Record>);
            new_bucket.id = bucket_insert.nextBucket;
            new_bucket.insertRecord(record);
            file2.write((char*)(&new_bucket), sizeof(Bucket<Record>));
            file2.seekp(pos * sizeof(Bucket<Record>), ios::beg);
            file2.write((char*)(&bucket_insert), sizeof(Bucket<Record>));
        }
    }

    template<typename T>
    vector<Record> search(T key) const {
        fstream file1(filename, ios::binary | ios::in);
        fstream file2(filename2, ios::binary | ios::in);

        vector<Record> foundRecords;

        if (!file1.is_open() || !file2.is_open()) {
            cout << "Error opening files for reading." << endl;
            return foundRecords;
        }

        BinHash bh;
        Bucket<Record> bucket;
        file1.seekg(0, ios::beg);

        while (file1.read((char*)(&bh), sizeof(BinHash))) {
            long bucket_id = bh.id;

            do {
                file2.seekg(bucket_id * sizeof(Bucket<Record>), ios::beg);
                file2.read((char*)(&bucket), sizeof(Bucket<Record>));

                for (int i = 0; i < bucket.size; i++) {
                    if (bucket.records[i].matches(key)) {
                        foundRecords.push_back(bucket.records[i]);
                    }
                }

                bucket_id = bucket.nextBucket;
            } while (bucket_id != -1);
        }

        file1.close();
        file2.close();

        return foundRecords;
    }
};

template<typename Record, typename KeyExtractor>
ostream& operator<<(ostream& os, const ExtendibleHashing<Record, KeyExtractor>& ex) {
    fstream file1(ex.fl1(), ios::binary | ios::in);
    fstream file2(ex.fl2(), ios::binary | ios::in);

    if (!file1.is_open() || !file2.is_open()) {
        os << "Error opening files for reading." << endl;
        return os;
    }

    os << "BinHash entries:" << endl;
    BinHash bh;
    while (file1.read((char*)(&bh), sizeof(BinHash))) {
        os << "BinID: " << bh.bin_id << ", BucketID: " << bh.id << ", NextPos: " << bh.next_pos << endl;
    }

    os << "\nBuckets:" << endl;
    Bucket<Record> bucket;
    while (file2.read((char*)(&bucket), sizeof(Bucket<Record>))) {
        os << "Bucket ID: " << bucket.id << ", Size: " << bucket.size << ", NextBucket: " << bucket.nextBucket << endl;
        for (int i = 0; i < bucket.size; i++) {
            os << "  Record " << i + 1 << ": ";
            os << bucket.records[i].to_string() << endl;
        }
        os << endl;
    }

    file1.close();
    file2.close();
    return os;
}

#endif // EXTENDIBLE_HASHING_HPP