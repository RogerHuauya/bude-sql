#include "bplus.hpp"
#include <array>
#include <iostream>
#include "apple.h"


BplusTxt::BplusTxt(string _csv,Index _pk){
	csv = _csv;
	pk = _pk;
	if (pk == RecordAux::ID) {
		index = "id_index.dat";
		data = "id_data.dat";
	} else if (pk == RecordAux::TRACK_NAME) {
		index = "track_name_index.dat";
		data = "track_name_data.dat";
	} else if (pk == RecordAux::SIZE_BYTES) {
		index = "size_bytes_index.dat";
		data = "size_bytes_data.dat";
	} else if (pk == RecordAux::CURRENCY) {
		index = "currency_index.dat";
		data = "currency_data.dat";
	} else if (pk == RecordAux::PRICE) {
		index = "price_index.dat";
		data = "price_data.dat";
	} else if (pk == RecordAux::RATING_COUNT_TOT) {
		index = "rating_count_tot_index.dat";
		data = "rating_count_tot_data.dat";
	} else if (pk == RecordAux::RATING_COUNT_VER) {
		index = "rating_count_ver_index.dat";
		data = "rating_count_ver_data.dat";
	} else if (pk == RecordAux::USER_RATING) {
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	} else if (pk == RecordAux::USER_RATING_VER) {
		index = "user_rating_ver_index.dat";
		data = "user_rating_ver_data.dat";
	} else if (pk == RecordAux::VER) {
		index = "ver_index.dat";
		data = "ver_data.dat";
	} else if (pk == RecordAux::CONT_RATING) {
		index = "cont_rating_index.dat";
		data = "cont_rating_data.dat";
	} else if (pk == RecordAux::PRIME_GENRE) {
		index = "prime_genre_index.dat";
		data = "prime_genre_data.dat";
	} else if (pk == RecordAux::SUP_DEVICES_NUM) {
		index = "sup_devices_num_index.dat";
		data = "sup_devices_num_data.dat";
	} else if (pk == RecordAux::IPADSC_URLS_NUM) {
		index = "ipadsc_urls_num_index.dat";
		data = "ipadsc_urls_num_data.dat";
	} else if (pk == RecordAux::LANG_NUM) {
		index = "lang_num_index.dat";
		data = "lang_num_data.dat";
	} else if (pk == RecordAux::VPP_LIC) {
		index = "vpp_lic_index.dat";
		data = "vpp_lic_data.dat";
	}

	
	ifstream datafile(data,ios::binary);
	ifstream indexfile(index,ios::binary);
	if (!datafile.is_open()){
		indexfile.close();
		ofstream index_file(index,ios::binary);
		ofstream data_file(data,ios::binary);
		
		Nodo<Type> _root;
		_root.leaf = true;
		_root.size = 0;
		_root.pointers[0] = 0; // representa al primer bucket
		Bucket tmp_bucket;
		tmp_bucket.next = -1; tmp_bucket.size = 0;
		root_pos = 4;

		index_file.write(reinterpret_cast<char*>(&root_pos),sizeof(int));
		index_file.write(reinterpret_cast<char*>(&_root),sizeof(Nodo<Type>));
		data_file.write(reinterpret_cast<char*>(&tmp_bucket),sizeof(Bucket));

		index_file.close();
		data_file.close();
	} 
	datafile.close(); indexfile.close();
	insert_csv(csv);

}


