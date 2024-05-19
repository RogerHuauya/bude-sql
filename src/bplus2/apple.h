#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <array>
#include <iomanip>

using namespace std;

const int S = 256;
const int M = 3;


struct Record {
    int id;
    std::array<char, 256> track_name;
    int size_bytes;
    std::array<char, 256> currency;
    float price;
    int rating_count_tot;
    int rating_count_ver;
    float user_rating;
    float user_rating_ver;
    std::array<char, 256> ver;
    std::array<char, 256> cont_rating;
    std::array<char, 256> prime_genre;
    int sup_devices_num;
    int ipadSc_urls_num;
    int lang_num;
    int vpp_lic;

    Record() {}

    Record(int _id, 
           std::array<char, 256> _track_name, 
           int _size_bytes, 
           std::array<char, 256> _currency, 
           float _price, 
           int _rating_count_tot, 
           int _rating_count_ver, 
           float _user_rating, 
           float _user_rating_ver, 
           std::array<char, 256> _ver, 
           std::array<char, 256> _cont_rating, 
           std::array<char, 256> _prime_genre, 
           int _sup_devices_num, 
           int _ipadSc_urls_num, 
           int _lang_num, 
           int _vpp_lic) 
    : id(_id), 
      track_name(_track_name), 
      size_bytes(_size_bytes), 
      currency(_currency), 
      price(_price), 
      rating_count_tot(_rating_count_tot), 
      rating_count_ver(_rating_count_ver), 
      user_rating(_user_rating), 
      user_rating_ver(_user_rating_ver), 
      ver(_ver), 
      cont_rating(_cont_rating), 
      prime_genre(_prime_genre), 
      sup_devices_num(_sup_devices_num), 
      ipadSc_urls_num(_ipadSc_urls_num), 
      lang_num(_lang_num), 
      vpp_lic(_vpp_lic) {}
};



// struct RecordAux {
//   Record record;
//   enum Attribute { ID,APP_NAME, SIZE_BYTES, PRICE, RATING_COUNT_TOT,USER_RATING,CONT_RATING,PRIME_GENRE,REMOVED };
//   RecordAux::Attribute attr;

// 	RecordAux(){}
// 	RecordAux(Record _record,RecordAux::Attribute _attr){
// 		record = _record;attr = _attr;
// 	}
// 	std::string operator()(){
//   	switch (attr) {
// 		case ID:
// 				return std::to_string(record.id);
//         case SIZE_BYTES:
// 				return std::to_string(record.size_bytes);
// 		case PRICE:
// 				return std::to_string(record.price);
//         case RATING_COUNT_TOT:
// 				return std::to_string(record.rating_count_tot);
// 		case USER_RATING:
// 				return std::to_string(record.user_rating);
//         default:
// 				std::cerr << "Atributo no válido" << std::endl;
//       	exit(EXIT_FAILURE);
//     }
//  	}
// 	std::array<char,256> operator()(Attribute attr){
// 		switch (attr) {
//     	case APP_NAME:
//             return record.app_name;
//     	case CONT_RATING:
//             return record.cont_rating;
//         case PRIME_GENRE:
//             return record.prime_genre;
//       default:
// 				std::cerr << "Atributo no válido" << std::endl;
//         exit(EXIT_FAILURE);
//     }
// 	}
// };



struct RecordAux {
    Record record;
    enum Attribute { ID, TRACK_NAME, SIZE_BYTES, CURRENCY, PRICE, RATING_COUNT_TOT, RATING_COUNT_VER, USER_RATING, USER_RATING_VER, VER, CONT_RATING, PRIME_GENRE, SUP_DEVICES_NUM, IPADSC_URLS_NUM, LANG_NUM, VPP_LIC, REMOVED };
    Attribute attr;

    RecordAux() {}
    RecordAux(Record _record, Attribute _attr) : record(_record), attr(_attr) {}

    std::string operator()() {
        switch (attr) {
            case ID:
                return std::to_string(record.id);
            case SIZE_BYTES:
                return std::to_string(record.size_bytes);
            case PRICE:
                return std::to_string(record.price);
            case RATING_COUNT_TOT:
                return std::to_string(record.rating_count_tot);
            case RATING_COUNT_VER:
                return std::to_string(record.rating_count_ver);
            case USER_RATING:
                return std::to_string(record.user_rating);
            case USER_RATING_VER:
                return std::to_string(record.user_rating_ver);
            case SUP_DEVICES_NUM:
                return std::to_string(record.sup_devices_num);
            case IPADSC_URLS_NUM:
                return std::to_string(record.ipadSc_urls_num);
            case LANG_NUM:
                return std::to_string(record.lang_num);
            case VPP_LIC:
                return std::to_string(record.vpp_lic);
            default:
                std::cerr << "Atributo numérico no válido" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    std::array<char, 256> operator()(Attribute attr) {
        switch (attr) {
            case TRACK_NAME:
                return record.track_name;
            case CURRENCY:
                return record.currency;
            case VER:
                return record.ver;
            case CONT_RATING:
                return record.cont_rating;
            case PRIME_GENRE:
                return record.prime_genre;
            default:
                std::cerr << "Atributo de cadena no válido" << std::endl;
                exit(EXIT_FAILURE);
        }
    }
};




// Overloading the ostream operator for the Record struct
std::ostream& operator<<(std::ostream& os, const Record& record) {
    // os << "Record {" << std::endl;
    os << "  ID: " << record.id ;
    os << "  Track Name: " << record.track_name.data() ;
    os << "  Size Bytes: " << record.size_bytes ;
    os << "  Currency: " << record.currency.data() ;
    os << "  Price: $" << std::fixed << std::setprecision(2) << record.price ;
    os << "  Rating Count Total: " << record.rating_count_tot ;
    os << "  Rating Count Ver: " << record.rating_count_ver ;
    os << "  User Rating: " << std::fixed << std::setprecision(1) << record.user_rating ;
    os << "  User Rating Ver: " << std::fixed << std::setprecision(1) << record.user_rating_ver ;
    os << "  Version: " << record.ver.data() ;
    os << "  Content Rating: " << record.cont_rating.data() ;
    os << "  Prime Genre: " << record.prime_genre.data() ;
    os << "  Supported Devices Number: " << record.sup_devices_num ;
    os << "  iPad Screenshots URLs Number: " << record.ipadSc_urls_num ;
    os << "  Languages Number: " << record.lang_num ;
    os << "  VPP License: " << record.vpp_lic ;
    os << "}";
    return os;
}



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


// std::ostream &operator<<(std::ostream &os, const Record &record) {
//     os << "id: " << record.id << std::endl;
//     for(auto a:record.app_name){os << a;}
//     os << std::endl;
//     os << "size_bytes: " << record.size_bytes << std::endl;
//     os << "price: " << record.price << std::endl;
//     os << "rating_count_tot: " << record.rating_count_tot << std::endl;
//     os << "user_rating: " << record.user_rating << std::endl;
//     for(auto a:record.cont_rating){os << a;}
//     os << std::endl;
//     for(auto a:record.prime_genre){os <<a;}
//     os << std::endl;
//     return os;
// }


std::ostream& operator<<(std::ostream &os,Bucket b1){
 
	os << "[ ";
	for(int i=0;i<M;i++){
		os << b1.records[i] << "|"; 
	}
	os << "sz: "<<b1.size << " nxt: " << b1.next << "* ]";
	return os;
}


