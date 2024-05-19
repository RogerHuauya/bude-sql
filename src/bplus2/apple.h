#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <array>

using namespace std;

const int S = 256;
const int M = 3;

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


struct Record {
    unsigned int id{};
    std::array<char, 256> app_name{'\0'};
    unsigned int size_bytes;
    float price{};
    unsigned int rating_count_tot{};
    UserRating user_rating{};
    std::array<char,256> cont_rating{'\0'};
    std::array<char,256> prime_genre{'\0'};
    bool removed{};
    Record(){}
    Record(unsigned int _id,std::array<char, 256> _app,unsigned int _sz,float _price,unsigned int rct,std::array<char, 256> cr ,std::array<char, 256>pr ,bool remo){
      id = _id;
      app_name = _app;
      size_bytes = _sz;
      price = _price;
      rating_count_tot = rct;
      cont_rating = cr;
      prime_genre = pr;
      removed = remo;
    }
};




struct RecordAux {
  Record record;
  enum Attribute { ID,APP_NAME, SIZE_BYTES, PRICE, RATING_COUNT_TOT,USER_RATING,CONT_RATING,PRIME_GENRE,REMOVED };
  RecordAux::Attribute attr;

	RecordAux(){}
	RecordAux(Record _record,RecordAux::Attribute _attr){
		record = _record;attr = _attr;
	}
	std::string operator()(){
  	switch (attr) {
		case ID:
				return std::to_string(record.id);
        case SIZE_BYTES:
				return std::to_string(record.size_bytes);
		case PRICE:
				return std::to_string(record.price);
        case RATING_COUNT_TOT:
				return std::to_string(record.rating_count_tot);
		case USER_RATING:
				return std::to_string(record.user_rating);
        default:
				std::cerr << "Atributo no válido" << std::endl;
      	exit(EXIT_FAILURE);
    }
 	}
	std::array<char,256> operator()(Attribute attr){
		switch (attr) {
    	case APP_NAME:
            return record.app_name;
    	case CONT_RATING:
            return record.cont_rating;
        case PRIME_GENRE:
            return record.prime_genre;
      default:
				std::cerr << "Atributo no válido" << std::endl;
        exit(EXIT_FAILURE);
    }
	}
};


// vector<Record> get_random_records(int n);





template<typename T>
struct Nodo{
	T index[M];
	int pointers[M+1];
	size_t size = 0;
	bool leaf = true;
};

template<>
struct Nodo<std::array<char,S>>{
	std::array<char,S> index[M];
	int pointers[M+1];
	size_t size=0;
	bool leaf=true;
};

struct Bucket{
	Record records[M];
	int next=-1;
	int size=0;
};





template <typename T>
std::ostream& operator<<(std::ostream &os,Nodo<T> n1){
	os << "{";
	os << n1.size;
	os << " [ ";
	for (int i=0;i<M;i++){
		os << n1.index[i] << "|";
	}
	os << " ] [";
	for (int i=0;i<M+1;i++){
		os << n1.pointers[i] << "|";
	}
	os<<" ]}";
	return os;
}

template <>
std::ostream& operator<<(std::ostream &os,Nodo<std::array<char, S>> n1){
	os << "{ ";
	os << std::boolalpha << n1.leaf << " ";
	os << n1.size;
	os << " [ ";
	for (int i=0;i<M;i++){
		for(auto a:n1.index[i]){
			os << a;
		}
		os << " | ";
	}
	os << " ] [";
	for (int i=0;i<M+1;i++){
		os << n1.pointers[i] << "|";
	}
	os<<" ]}";
	return os;
}


std::ostream &operator<<(std::ostream &os, const Record &record) {
    os << "id: " << record.id << std::endl;
    for(auto a:record.app_name){os << a;}
    os << std::endl;
    os << "size_bytes: " << record.size_bytes << std::endl;
    os << "price: " << record.price << std::endl;
    os << "rating_count_tot: " << record.rating_count_tot << std::endl;
    os << "user_rating: " << record.user_rating << std::endl;
    for(auto a:record.cont_rating){os << a;}
    os << std::endl;
    for(auto a:record.prime_genre){os <<a;}
    os << std::endl;
    return os;
}


std::ostream& operator<<(std::ostream &os,Bucket b1){
 
	os << "[ ";
	for(int i=0;i<M;i++){
		os << b1.records[i] << "|"; 
	}
	os << "sz: "<<b1.size << " nxt: " << b1.next << "* ]";
	return os;
}


