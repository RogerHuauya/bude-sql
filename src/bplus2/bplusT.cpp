#include "bplus.hpp"
//#include <cstddef>
#include <fstream>
#include <ios>


template<typename T>
Bplus<T>::Bplus(string _csv,Index _pk){
	csv = _csv;
	pk = _pk;


	if(pk == RecordAux::ID){ 
		index = "id_index.dat";
		data = "id_data.dat";
	}else if(pk == RecordAux::APP_NAME){
		index = "app_name_index.dat";
		data = "app_name_data.dat";
	}else if(pk == RecordAux::SIZE_BYTES){
		index = "size_bytes_index.dat";
		data = "size_bytes_data.dat";
	}else if(pk == RecordAux::PRICE){
		index = "price_index.dat";
		data = "price_data.dat";
	}else if(pk == RecordAux::RATING_COUNT_TOT){
		index = "rating_count_tot_index.dat";
		data = "rating_count_tot_data.dat";
	}else if(pk == RecordAux::USER_RATING){
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	}else if(pk == RecordAux::CONT_RATING){
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	}else if(pk == RecordAux::PRIME_GENRE){
		index = "prime_genre_index.dat";
		data = "prime_genre_data.dat";
	}
	

	
	ifstream datafile(data,ios::binary);
	ifstream indexfile(index,ios::binary);
	if (!datafile.is_open()){
		indexfile.close();
		ofstream index_file(index,ios::binary);
		ofstream data_file(data,ios::binary);
		
		Nodo<T> _root;
		_root.leaf = true;
		_root.size = 0;
		_root.pointers[0] = 0; // representa al primer bucket
		Bucket tmp_bucket;
		tmp_bucket.next = -1; tmp_bucket.size = 0;
		root_pos = 4;

		index_file.write(reinterpret_cast<char*>(&root_pos),sizeof(int));
		index_file.write(reinterpret_cast<char*>(&_root),sizeof(Nodo<T>));
		data_file.write(reinterpret_cast<char*>(&tmp_bucket),sizeof(Bucket));

		index_file.close();
		data_file.close();
	} 
	datafile.close(); indexfile.close();
	insert_csv(csv);

}


template<typename T>
Bplus<T>::Bplus(Index _pk){
	pk = _pk;
	if(pk == RecordAux::ID){ 
		index = "id_index.dat";
		data = "id_data.dat";
	}else if(pk == RecordAux::APP_NAME){
		index = "app_name_index.dat";
		data = "app_name_data.dat";
	}else if(pk == RecordAux::SIZE_BYTES){
		index = "size_bytes_index.dat";
		data = "size_bytes_data.dat";
	}else if(pk == RecordAux::PRICE){
		index = "price_index.dat";
		data = "price_data.dat";
	}else if(pk == RecordAux::RATING_COUNT_TOT){
		index = "rating_count_tot_index.dat";
		data = "rating_count_tot_data.dat";
	}else if(pk == RecordAux::USER_RATING){
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	}else if(pk == RecordAux::CONT_RATING){
		index = "user_rating_index.dat";
		data = "user_rating_data.dat";
	}else if(pk == RecordAux::PRIME_GENRE){
		index = "prime_genre_index.dat";
		data = "prime_genre_data.dat";
	}
	

	
	ifstream datafile(data,ios::binary);
	ifstream indexfile(index,ios::binary);
	if (!datafile.is_open()){
		indexfile.close();
		ofstream index_file(index,ios::binary);
		ofstream data_file(data,ios::binary);
		
		Nodo<T> _root;
		_root.leaf = true;
		_root.size = 0;
		_root.pointers[0] = 0; // representa al primer bucket
		Bucket tmp_bucket;
		tmp_bucket.next = -1; tmp_bucket.size = 0;
		root_pos = 4;

		index_file.write(reinterpret_cast<char*>(&root_pos),sizeof(int));
		index_file.write(reinterpret_cast<char*>(&_root),sizeof(Nodo<T>));
		data_file.write(reinterpret_cast<char*>(&tmp_bucket),sizeof(Bucket));

		index_file.close();
		data_file.close();
	} 
	datafile.close(); indexfile.close();

}