BplusTxt::BplusTxt(Index _pk){
	pk = _pk;
	if (pk == RecordAux::ID) {
		index = "id_index.dat";
		data = "id_data.dat";
	} else if (pk == RecordAux::TRACK_NAME) {
		index = "track_name_index.dat";
		data = "track_name_data.dat";
	} else if (pk == RecordAux::SIZE_BYTES) {
		index = "size_bytes_index.dat";
		data = "size_bytes_data.dat";
	} else if (pk == RecordAux::CURRENCY) {
		index = "currency_index.dat";
		data = "currency_data.dat";
	} else if (pk == RecordAux::PRICE) {
		index = "price_index.dat";
		data = "price_data.dat";
	} else if (pk == RecordAux::RATING_COUNT_TOT) {
		index = "rating_count_tot_index.dat";
		data = "rating_count_tot_data.dat";
	} else if (pk == RecordAux::RATING_COUNT_VER) {
		index = "rating_count_ver_index.dat";
		data = "rating_count_ver_data.dat";
	} else if (pk == RecordAux::USER_RATING) {
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	} else if (pk == RecordAux::USER_RATING_VER) {
		index = "user_rating_ver_index.dat";
		data = "user_rating_ver_data.dat";
	} else if (pk == RecordAux::VER) {
		index = "ver_index.dat";
		data = "ver_data.dat";
	} else if (pk == RecordAux::CONT_RATING) {
		index = "cont_rating_index.dat";
		data = "cont_rating_data.dat";
	} else if (pk == RecordAux::PRIME_GENRE) {
		index = "prime_genre_index.dat";
		data = "prime_genre_data.dat";
	} else if (pk == RecordAux::SUP_DEVICES_NUM) {
		index = "sup_devices_num_index.dat";
		data = "sup_devices_num_data.dat";
	} else if (pk == RecordAux::IPADSC_URLS_NUM) {
		index = "ipadsc_urls_num_index.dat";
		data = "ipadsc_urls_num_data.dat";
	} else if (pk == RecordAux::LANG_NUM) {
		index = "lang_num_index.dat";
		data = "lang_num_data.dat";
	} else if (pk == RecordAux::VPP_LIC) {
		index = "vpp_lic_index.dat";
		data = "vpp_lic_data.dat";
	}
	

	ifstream datafile(data,ios::binary);
	ifstream indexfile(index,ios::binary);
	if (!datafile.is_open()){
		indexfile.close();
		ofstream index_file(index,ios::binary);
		ofstream data_file(data,ios::binary);
		
		Nodo<Type> _root;
		_root.leaf = true;
		_root.size = 0;
		_root.pointers[0] = 0; // representa al primer bucket
		Bucket tmp_bucket;
		tmp_bucket.next = -1; tmp_bucket.size = 0;
		root_pos = 4;

		index_file.write(reinterpret_cast<char*>(&root_pos),sizeof(int));
		index_file.write(reinterpret_cast<char*>(&_root),sizeof(Nodo<Type>));
		data_file.write(reinterpret_cast<char*>(&tmp_bucket),sizeof(Bucket));

		index_file.close();
		data_file.close();
	} 
	datafile.close(); indexfile.close();

}


void BplusTxt::printIndex(){
	Nodo<Type> nodo;
	ifstream indexfile(index,ios::binary|ios::in);
	indexfile.seekg(sizeof(int));
	while(indexfile.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>))){
		cout << int(indexfile.tellg()) - sizeof(Nodo<Type>) << "  ";
		cout << nodo << endl;
	}
	indexfile.close();
}

void BplusTxt::printData(){
	Bucket bucket;
	ifstream datafile(data,ios::binary|ios::in);
	while(datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket))){
		cout << int(datafile.tellg()) - sizeof(Bucket) << "  ";
		cout << bucket << endl;
	}
	datafile.close();
}

Record BplusTxt::Bin2Record(ifstream &file){
	char a='a';
	string _id;
	string _track_name;
	string _size_bytes;
	string _currency;
	string _price;
	string _rating_count_tot;
	string _rating_count_ver;
	string _user_rating;
	string _user_rating_ver;
	string _ver;
	string _cont_rating;
	string _prime_genre;
	string _sup_devices_num;
	string _ipadsc_urls_num;
	string _lang_num;
	string _vpp_lic;

	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		if(a != ','){ _id.push_back(a); }
	}
	a = 'a';

	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;
		if(a != ','){ _track_name.push_back(a); }
	}
	a = 'a';

			
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _size_bytes.push_back(a); }
	}
	a = 'a';

	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _currency.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _price.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _rating_count_tot.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _rating_count_ver.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _user_rating.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout <<a;
		if(a != ','){ _user_rating_ver.push_back(a); }
	}
	a = 'a';
			
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;
		if(a != ','){ _ver.push_back(a); }
	}
	a = 'a';

			
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _cont_rating.push_back(a); }
	}
	a = 'a';

	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _prime_genre.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _sup_devices_num.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _ipadsc_urls_num.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;

		if(a != ','){ _lang_num.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;
		if(a != ','){ _vpp_lic.push_back(a); }
	}
	a = 'a';

	while (a != '\n') {
		if (file.eof()){ break; }
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		// cout << a;
		
	}
	
	unsigned int id = std::stoi(_id);
	unsigned int size_bytes = std::stoi(_size_bytes);
	float price = std::stof(_price);
	unsigned int rating_count_tot = std::stoi(_rating_count_tot);
	unsigned int rating_count_ver = std::stoi(_rating_count_ver);
	float user_rating = std::stof(_user_rating);
	float user_rating_ver = std::stof(_user_rating_ver);
	unsigned int sup_devices_num = std::stoi(_sup_devices_num);
	unsigned int ipadsc_urls_num = std::stoi(_ipadsc_urls_num);
	unsigned int lang_num = std::stoi(_lang_num);
	int vpp_lic = std::stoi(_vpp_lic);

	// Convert string arrays to std::array<char, 256>
	std::array<char, 256> track_name, currency, ver, cont_rating, prime_genre;

	for(int i=0;i<_track_name.size();i++){
		track_name[i] = _track_name[i];
	}
	for(int i=_track_name.size();i<256;i++){
		track_name[i] = '\0';
	}

	for(int i=0;i<_currency.size();i++){
		currency[i] = _currency[i];
	}
	for(int i=_currency.size();i<256;i++){
		currency[i] = '\0';
	}

	for(int i=0;i<_ver.size();i++){
		ver[i] = _ver[i];
	}
	for(int i=_ver.size();i<256;i++){
		ver[i] = '\0';
	}

	for(int i=0;i<_cont_rating.size();i++){
		cont_rating[i] = _cont_rating[i];
	}
	for(int i=_cont_rating.size();i<256;i++){
		cont_rating[i] = '\0';
	}

	for(int i=0;i<_prime_genre.size();i++){
		prime_genre[i] = _prime_genre[i];
	}
	for(int i=_prime_genre.size();i<256;i++){
		prime_genre[i] = '\0';
	}

	return Record(id, track_name, size_bytes, currency, price, rating_count_tot, rating_count_ver,
				user_rating, user_rating_ver, ver, cont_rating, prime_genre,
				sup_devices_num, ipadsc_urls_num, lang_num, vpp_lic);

}


