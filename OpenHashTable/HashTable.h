/*
*HashTable.h
*Author: James Watters
*Date: 11-13-17
*
*Description: Initializes all methods for my hashtable
*			  class. Both public and private

*
*/

#pragma once
#include <string>
#include "Pair.h"
#include <vector>
using namespace std;


class HashTable
{
private:
	vector<Pair> htable;				//Initializes the vector of pairs
	int num_cells;						// Number of cells in htable
	int max_probes;						// Max probes until add, search, or delete stops
	char col_res_type;					// Clarifies what type of collision resolution type ( l or q )
	int c1;								// c1 for quadratic probing
	int c2;								// c2 for quadratic probing
	int hash_fn(std::string value);		// function to find which key the pair should go into
	int lin_probe(std::string value, int cell);		//Linear probing function using the key passed
	int quad_probe(std::string value, int cell);    // Quadtaric probing
	int find_cell(std::string find);				// Finds the cell that the string sent to it is in


public:
	HashTable(int num_cells, char probe_type, int MAX, int c1, int c2);		// Initilizes hash table
	~HashTable();					//Deconstuctor 
	bool add_key(std::string data, int number);		//Adds key with the data and value removes true if it can
	bool remove_key(std::string data);				//Lazy deletes the cell with the passed data
	void erase_table();								// Erases table
	bool resize_table(int new_size);				// Resizes the table and rehashes it
	bool value(string key, int& cell);				// 'returns' the value in the cell using the reference variable
	void print_table();								// Prints out all the data in the table
};


