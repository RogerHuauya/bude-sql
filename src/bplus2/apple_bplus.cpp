// #include "apple.h"

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

// vector<Record> get_random_records(int n) {
//     vector<Record> random_records;
//     for (int i = 0; i < n; ++i) {
//         Record record;
//         record.id = i;
//         record.app_name = {"app_name %d"};
//         record.size_bytes = 1000 * i;
//         record.price = 0.99 * i;
//         record.rating_count_tot = 100 * i;
//         record.user_rating = UserRating_5;
//         record.cont_rating = { "4+"};
//         record.prime_genre = { "Games"};
//         random_records.push_back(record);
//     }
//     return random_records;
// }




// template <typename T>
// std::ostream& operator<<(std::ostream &os,Nodo<T> n1){
// 	os << "{";
// 	os << n1.size;
// 	os << " [ ";
// 	for (int i=0;i<M;i++){
// 		os << n1.index[i] << "|";
// 	}
// 	os << " ] [";
// 	for (int i=0;i<M+1;i++){
// 		os << n1.pointers[i] << "|";
// 	}
// 	os<<" ]}";
// 	return os;
// }

// template <>
// std::ostream& operator<<(std::ostream &os,Nodo<std::array<char, S>> n1){
// 	os << "{ ";
// 	os << std::boolalpha << n1.leaf << " ";
// 	os << n1.size;
// 	os << " [ ";
// 	for (int i=0;i<M;i++){
// 		for(auto a:n1.index[i]){
// 			os << a;
// 		}
// 		os << " | ";
// 	}
// 	os << " ] [";
// 	for (int i=0;i<M+1;i++){
// 		os << n1.pointers[i] << "|";
// 	}
// 	os<<" ]}";
// 	return os;
// }


// std::ostream& operator<<(std::ostream &os,Bucket b1){
 
// 	os << "[ ";
// 	for(int i=0;i<M;i++){
// 		os << b1.records[i] << "|"; 
// 	}
// 	os << "sz: "<<b1.size << " nxt: " << b1.next << "* ]";
// 	return os;
// }