bool BplusTxt::add(Record record){
	fstream indexfile(index,ios::binary|ios::in|ios::out);
	fstream datafile(data,ios::binary|ios::in|ios::out);
	RecordAux recordaux(record,pk);
	
	insert_root(recordaux,indexfile,datafile,root_pos);
	
	indexfile.close(); datafile.close();
	return true;
}

void BplusTxt::insert_root(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<Type> nodo;
	pair<pair<bool,bool>,pair<BplusTxt::Type,int>> request;request.first.first = false;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));
	
	if(nodo.size == 0){root_0(recordaux,index,data,pos);} 
	else if(nodo.size != 0){request = insert_nodo(recordaux,index,data,pos);}

	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<Type>));

	if(request.first.first == true) {
		if(request.first.second == false){
			for(int i=nodo.size-1;i>-1;i--){
				if(nodo.index[i] < request.second.first){
					nodo.index[i+1] = request.second.first;
					nodo.pointers[i+2] = request.second.second;
				} else {
					nodo.index[i+1] = nodo.index[i];
					nodo.pointers[i+2] = nodo.pointers[i+1];
				}
	 	 	}
	 	 	nodo.size += 1;
		} else if (request.first.second == true){

			Nodo<Type> new_root;
			new_root.index[0] = request.second.first;

			new_root.pointers[1] = request.second.second;
			new_root.pointers[0] = pos;
			new_root.leaf = false;
			new_root.size += 1;
			index.seekg(0,ios::end);
			root_pos = index.tellg();
			index.write(reinterpret_cast<char*>(&new_root),sizeof(Nodo<Type>));
			index.seekg(request.second.second);
			Nodo<Type> tmp; 
			index.read(reinterpret_cast<char*>(&tmp), sizeof(Nodo<Type>));
			tmp.leaf = nodo.leaf;
			index.seekp(request.second.second);
			index.write(reinterpret_cast<char*>(&tmp), sizeof(Nodo<Type>));
		}
	}
	if (nodo.size == M) {
	 	split_root(index,pos);	
	}
}

void BplusTxt::root_0(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<Type> nodo;
	Bucket bucket,bucket_prev;
	Type key = recordaux(pk);
	index.seekg(pos);
	data.seekg(ios::beg);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));

	
	nodo.index[0] = key;

	nodo.size = 1;
	nodo.pointers[0] = 0;
	nodo.leaf = true;
	
	bucket.records[0] = recordaux.record;
	bucket.size = 1;
	bucket_prev.next = int(sizeof(Bucket));
	bucket.next = -1;

	data.seekp(0);
	data.write(reinterpret_cast<char*>(&bucket_prev),sizeof(Bucket));
	nodo.pointers[1] = data.tellp();
	data.write(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	index.seekp(pos);
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));

    index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));
}

