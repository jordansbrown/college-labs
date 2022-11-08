//Jordan Brown
//Lab 8: Hash Tables
//March 19 2021

//APRIL 20 2021

#include "hash.hpp"
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <sstream>
#include <cstdlib>
#include <string>

using namespace std;

//Set_Up() to set up the table before using it.
string Hash::Set_Up(size_t table_size, const std::string &fxn, const std::string &collision)
{
	if(Keys.size() != 0) {
		return "Hash table already set up";
	}

	if(!(table_size)) {
		return  "Bad table size"; 
	}

	if(fxn != "Last7" && fxn != "XOR") {
		return "Bad hash function";
	}

	if(collision != "Linear" && collision != "Double") {
		return "Bad collision resolution strategy";
	}
	
	Keys.resize(table_size);
	Vals.resize(table_size);
	Nkeys = 0;
					
	if(fxn == "XOR") {
		Fxn = 'X';
	}
	if(fxn == "Last7") {
		Fxn = 'L';
	}	

	if(collision == "Linear") {
		Coll = 'L';
	}
	if(collision == "Double") {
		Coll = 'D';
	}

			
	(void) table_size;
	(void) fxn;
	(void) collision;
	return "";	
}

//adds the given key/val pair to the hash table.
string Hash::Add(const string &key, const string &val)
{
	if(Keys.size() <= 0) {
		return "Hash table not set up";
	}
	
	if(key == "") {
		return "Empty key";
	}

	if(val == "") {
		return "Empty val";
	}

	if(Nkeys >= Keys.size()) {
		return "Hash table full";
	}
			
	for(size_t i = 0; i < Keys.size(); i++) {
		if(key == Keys[i]) {
			return "Key already in the table";
		}
	}

	istringstream ss;
	string  Last7, First7;

	if(key.size() > 7) {
		Last7 = key.substr(key.size() - 7, key.size()); 
		ss.clear();
		ss.str(Last7);
	} else {
		First7 = key;
		ss.clear();
		ss.str(First7);
	}

	int num;
	ss >> hex >> num;
	num %= Keys.size();
	
	int rem = key.size() % 7, XOR = 0;				
	vector <string> keysize; 
	
	for(size_t i = 0; i < (key.size() / 7); i++) {
		keysize.push_back(key.substr(i * 7, 7));
	}

	if(rem != 0) {
		keysize.push_back(key.substr(7 * (key.size() / 7), key.size()));
	}
	
	vector <int> temp;
	temp.resize(keysize.size());
	
	ss.str("");
	for(size_t i = 0; i < keysize.size(); i++) {
		ss.clear();
		ss.str(keysize[i]);
		ss >> hex >> temp[i];
	}

	for(size_t i = 0; i < temp.size(); i++) {
		XOR ^= temp[i];
	}

	XOR = XOR % Keys.size();
	
	int ex = XOR;
	int last = num;  
	
if(Fxn == 'L') {
	if(Coll == 'L') {
		for(size_t i = 0; i < Keys.size(); i++) {
			if(Keys[ (last + i) % Keys.size() ] == "") {
				Keys[ (last + i) % Keys.size() ] = key;
				Vals[ (last + i) % Keys.size() ] = val;
				Nkeys++;
				return "";
			}	
		}
	}

	num = 0;
	if(Coll == 'D') {
		for(size_t i = 0; i < Keys.size(); i++){
			num = (ex % Keys.size());
			if(num == 0) {
				num = 1;
			}
			if(Keys[ (last + i * (num)) % Keys.size()] == "") {
				Keys[ (last + i * (num)) % Keys.size()] = key; 
				Vals[ (last + i * (num)) % Keys.size()] = val;
				Nkeys++;
				return "";
			}
		}	
	}
}

if(Fxn == 'X') {
	if(Coll == 'L') {
		for(size_t i = 0; i < Keys.size(); i++) {
			if(Keys[ (ex + i) % Keys.size() ] == "") {
				Keys[ (ex + i) % Keys.size() ] = key;	
				Vals[ (ex + i) % Keys.size() ] = val;
				Nkeys++;
				return "";
			}
		}
	}

	if(Coll == 'D') {
		num = 0;
		for(size_t i = 0; i < Keys.size(); i++) {
			num = (last % Keys.size());
			if(num == 0) {
				num = 1;
			}
			if(Keys[ (ex + i * (num)) % Keys.size()] == "") {
				Keys[ (ex + i * (num)) % Keys.size()] = key;
				Vals[ (ex + i * (num)) % Keys.size()] = val;
				Nkeys++;
				return "";
			}
		}
	}
}

	(void) key;
	(void) val;
	return "";	
}

