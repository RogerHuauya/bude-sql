#include <array>
#include <fstream>
#include <vector>
#include "apple.h"
using namespace std;

#pragma once


template<typename T>
class Bplus{
public:
	typedef RecordAux::Attribute Index;
private:
	void insert_csv(string csv);
	T stoT(string value);
	Record Bin2Record(ifstream &file);
private:
	void insert_root(RecordAux record,fstream &index,fstream &data,int pos);
	void root_0(RecordAux recordaux,fstream &index,fstream &data,int pos);
	void split_root(fstream& index,int pos);
	pair<pair<bool,bool>,pair<T,int>> insert_nodo(RecordAux recordaux,fstream &index,fstream &data,int pos);
	pair<T,int> split_nodo(fstream &index,int pos);
	pair<pair<bool,bool>,pair<T,int>> insert_bucket(RecordAux record,fstream &data,int pos_bucket);	
	pair<T,int> split_bucket(fstream &data,int pos_bucket);
	int search_from_nodo(T key,int pos,fstream &index);
	

	void remove_root(T key,fstream &index,fstream &data);
	bool remove_nodo(T key,fstream &index,fstream &data,int pos,int prev_pos);
	
	T remove_bucket(T key,fstream &index,fstream &data,int pos,int prev_pos,bool isidx0);
	void replace_node_index(T oldkey,T new_key,int node_pos,fstream &index,fstream &data);
	void manage_underflow_bucket(int pos_bucket,int pos_nodo,fstream &index,fstream &data);
	void borrow_keys_left(int pos,int pos_left,int pos_nodo,fstream &index,fstream &data);
	void borrow_keys_right(int pos,int pos_right,int pos_nodo,fstream &index,fstream &data);
	void merge_right(int pos,int pos_right,int pos_nodo,fstream &index,fstream &data);
	void merge_left(int pos,int pos_left,int pos_nodo, fstream &index,fstream &data);

	Record aux_delete_bucket_record(int pos_bucket,bool left,fstream &data);
	void aux_insert_bucket_record(int pos_bucket,bool left,Record record,fstream &data);
	T nodo_index_successor(int nodo_sibling,fstream &index,fstream &data);
	void merge_nodo_2siblings_left2right(int pos_nodo,int index_nodo_l0,int index_nodo_l,fstream &index);
	void merge_nodo_2siblings_right2left(int pos_nodo,int index_nodo_l0,int index_nodo_l,fstream &index);
public:
	Bplus<T>(string _csv,Index _pk);
	Bplus<T>(Index _pk);
	bool add(Record record);
	void remove(T key);
	vector<Record> search(T key);
	vector<Record> rangeSearch(T bkey,T ekey);
	void printIndex();
	void printData();

private:
	string data;
	string index;
	int root_pos;
	Index pk;
	string csv;
};



class BplusTxt{
public:
	typedef RecordAux::Attribute Index;
	typedef std::array<char,S> Type;
private:
	void insert_csv(string csv);
	Record Bin2Record(ifstream &file);
private:
	void insert_root(RecordAux record,fstream &index,fstream &data,int pos);
	void root_0(RecordAux recordaux,fstream &index,fstream &data,int pos);
	void split_root(fstream& index,int pos);
	pair<pair<bool,bool>,pair<Type,int>> insert_nodo(RecordAux recordaux,fstream &index,fstream &data,int pos);
	pair<Type,int> split_nodo(fstream &index,int pos);
	pair<pair<bool,bool>,pair<Type,int>> insert_bucket(RecordAux record,fstream &data,int pos_bucket);	
	pair<Type,int> split_bucket(fstream &data,int pos_bucket);
	int search_from_nodo(Type key,int pos,fstream &index);
public:
	BplusTxt(string _csv,Index _pk);
	BplusTxt(Index _pk);
	bool add(Record record);
	bool remove(Type key);
	vector<Record> search(Type key);
	vector<Record> rangeSearch(Type bkey,Type ekey);
	void printIndex();
	void printData();

private:
	string data;
	string index;
	int root_pos;
	Index pk;
	string csv;
};