pair<pair<bool,bool>,pair<BplusTxt::Type,int>> BplusTxt::insert_nodo(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<Type> nodo;
	Type key = recordaux(pk);
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));
	pair<pair<bool,bool>,pair<BplusTxt::Type,int>> response,request;

	int next_pos;
	for(int i=nodo.size-1;i>-1;i--){
		if(key < nodo.index[i]){
			next_pos = nodo.pointers[i];
		}else if(key > nodo.index[i]){
			next_pos = nodo.pointers[i+1];
			break;
		}
	}

	if (!nodo.leaf){ request = insert_nodo(recordaux,index,data,next_pos);
	} else {request = insert_bucket(recordaux,data,next_pos);}


	if(request.first.first == true){
		pair<Type,int> index_pointer;
		index_pointer.first = request.second.first;index_pointer.second = request.second.second;

		for(int i=nodo.size-1;i>-1;i--){
			if(nodo.index[i] < index_pointer.first){
				nodo.index[i+1] = index_pointer.first;
				nodo.pointers[i+2] = index_pointer.second;
				nodo.size +=1;
				break;
			} else{
				nodo.index[i+1] = nodo.index[i];
				nodo.pointers[i+2] = nodo.pointers[i+1];
			}
			if(nodo.index[i] > index_pointer.first && i==0){
				nodo.index[i] = index_pointer.first;
				nodo.pointers[i+1] = index_pointer.second;
				nodo.size +=1;
			}
		}
		index.seekg(pos);
		index.write(reinterpret_cast<char*>(&nodo), sizeof(Nodo<Type>));
	}

	response.first.second = false;
	if(nodo.size == M){

		pair<Type,int> index_pointer = split_nodo(index,pos);
		response.first.first = true; response.second = index_pointer;
		if (pos == root_pos){ 
			response.first.second = true; 
		}
	} else { 
		response.first.first = false;
		
	}
	return  response;
}


pair<pair<bool,bool>,pair<std::array<char,S>,int>> BplusTxt::insert_bucket(RecordAux recordaux,fstream &data,int pos_bucket){
	Bucket bucket;
	pair<pair<bool,bool>,pair<Type,int>> response; 
	response.first.first = false;
	data.seekg(pos_bucket);
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));

	RecordAux tmp; tmp.attr = pk;

	if(bucket.size == 0){
		bucket.records[0] = recordaux.record;
	} else {
		for(int i=bucket.size-1;i>-1;i--){
			tmp.record = bucket.records[i];

			if(recordaux(pk) > tmp(pk)){
				bucket.records[i+1] = recordaux.record;
				break;
			} else if(recordaux(pk) == tmp(pk)){
				cout << "Indice ocupado"<<endl;
				break;
			}
			else {
				bucket.records[i+1] = bucket.records[i];
                if(i == 0){
                    bucket.records[i] = recordaux.record;
                }
			}
		}

	}
	bucket.size += 1; 
	data.seekp(pos_bucket);
	data.write(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	if (bucket.size == M){
		response.first.first = true;
		response.second = split_bucket(data,pos_bucket);
	}
	return response;
}


pair<std::array<char,S>,int> BplusTxt::split_bucket(fstream &data,int pos_bucket){
	Bucket bucket;
	Bucket sibling;
	pair<Type,int> response;
	data.seekg(pos_bucket);
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	int midindex = bucket.size/2; //sube y se va con la mitad derecha nueva
	for(int i=midindex,j=0;i<M;i++,j++){
		sibling.records[j] = bucket.records[i];
		sibling.size += 1;
	}
	bucket.size = midindex; //reducir el size nuevo;
	data.seekp(0,ios::end);
	int bucket_next = bucket.next;
	int siblingpointer = data.tellp();
	sibling.next = bucket_next;
	bucket.next = siblingpointer;
	data.write(reinterpret_cast<char*>(&sibling),sizeof(Bucket));

	data.seekp(pos_bucket);
	data.write(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	
	RecordAux recordaux(bucket.records[midindex],pk);
	Type index2insert = recordaux(pk);
	
	response.first = index2insert;
	response.second = siblingpointer;
	return response;
}


pair<std::array<char,S>,int> BplusTxt::split_nodo(fstream &index,int pos){
	pair<Type,int> response;
	Nodo<Type> nodo;
	
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<Type>));
	
	int middle_index = nodo.size / 2;
	Type middle_value = nodo.index[middle_index];
	Nodo<Type> sibling;

	for(int i = middle_index + 1,j=0;i < nodo.size;i++,j++){
		sibling.index[j] = nodo.index[i];
		sibling.pointers[j] = nodo.pointers[i];
		sibling.size += 1;
		if(i == nodo.size-1){
			sibling.pointers[j+1] = nodo.pointers[i+1];
		}

	}
	nodo.size = nodo.size /2;
	sibling.leaf = nodo.leaf;
	index.seekg(pos);
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));

	index.seekp(0,ios::end);
	int ptr_index = index.tellp();
	index.write(reinterpret_cast<char*>(&sibling),sizeof(sibling));
	
	response.first = middle_value;
	response.second = ptr_index;

	return response;
}