template<typename T>
void Bplus<T>::printIndex(){
	Nodo<T> nodo;
	ifstream indexfile(index,ios::binary|ios::in);
	indexfile.seekg(sizeof(int));
	while(indexfile.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>))){
		cout << int(indexfile.tellg()) - sizeof(Nodo<T>) << "  ";
		cout << nodo << endl;
	}
	indexfile.close();
}
template<typename T>
void Bplus<T>::printData(){
	Bucket bucket;
	ifstream datafile(data,ios::binary|ios::in);
	while(datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket))){
		cout << int(datafile.tellg()) - sizeof(Bucket) << "  ";
		cout << bucket << endl;
	}
	datafile.close();
}
template<typename T>
T Bplus<T>::stoT(string value){
	if(is_integral_v<T>){return stoi(value);}
	else if(is_floating_point_v<T>){return stof(value);}
	else if(value == "True" || value == "TRUE" || value == "true"){
		return true;
	}
	else if(value == "False" || value == "FALSE" || value == "false"){
		return false;
	}
	return T();
}
template<>
string Bplus<string>::stoT(string value){
	return value;
}
template<>
char* Bplus<char*>::stoT(string value){
	char* tmp = value.data();
	return tmp;
}
template<typename T>
Record Bplus<T>::Bin2Record(ifstream &file){
	char a='a';
	string _id;
	string app_name;
	string size_bytes;
	string price;
	string rating_count_tot;
	string user_rating;
	string cont_rating;
	string prime_genre;
	string removed;

	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout <<a;
		if(a != ','){ _id.push_back(a); }
	}
	a = 'a';
			
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;
		if(a != ','){ app_name.push_back(a); }
	}
	a = 'a';

			
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ size_bytes.push_back(a); }
	}
	a = 'a';

	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ price.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ rating_count_tot.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ user_rating.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ cont_rating.push_back(a); }
	}
	a = 'a';
	while (a != ',') {
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		if(a != ','){ prime_genre.push_back(a); }
	}
	a = 'a';

	while (a != '\n') {
		if (file.eof()){ break; }
		file.read(reinterpret_cast<char*>(&a),sizeof(a));
		cout << a;

		removed.push_back(a);
	}
	
	unsigned int id = stoi(_id);
	unsigned int _size_bytes = stoi(size_bytes);
	unsigned int _rating_count_tot = stoi(rating_count_tot);
	float _price = stof(price);
	bool _removed;


    array<char, 256> _app_name;
    array<char, 256> _cont_rating;
    array<char, 256> _prime_genre;

	for(int i=0;i<256;i++){
		_app_name[i] = app_name[i];
		_cont_rating[i] = cont_rating[i];
		_prime_genre[i]  = prime_genre[i];
	}

	if (removed == "True" || removed == "true" || removed == "TRUE"){_removed = true;}
	else {removed = false;}

	return Record(id,_app_name,_size_bytes,_price,_rating_count_tot,_cont_rating,_prime_genre,_removed);

}


template<typename T>
bool Bplus<T>::add(Record record){
	fstream indexfile(index,ios::binary|ios::in|ios::out);
	fstream datafile(data,ios::binary|ios::in|ios::out);
	RecordAux recordaux(record,pk);
	
	insert_root(recordaux,indexfile,datafile,root_pos);
	
	indexfile.close(); datafile.close();
	return true;
}

template<typename T>
void Bplus<T>::insert_root(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<T> nodo;
	pair<pair<bool,bool>,pair<T,int>> request;request.first.first = false;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	

	if(nodo.size == 0){
		root_0(recordaux,index,data,pos);
	} else if(nodo.size != 0){
		request = insert_nodo(recordaux,index,data,pos);
	}


	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));


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
			Nodo<T> new_root;
			new_root.index[0] = request.second.first;
			new_root.pointers[1] = request.second.second;
			new_root.pointers[0] = pos;
			new_root.leaf = false;
			new_root.size += 1;
			index.seekg(0,ios::end);
			root_pos = index.tellg();
			index.write(reinterpret_cast<char*>(&new_root),sizeof(Nodo<T>));
            Nodo<T> tmp; 
			index.read(reinterpret_cast<char*>(&tmp), sizeof(Nodo<T>));
			tmp.leaf = nodo.leaf;
			index.seekp(request.second.second);
			index.write(reinterpret_cast<char*>(&tmp), sizeof(Nodo<T>));
        }

	}
	if (nodo.size == M) {
	 	split_root(index,pos);	
	}

}
template<typename T>
void Bplus<T>::root_0(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<T> nodo;
	Bucket bucket,bucket_prev;
	T key = stoT(recordaux());
	index.seekg(pos);
	data.seekg(ios::beg);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
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
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

    data.seekg(sizeof(Bucket));
	data.read(reinterpret_cast<char*>(&bucket),sizeof(bucket));
}


