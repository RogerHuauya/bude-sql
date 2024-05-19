// // #include "usefull_structures.hpp"
// #include <array>


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

// std::ostream& operator<<(std::ostream& os,Record r1){
// 	os <<"( code:"<< r1.code << " nombre:";
// 	for(auto a:r1.nombre){os << a;}
// 	os << " promedio:" << r1.promedio << " alto:" << r1.alto <<")";
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