//Find() returns the val associated with the given key
string Hash::Find(const string &key)
{
	istringstream ss;
	string  Last7, First7;
	if(key.size() > 7) {
		Last7 = key.substr(key.size() - 7, key.size());
		ss.clear();
		ss.str(Last7);
	} else {
		First7 = key;
		ss.clear();
		ss.str(First7);
	}
	
	int num;
	ss >> hex >> num;
	num %= Keys.size();
		
	
	int rem = key.size() % 7, XOR = 0;				
	vector <string> keysize; 
	
	for(size_t i = 0; i < (key.size() / 7); i++) {
		keysize.push_back(key.substr(i * 7, 7));
	}

	if(rem != 0) {
		keysize.push_back(key.substr(7 * (key.size() / 7), key.size()));
	}
	
	vector <int> temp;
	temp.resize(keysize.size());
	
	ss.str("");
	for(size_t i = 0; i < keysize.size(); i++) {
		ss.clear();
		ss.str(keysize[i]);
		ss >> hex >> temp[i];
	}

	for(size_t i = 0; i < temp.size(); i++) {
		XOR ^= temp[i];
	}

	XOR = XOR % Keys.size();
	
	int ex = XOR;
	int last = num;  
	
	if(Fxn == 'L') {
		if(Coll == 'L') {
			for(size_t i = 0; i < Keys.size(); i++) {
				if(Keys[ (last + i) % Keys.size() ] == key) {
					return Vals[ (last + i) % Keys.size() ];
				}
				Nprobes++;
			}
		}
		num = 0;
		if(Coll == 'D') {
			for(size_t i = 0; i < Keys.size(); i++) {
				int num = (ex % Keys.size());
				if(num == 0) {
					num = 1;
				}
				if(Keys[ (last + i * (num)) % Keys.size()] == key) {
					return Vals[ (last + i * (num)) % Keys.size()];
				}
				Nprobes++;
			}
		}
	}

	if(Fxn == 'X') {
		if(Coll == 'L') {
			for(size_t i = 0; i < Keys.size(); i++) {
				if(Keys[ (ex + i) % Keys.size() ] == key) {
					return Vals[ (ex + i) % Keys.size() ];
				}
				Nprobes++;
			}
		}			
		if(Coll == 'D') {
			for(size_t i = 0; i < Keys.size(); i++) {
				int num = (last % Keys.size());
				if(num == 0) {
					num = 1;
				}
				if(Keys[ (ex + i * (num)) % Keys.size()] == key) {
					return Vals[ (ex + i * (num)) % Keys.size()] ;
				}
				Nprobes++;
			}
		}
	}
	(void) key;
	return "";
}

// Print() prints all non-empty slots in the hash table, one per line.
void Hash::Print() const
{
	for(size_t i = 0; i < Keys.size(); i++) {
		if(Keys[i] != "") {
			printf("%5lu %s %s\n", i, Keys[i].c_str(), Vals[i].c_str());
		}
	}
}

// Total_Probes() should traverse the hash table, and for every key, 
// caculcate how many probes it takes find that key.
size_t Hash::Total_Probes()
{
	if(Keys.size() == 0) {
		return 0;
	}
	Nprobes = 0;
	for(size_t i = 0; i < Keys.size(); i++) {
		if(Keys[i] != "") {
			Find(Keys[i]);
		}
	}
	return Nprobes;
}


