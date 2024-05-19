// #include <iostream>
// #include <array>
// #include <cstring>
// #include <string>

// const int S = 20;
// const int M = 3;


// struct Record {
// 	int code;
// 	std::array<char,S> nombre;
//     float promedio;
//     bool alto;
// 	Record(){}
//   	Record(int _code,std::array<char, 20> _nombre,float _promedio,bool _alto){
//       	code = _code;
//       	nombre =  _nombre;
//       	promedio = _promedio;
//        	alto = _alto;
//   	}
// };



// struct RecordAux {
//     Record record;
//     enum Attribute { Code, Promedio, Nombre, Alto };
//     RecordAux::Attribute attr;

// 	RecordAux(){}
// 	RecordAux(Record _record,RecordAux::Attribute _attr){
// 		record = _record;attr = _attr;
// 	}
// 	std::string operator()(){
//   	switch (attr) {
// 			case Code:
// 				return std::to_string(record.code);
//       case Promedio:
// 				return std::to_string(record.promedio);
//       case Alto:
// 				return std::to_string(record.alto);
//       default:
// 				std::cerr << "Atributo no válido" << std::endl;
//       	exit(EXIT_FAILURE);
//     }
//  	}
// 	std::array<char,S> operator()(Attribute attr){
// 		switch (attr) {
//     	case Nombre:
// 				return record.nombre;
//       default:
// 				std::cerr << "Atributo no válido" << std::endl;
//         exit(EXIT_FAILURE);
//     }
// 	}
// };



// template<typename T>
// struct Nodo{
// 	T index[M];
// 	int pointers[M+1];
// 	size_t size = 0;
// 	bool leaf = true;
// };

// template<>
// struct Nodo<std::array<char,S>>{
// 	std::array<char,S> index[M];
// 	int pointers[M+1];
// 	size_t size=0;
// 	bool leaf=true;
// };

// struct Bucket{
// 	Record records[M];
// 	int next=-1;
// 	int size=0;
// };