template <typename T>
pair<pair<bool,bool>,pair<T,int>> Bplus<T>::insert_nodo(RecordAux recordaux,fstream &index,fstream &data,int pos){
	Nodo<T> nodo;
	T key = stoT(recordaux());
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	pair<pair<bool,bool>,pair<T,int>> response,request;

	int next_pos;
	for(int i=nodo.size-1;i>-1;i--){
		if(key < nodo.index[i]){
			next_pos = nodo.pointers[i];
		}else if(key > nodo.index[i]){
			next_pos = nodo.pointers[i+1];
			break;
		}
	}


	if (!nodo.leaf){
		request = insert_nodo(recordaux,index,data,next_pos);
	} else {
		request = insert_bucket(recordaux,data,next_pos);
	}


	if(request.first.first == true){
		pair<T,int> index_pointer;
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
		index.write(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
	}

	response.first.second = false;
	if(nodo.size == M){
		pair<T,int> index_pointer = split_nodo(index,pos);
		response.first.first = true; response.second = index_pointer;
		if (pos == root_pos){ 
			response.first.second = true; 
		}
	} else { 
		response.first.first = false;
	}

	return  response;
}


template<typename T>
pair<pair<bool,bool>,pair<T,int>> Bplus<T>::insert_bucket(RecordAux recordaux,fstream &data,int pos_bucket){
	Bucket bucket;
	pair<pair<bool,bool>,pair<T,int>> response; 
	response.first.first = false;
	data.seekg(pos_bucket);
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));

	RecordAux tmp; tmp.attr = pk;


	if(bucket.size == 0){
		bucket.records[0] = recordaux.record;
	} else {
		for(int i=bucket.size-1;i>-1;i--){
			tmp.record = bucket.records[i];
      		
			if(stoT(recordaux()) > stoT(tmp())){
				bucket.records[i+1] = recordaux.record;
				break;
			} else if(stoT(recordaux()) == stoT(tmp())){
				break;
			} else {
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
template<typename T>
pair<T,int> Bplus<T>::split_bucket(fstream &data,int pos_bucket){
	Bucket bucket;
	Bucket sibling;
	pair<T,int> response;
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
	T index2insert = stoT(recordaux());

	response.first = index2insert;
	response.second = siblingpointer;
	return response;
}

template<typename T>
pair<T,int> Bplus<T>::split_nodo(fstream &index,int pos){
	pair<T,int> response;
	Nodo<T> nodo;
	
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
	
	int middle_index = nodo.size / 2;
	T middle_value = nodo.index[middle_index];
	Nodo<T> sibling;

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
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	index.seekp(0,ios::end);
	int ptr_index = index.tellp();
	index.write(reinterpret_cast<char*>(&sibling),sizeof(sibling));
	
	response.first = middle_value;
	response.second = ptr_index;

	return response;
}

template <typename T>
void Bplus<T>::split_root(fstream &index,int pos){
	Nodo<T> nodo;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	int middle_index = nodo.size / 2;
	T middle_value = nodo.index[middle_index];
		
	Nodo<T> sibling, new_root;
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
	index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	index.seekp(ios::end);
	int new_root_pos = index.tellp(); //indice del nuevo root
	index.write(reinterpret_cast<char*>(&new_root),sizeof(Nodo<T>));
		
	root_pos = new_root_pos;
	index.seekp(0); //insertar nuevo root
	index.write(reinterpret_cast<char*>(&new_root_pos),sizeof(int));		
}

template <typename T>
void Bplus<T>::insert_csv(string csv){
	ifstream file(csv,ios::binary);
	Record record;
	file.seekg(0,ios::end);
	int end = file.tellg();
	file.seekg(0);


	while(true){
		cout << file.tellg() << endl;
		record = Bin2Record(file);
		cout << record << endl;
		add(record);
		if (file.tellg() == end){break;}

	}

	file.close();
}
template <typename T>
vector<Record> Bplus<T>::search(T key){
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
		if(stoT(tmp()) == key){
			record = tmp.record;
			break;
		}
	}

	indexfile.close();datafile.close();
	vector<Record> response ={record};
	return response;
}
template <typename T>
int Bplus<T>::search_from_nodo(T key,int pos,fstream &index){
	Nodo<T> nodo;
	int next_pos , response;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	

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
template <typename T>
vector<Record> Bplus<T>::rangeSearch(T bkey,T ekey){
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
		if(stoT(tmp()) >= bkey){response.push_back(tmp.record);}
	}
	next_bucket = bucket.next;

	while(next_bucket != -1){
		datafile.seekg(next_bucket);
		datafile.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
		for(int i=0;i<bucket.size;i++){
			tmp.record = bucket.records[i];
			if(stoT(tmp()) > ekey){break;}
			else {response.push_back(bucket.records[i]);}
		}
		next_bucket = bucket.next;
	}
	
	return response;
}



template<typename T> void Bplus<T>::remove(T key){
	fstream indexfile(index,ios::binary|ios::in|ios::out);
	fstream datafile(data,ios::binary|ios::in|ios::out);
	
	cout << key << endl;
	remove_root(key,indexfile,datafile);
	
	indexfile.close();datafile.close();
	
}

template<typename T> void Bplus<T>::remove_root(T key,fstream &index,fstream &data){
	Nodo<T> nodo; index.seekg(root_pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	
	if(nodo.size == 0){return;}
	cout << "entrando al remove nodo \n";
	remove_nodo(key,index,data,root_pos,root_pos);
	cout << "saliendo del remove nodo \n";
	//aqui va a haber logica extra
}


template<typename T> bool Bplus<T>::remove_nodo(T key,fstream &index,fstream &data,int pos,int prev_pos){
	Nodo<T> nodo;
	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	//el bool de la funcion indica si se debe hacer un merge entre los hijos
	bool response = false;
	int next_pos;
	int next_pos_index;
	for(int i=nodo.size-1;i>-1;i--){
		if(key < nodo.index[i]){
			next_pos = nodo.pointers[i];
			next_pos_index = i;
		}
		else if(key >= nodo.index[i]){
			next_pos = nodo.pointers[i+1];
			next_pos_index = i+1;
			break;
		}
	}
	
	T request; //key deleted

	bool b;
	if(next_pos_index == 0){b=true;}


	if(nodo.leaf){
		request = remove_bucket(key,index,data,next_pos,pos,0);
	} else {
		response = remove_nodo(key,index,data,next_pos,pos);
	}

	cout << "RESPONSE AAAAAAAAAAAAAAAAAAAAAAA  " << boolalpha<< response << endl;

	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	

	//1. reagrupar si un nodo hijo esta en size 0 o cerca de ahi

	//2.si el valor que elimiaste se encuentra en el nodo tienes que reemplazarlo con su sucesor 
	//que esta dentro de un nodo hoja

	if(nodo.size == 0){
		//mandar senal para el merge entre el nodo su sibling y padre          
		//return (true) el padre se encargara del merge
		return true;
	}

	//encontrar sucesor si el nodo no esta vacio y el valor eliminado se encientra en el nodo
	bool is_in = false;
	int del_index = -1;
	for(int i=0;i<nodo.size;i++){
		if(nodo.index[i] == key){
			del_index = i;
			is_in = true; 
			break;
		}
	}
	if(is_in){
		//funcion para eliminar y reemplazar por el sucesor
		nodo.index[del_index] = nodo_index_successor(nodo.pointers[del_index+1],index,data);
		index.seekp(pos);index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	}

	index.seekg(pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	

	if(response){
		//funcionar para hacer el merge entre nodo padre y hermando
		cout << "HOLA QUIEN SOY NOSE SE ME OLVIDO \n"; 
		Nodo<T> normal,down;
		index.seekg(nodo.pointers[next_pos_index]);
		index.read(reinterpret_cast<char*>(&down), sizeof(Nodo<T>));
		index.seekg(nodo.pointers[next_pos_index-1]);
		index.read(reinterpret_cast<char*>(&normal), sizeof(Nodo<T>));

		// cout << nodo << endl;
		// cout << down << endl;
		// cout << normal << endl;

		if(next_pos_index == 0){
			merge_nodo_2siblings_right2left(pos,next_pos_index,next_pos_index+1,index);
		} else {
			cout << "por aqui\n";
			merge_nodo_2siblings_left2right(pos,next_pos_index,next_pos_index-1,index);
		}
	}		


	return false;
}


template<typename T> T Bplus<T>::remove_bucket(T key,fstream &index,fstream &data,int pos,int prev_pos, bool isidx0){
	Bucket bucket;
	RecordAux tmp; tmp.attr = pk; 

	data.seekg(pos);
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	
	int record_index;


	int i_pos = -1;
	for(int i=bucket.size-1;i>-1;i--){
		tmp.record = bucket.records[i];
		if(key == stoT(tmp())){
			i_pos = i;
			break;
		}
	}
	if(i_pos == -1){ return T(); } // el valor no esta en el bucket
	
	for(int i=i_pos;i<bucket.size;i++){
		bucket.records[i] = bucket.records[i+1];
	}
	bucket.size -= 1; // valor eliminado

	data.seekp(pos);
	data.write(reinterpret_cast<char*>(&bucket), sizeof(Bucket));

	if(i_pos == 0 && !isidx0){
		RecordAux recordaux;recordaux.attr=pk;recordaux.record=bucket.records[0];
		T new_key = stoT(recordaux()); // nuevo valor
		replace_node_index(key,new_key,prev_pos,index,data);//reemplazar el valor eliminado en el nodo
	}



	if(bucket.size < M/2 ){
		manage_underflow_bucket(pos,prev_pos,index,data);//si el nodo tiene menos indices de lo esperado
		// sino muere ahi
	}


	return key;
}


template<typename T>
void Bplus<T>::replace_node_index(T oldkey,T new_key,int node_pos,fstream &index,fstream &data){
	Nodo<T> nodo;
	index.seekg(node_pos);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	for(int i=0;i<nodo.size;i++){
		if(nodo.index[i] == oldkey){
			nodo.index[i] = new_key;
			break;
		}
	}
	index.seekp(node_pos);
	index.write(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
}


template<typename T>
void Bplus<T>::manage_underflow_bucket(int pos_bucket,int pos_nodo,fstream &index,fstream &data){
	Nodo<T> nodo; index.seekg(pos_nodo);
	index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	cout << "MANAGE UNDEFLOW BUCKET \n\n";	
	int bucket_index;
	for(int i=0;i<nodo.size+1;i++){
		if(nodo.pointers[i] == pos_bucket){
			bucket_index = i; break;
		}
	}
	cout << nodo << endl;

	if(bucket_index == 0){
		Bucket right;data.seekg(nodo.pointers[bucket_index+1]);
		data.read(reinterpret_cast<char*>(&right),sizeof(Bucket));
		

		if(right.size > M/2){ 
			cout << "not underflow \n";
			//borrow keys from right
			borrow_keys_right(pos_bucket,nodo.pointers[bucket_index+1],pos_nodo,index,data);
		} else {
			// merge
			merge_right(pos_bucket,nodo.pointers[bucket_index+1],pos_nodo,index,data);
		}
	
	} else if(bucket_index == nodo.size){ //recuerda que los nodos tienen M+1 indices
		Bucket left;data.seekg(nodo.pointers[bucket_index-1]);
		data.read(reinterpret_cast<char*>(&left),sizeof(Bucket));

		cout << "index nodo = size" << endl;

		if(left.size > M/2){
			cout << "not underflow " << endl;
			borrow_keys_left(pos_bucket,nodo.pointers[bucket_index-1],pos_nodo,index,data);
		} else {
			//merge
			cout << "UNDERFLOW MERGE LEFT" << endl;
			merge_left(pos_bucket,nodo.pointers[bucket_index-1], pos_nodo,index,data);
		}

	} else {
		Bucket right,left;
		data.seekg(nodo.pointers[bucket_index+1]);
		data.read(reinterpret_cast<char*>(&right),sizeof(Bucket));

		if(right.size > M/2){
			// borrow from right
			borrow_keys_right(pos_bucket,nodo.pointers[bucket_index+1],pos_nodo,index,data);
		} else if(left.size > M/2){
			// borrow from left
			borrow_keys_left(pos_bucket,nodo.pointers[bucket_index-1],pos_nodo,index,data);
		} else {
			merge_right(pos_bucket,nodo.pointers[bucket_index+1],pos_nodo,index,data);
		}
	}
}


template<typename T>
void Bplus<T>::borrow_keys_left(int pos,int pos_left,int pos_nodo,fstream &index,fstream &data){
	Bucket bucket,left_bucket;
	//llamas al bucket y al bucket de la izquierda
	data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
	data.seekg(pos_left);data.read(reinterpret_cast<char*>(&left_bucket), sizeof(Bucket));

	RecordAux tmp; tmp.attr = pk;tmp.record = bucket.records[0];
	T oldkey_nodo = stoT(tmp());

	//agarras la mitad de las llaves del bucket izquierdo y las insertas en el bucket current
		//crear una funcion que elimine un valor del array records y te retorne el valor eliminado
		//crear una funcion que inserte y acomode un valor que se ingrese como parametro
	cout << bucket.size << " left size " << left_bucket.size << endl;
	int cant_keys_2move = left_bucket.size - M/2;
	cout << "cant_keys_2move " << cant_keys_2move << endl;

	for(int i=0;i<cant_keys_2move;i++){
		Record tmp = aux_delete_bucket_record(pos_left,true,data);
		data.seekg(pos_left);data.read(reinterpret_cast<char*>(&left_bucket),sizeof(Bucket));
		aux_insert_bucket_record(pos,true,tmp,data);
		data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	}

	//actualizas la key del nodo con la nueva generada al llamar a las otras llaves
	//necesitas la llave pasada y la nueva
	tmp.record = bucket.records[0];
	T newkey_nodo = stoT(tmp());

	replace_node_index(oldkey_nodo,newkey_nodo,pos_nodo,index,data);
}

template<typename T>
void Bplus<T>::borrow_keys_right(int pos,int pos_right,int pos_nodo,fstream &index,fstream &data){
	Bucket bucket,right_bucket;
	//llamas al bucket y al bucket de la izquierda
	data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
	data.seekg(pos_right);data.read(reinterpret_cast<char*>(&right_bucket), sizeof(Bucket));

	RecordAux tmp; tmp.attr = pk;tmp.record = bucket.records[0];
	T oldkey_nodo = stoT(tmp());

	//agarras la mitad de las llaves del bucket izquierdo y las insertas en el bucket current
		//crear una funcion que elimine un valor del array records y te retorne el valor eliminado
		//crear una funcion que inserte y acomode un valor que se ingrese como parametro
	int cant_keys_2move = right_bucket.size - M/2;
	cout << "cant keys to move "<< cant_keys_2move << endl;
	for(int i=0;i<cant_keys_2move;i++){

		Record tmp = aux_delete_bucket_record(pos_right,false,data);

		
		data.seekg(pos_right);data.read(reinterpret_cast<char*>(&right_bucket),sizeof(Bucket));
		
		aux_insert_bucket_record(pos,true,tmp,data);
		
		data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	}
	//actualizas la key del nodo con la nueva generada al llamar a las otras llaves
	//necesitas la llave pasada y la nueva
	tmp.record = right_bucket.records[0];
	T newkey_nodo = stoT(tmp());
	replace_node_index(oldkey_nodo,newkey_nodo,pos_nodo,index,data);
}

template<typename T>
void Bplus<T>::merge_left(int pos,int pos_left,int pos_nodo,fstream &index,fstream &data){
	Nodo<T> nodo;index.seekg(pos_nodo);index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	Bucket bucket;data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	Bucket l_bucket;data.seekg(pos_left);data.read(reinterpret_cast<char*>(&l_bucket),sizeof(Bucket));


	bool bucket_size = false;
	T oldkey; RecordAux recordaux;recordaux.attr=pk;
	cout << bucket.size << endl;


	if(l_bucket.size==1){
		bucket_size = true;
		l_bucket.next=bucket.next;
	}else {
		recordaux.record = bucket.records[0];
		oldkey = stoT(recordaux());
	


		for(int i=l_bucket.size-1,j=0;i>=0;i--,j++){
			bucket.records[j] = l_bucket.records[i];
			bucket.size+=1;
			l_bucket.size-=1;
		}
	}
	data.seekp(pos);data.write(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	data.seekp(pos_left);data.write(reinterpret_cast<char*>(&l_bucket),sizeof(Bucket));

	if(bucket_size){
		nodo.size=0;
	}else {
		recordaux.record = bucket.records[0];

		replace_node_index(oldkey,stoT(recordaux()),pos_nodo,index, data);
		index.read(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
	}
	// l_bucket.size-=1; // reduce el size del nodo, este merge esta disenado para el indice -1 del nodo
	cout <<"MERGE LEFT GOKUUUU AAA " <<  nodo << endl;	
	index.seekp(pos_nodo);index.write(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
}

template<typename T>
void Bplus<T>::merge_right(int pos,int pos_right,int pos_nodo,fstream &index,fstream &data){
	//cargas el nodo,bucket,bucket derecho
	Nodo<T> nodo;index.seekg(pos_nodo);index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>)); 
	Bucket bucket,r_bucket;
	data.seekg(pos);data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	data.seekg(pos_right);data.read(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
	
	RecordAux recordaux;recordaux.attr=pk;recordaux.record=bucket.records[0];
	T bucket_index_key = stoT(recordaux());

	//insertas los valores del bucket derecho al current
	for(int i=0,j=bucket.size;i<r_bucket.size;i++,j++){
		bucket.records[j] = r_bucket.records[i];
		bucket.size+=1;r_bucket.size-=1;
	}

	//corres la posicion de los indices y punteros del nodo en 1, contando desde el bucket derecho
	for(int i=0;i<nodo.size-1;i++){
		if(nodo.index[i] >= bucket_index_key){
			nodo.index[i] = nodo.index[i+1];
			nodo.pointers[i+1] = nodo.pointers[i+2];
		}
	}

	index.seekp(pos_nodo);index.write(reinterpret_cast<char*>(&nodo), sizeof(Nodo<T>));
	data.seekp(pos);data.write(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
	data.seekp(pos_right);data.write(reinterpret_cast<char*>(&r_bucket),sizeof(Bucket));
}

template<typename T>
Record Bplus<T>::aux_delete_bucket_record(int pos_bucket,bool left,fstream &data){
	Bucket bucket;
	data.seekg(pos_bucket); data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	Record response;

	if(left){
		response = bucket.records[bucket.size-1];
	}else {
		response = bucket.records[0];
		for(int i=0;i<bucket.size-1;i++){
			bucket.records[i] = bucket.records[i+1];
		}
	}
	bucket.size-=1;
	data.seekp(pos_bucket);data.write(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
	return response;
}

template<typename T>
void Bplus<T>::aux_insert_bucket_record(int pos_bucket,bool left,Record record,fstream &data){
	Bucket bucket;
	data.seekg(pos_bucket);data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	RecordAux recordaux; recordaux.attr =pk;recordaux.record = record;
	RecordAux tmp; tmp.attr = pk;

	if(bucket.size==0){
		bucket.records[0] = record;
	}else {

		for(int i=bucket.size-1;i>-1;i--){
			tmp.record = bucket.records[i];
			
			if(stoT(recordaux()) > stoT(tmp())){
				bucket.records[i+1] = recordaux.record;
				break;
			} else if(stoT(recordaux()) == stoT(tmp())){
				break;
			} else {
				bucket.records[i+1] = bucket.records[i]; 
				if(i == 0){
					bucket.records[i] = recordaux.record;
				}
			}
		}
	}

	bucket.size+=1;
	data.seekp(pos_bucket);data.write(reinterpret_cast<char*>(&bucket), sizeof(Bucket));
}

template<typename T>
T Bplus<T>::nodo_index_successor(int nodo_sibling,fstream &index,fstream &data){
	Nodo<T> nodo;
	index.seekg(nodo_sibling);index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));

	while(!nodo.leaf){
		index.seekg(nodo.pointers[0]);
		index.read(reinterpret_cast<char*>(&nodo),sizeof(Nodo<T>));
	}
	data.seekg(nodo.pointers[0]);
	Bucket bucket;
	data.read(reinterpret_cast<char*>(&bucket),sizeof(Bucket));
	Record record = bucket.records[0];

	RecordAux recordaux; recordaux.attr=pk;recordaux.record = record;
	
	return stoT(recordaux());
}

template<typename T>
void Bplus<T>::merge_nodo_2siblings_left2right(int pos_nodo,int index_nodo_l0,int index_nodo_l,fstream &index){
	Nodo<T> father,sibling0,sibling1;
	index.seekg(pos_nodo);index.read(reinterpret_cast<char*>(&father),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l0]);index.read(reinterpret_cast<char*>(&sibling0),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l]);index.read(reinterpret_cast<char*>(&sibling1),sizeof(Nodo<T>));

	//de nodo derecha a nodo izquierdo

	cout << "FATHER " << father << endl;
	cout << "sibling0" << sibling0 << endl;
	cout << "sibling1" << sibling1 << endl;
	
	cout << sibling1 << " --- " << M/2 << endl;
	if(sibling1.size < M/2){
		int len_nodo_normal = sibling1.size;
		for(int i=0,j=father.size-1;i<len_nodo_normal;i++,j--){
			father.index[j+1] = father.index[j];
			father.pointers[j+2] = father.pointers[j+1];
			father.size+=1;
			if(j==0){
				father.pointers[j] = father.pointers[j+1];
				break;
			} 
		}
		cout << len_nodo_normal << endl;
		for(int i=0;i<len_nodo_normal;i++){
			father.index[i] = sibling1.index[i];
			father.pointers[i] = sibling1.pointers[i];
		}
		father.pointers[len_nodo_normal] = sibling1.pointers[len_nodo_normal];
		father.pointers[father.size] = sibling0.pointers[0];
	}else {
		cout << "sweet marie" << endl;
		sibling0.index[0] = father.index[father.size-1];
		father.index[0] = sibling1.index[sibling1.size-1];
		sibling0.pointers[1] = sibling0.pointers[0];
		sibling0.pointers[0] = sibling1.pointers[sibling1.size];
		sibling1.size -=1;
		sibling0.size +=1;
 	}

	cout << "FATHER " << father << endl;
	cout << "sibling0" << sibling0 << endl;
	cout << "sibling1" << sibling1 << endl;
	
 	index.seekp(pos_nodo);index.write(reinterpret_cast<char*>(&father),sizeof(Nodo<T>));
	index.seekp(father.pointers[index_nodo_l]);index.write(reinterpret_cast<char*>(&sibling1),sizeof(Nodo<T>));
	index.seekp(father.pointers[index_nodo_l0]);index.write(reinterpret_cast<char*>(&sibling0),sizeof(Nodo<T>));
}

template<typename T>
void Bplus<T>::merge_nodo_2siblings_right2left(int pos_nodo,int index_nodo_l0,int index_nodo_l,fstream &index){
	Nodo<T> father,sibling0,sibling1;
	index.seekg(pos_nodo);index.read(reinterpret_cast<char*>(&father),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l0]);index.read(reinterpret_cast<char*>(&sibling0),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l]);index.read(reinterpret_cast<char*>(&sibling1),sizeof(Nodo<T>));

	if(sibling1 < M/2) {
		father.pointers[0] = sibling0.pointers[sibling0.size];
		// father.
	}else {
 
	}

	index.seekg(pos_nodo);index.read(reinterpret_cast<char*>(&father),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l0]);index.read(reinterpret_cast<char*>(&sibling0),sizeof(Nodo<T>));
	index.seekg(father.pointers[index_nodo_l]);index.read(reinterpret_cast<char*>(&sibling1),sizeof(Nodo<T>));

}

