#include "apple.h"
#include "bplus.hpp"
#include "bplusT.cpp"
#include "bplustxt.cpp"
#include <array>
using namespace std;
#include <vector>

#include <string>





void test_text_variables(){
	BplusTxt b2("Updated_AppleStore.csv",RecordAux::TRACK_NAME);

	cout << endl <<endl;
	cout << "=================INDEX===================\n";
	b2.printIndex();
	cout << "=================DATA====================\n";
	b2.printData();


	///////////////////////////
	cout << endl << endl;
	std::array<char,256> key;
	string test = "Facebook"; // los caracteres no inicializados deben ser de tipo \0
	for(int i=0;i<test.size();i++){key[i] = test[i];}
	for(int i=test.size();i<256;i++){key[i] = '\0';} //hace esto es obligatorio
	//////////////////////////
	cout << endl <<endl << endl;

	vector a = b2.search(key);
	cout << a[0];
	
}


void test_notText_variables(){
	Bplus<int> b1("Updated_AppleStore.csv",RecordAux::ID);

	cout << endl <<endl;
	cout << "=================INDEX===================\n";
	b1.printIndex();
	cout << "=================DATA====================\n";
	b1.printData();

	cout << endl <<endl << endl;

	vector a = b1.search(284882215);
	cout << a[0];
}



int main(){

	test_text_variables();
	

	return 0;
}