void BplusTxt::split_root(fstream &index,int pos){
	Nodo<Type> nodo;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));

	int middle_index = nodo.size / 2;
	Type middle_value = nodo.index[middle_index];
		
	Nodo<Type> sibling, new_root;
	for(int i = middle_index + 1,j=0;i < nodo.size;i++,j++){
		sibling.index[j] = nodo.index[i];
		sibling.pointers[j] = nodo.pointers[i];
		if(i == nodo.size){
			sibling.pointers[j+1] = nodo.pointers[i+1];
		}
	}
	nodo.leaf = sibling.leaf = true;
	new_root.leaf = false;

	index.seekp(ios::end);
	int ptr_index = index.tellp();
	index.write(reinterpret_cast<char*>(&sibling),sizeof(sibling));
	
	nodo.size = nodo.size/2;
	new_root.index[0] = middle_value;
	new_root.size += 1;
	new_root.pointers[0] = root_pos;
	new_root.pointers[1] = ptr_index;

	index.seekg(pos);
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));

	index.seekp(ios::end);
	int new_root_pos = index.tellp(); //indice del nuevo root
	index.write(reinterpret_cast<char*>(&new_root),sizeof(Nodo<Type>));
		
	root_pos = new_root_pos;
	index.seekp(0); //insertar nuevo root
	index.write(reinterpret_cast<char*>(&new_root_pos),sizeof(int));		
}


void BplusTxt::insert_csv(string csv){
	ifstream file(csv,ios::binary);
	Record record;
	file.seekg(0,ios::end);
	int end = file.tellg();
	file.seekg(0);


	char a = 'a';
	while(a != '\n'){
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
	}
	int contador = 0;
	while(true){
		contador +=1;
		if(contador==K){break;}
		// cout << file.tellg() << endl;
		record = Bin2Record(file);
		// cout << record << endl;
		add(record);
		if (file.tellg() == end){break;}
	}

	file.close();
}


vector<Record> BplusTxt::search(Type key){
	fstream indexfile(index,ios::binary|ios::in|ios::out);
	fstream datafile(data,ios::binary|ios::in|ios::out);
	int bucket_pos  = search_from_nodo(key,root_pos,indexfile);

	Bucket bucket;
	datafile.seekg(bucket_pos);
	datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	
	Record record;
	RecordAux tmp; tmp.attr = pk;


	for(int i=0;i<bucket.size;i++){
		tmp.record = bucket.records[i];
		if(tmp(pk) == key){
			record = tmp.record;
			break;
		}
	}

	indexfile.close();datafile.close();
	vector<Record> response ={record};
	return response;
}

int BplusTxt::search_from_nodo(Type key,int pos,fstream &index){
	Nodo<Type> nodo;
	int next_pos , response;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<Type>));

	if (!nodo.leaf){
		for(int i=nodo.size-1;i>-1;i--){
			if(key < nodo.index[i]){
				next_pos = nodo.pointers[i];
			} else if(key > nodo.index[i]){
				next_pos = nodo.pointers[i+1];
				break;
			}
		}
		response = search_from_nodo(key,next_pos,index);
	} else {
		for(int i=nodo.size-1;i>-1;i--){
			if(key == nodo.index[i]){
				next_pos = nodo.pointers[i+1];
				break;
			}
		}
		response = next_pos;
	}

	return response;
} 


vector<Record> BplusTxt::rangeSearch(Type bkey,Type ekey){
	fstream indexfile(index,ios::binary|ios::in|ios::out);
	fstream datafile(data,ios::binary|ios::in|ios::out);
	int b_bucket_pos = search_from_nodo(bkey,root_pos,indexfile);
	Bucket bucket;
	vector<Record> response;
	int next_bucket;


	RecordAux tmp; tmp.attr = pk;
	datafile.seekg(b_bucket_pos);
	datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	for(int i=0;i<bucket.size;i++){
		tmp.record = bucket.records[i];
		if(tmp(pk) >= bkey){response.push_back(tmp.record);}
	}
	next_bucket = bucket.next;

	while(next_bucket != -1){
		datafile.seekg(next_bucket);
		datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
		for(int i=0;i<bucket.size;i++){
			tmp.record = bucket.records[i];
			if(tmp(pk) > ekey){break;}
			else {response.push_back(bucket.records[i]);}
		}
		next_bucket = bucket.next;
	}
	
	return response;
}




