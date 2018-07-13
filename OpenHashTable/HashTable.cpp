/*
*HashTable.cpp
*Author: James Watters
*Date: 11-13-17
*
*Description: Contains all the functions and methods
*			  for the HashTable. Contains the functionality
*			  of each method and creates the variables.
*
*/

#include "HashTable.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;


//Creates the table as a vector. Takes the table size, probing type, max cell size
// and c1 and c2 to use for the hashing funciton.
HashTable::HashTable(int table_size, char type, int	MAX, int cOne, int cTwo) {		//Initializes table for each needed variable
	max_probes = MAX;
	c1 = cOne;
	c2 = cTwo;
	col_res_type = type;
	num_cells = table_size;
	htable.resize(num_cells);
	int max_counter;
}


//Destroys hashtable
HashTable::~HashTable()			// Sets all members back to NULL types but maintains the size.
{
	htable.clear();
	col_res_type = '/0';
	num_cells = 0;
	c1 = 0;
	c2 = 0;
	max_probes = 0;
}



//Takes the string value and converts it into a number.
//Then, takes the number and divides it by the size of the hashtable
//to come up with the correct location for the hash value. 
int HashTable::hash_fn(string data) {
	int sum = 0;
	for (int i = 0; i < data.length(); i++) {			//Iterates through the string and adds the value of each
		sum += int(data[i]);
	}
	return sum % htable.size();							// Performs the hashing function
}


//Probes through the hashtable if there is a collision and 
// finds the next available location using the linear probing 
//equation
int HashTable::lin_probe(string key, int i = 0) {		//Linearly probes through the table if collision occurs

	int counter = max_probes;
	int new_location = hash_fn(key);
	while (htable[new_location].status == 1) {				//if the status is 1, there is a collision and continue
		new_location = ((hash_fn(key) + i) % num_cells);    // perform the linear probe
		i += 1;												// increments i
		counter--;
		
	}
	if (counter > 0) {										//Checks if max_probes has been reached
		return new_location;			
	}
	return NULL;
}


//Probes through the hashtable if there is a collision and 
// finds the next available location using the quadratic probing 
//equation
int HashTable::quad_probe(string key, int i = 0) {						//Probes through the table if there is a collision
	int counter = max_probes;											//Temporary variable to store max probes
	int new_location = hash_fn(key);
	while (htable[new_location].status == 1) {							// if the status is 1, continue
		int trial = (hash_fn(key) + (c1 * pow(i, 2)) + (c2 * i));		// does hash function
 		new_location = (trial % num_cells);								//updates new location
		i++;
		counter--;														//Decrements counter to check if max is reached later
		
	}
	if (counter > 0) {													//checks if max probes has been reached
		return new_location;
	}
	return NULL;													//The counter is 0 or less and return NULL as invalid
}


//Searches throughout the HashTable to find the cell location of 
// where the finder data is located and returns the location integer
int HashTable::find_cell(string finder) {
	int start = hash_fn(finder);

	int i = 0;
	if (col_res_type == 'l') {								//searches through the hash table linearly
		while (htable[start].key != finder) {
			if (htable[start].status == 0) {				//checks if it is at an open cell, if yes, if is not found
				return (-1);								//returns -1 meaning it is not found
			}
			start = ((hash_fn(finder) + i) % num_cells);		//Performs the linear function
			i++;
		}
		return start;
	}

	else if (col_res_type == 'q') {							//searches through the hash table quadraticly
		while (htable[start].key != finder) {
			if (htable[start].status == 0) {				//checks if it is at an open cell, if yes, if is not found
				return (-1);								//returns -1 meaning it is not found
			}
			int checker = (hash_fn(finder) + (c1 * pow(i, 2)) + (c2 * i));		//Performs the quadratic function
			start = (checker % num_cells);		//Updates start to get new position
			i++;
		}
		return start;							//Returns the start position
	}
}


//Adds a key into the HashTable. Takes the info
bool HashTable::add_key(string key, int value) {		//Initializes the key and value that will be added into the table	

	Pair next;
	next.key = key;
	next.value = value;
	next.status = 1;

	int location = hash_fn(key);						// Gets the start location where the cell should go

	int yes_no = find_cell(key);						// Checks if the key already exists

	if (yes_no == -1) {									//if the cell does not exist...

		if (htable[hash_fn(key)].status != 1) {			// ... and the cell is empty,
			htable[location] = next;					// add the newly made pair into the vector
		}

		else {											//Else, the status is 1, and there is a collision, start probing 
			if (col_res_type == 'l') {					//Checks if it is a linear probing table, and performs
				if (lin_probe(key,1) != NULL) {
					int new_loc = lin_probe(key, 1);	// sends to linear probe
					htable[new_loc] = next;
					return true;						//if found a valid cell, returns true
				}
				else {
					return false;
				}
			}

			else if (col_res_type == 'q') {				//Checks if the collision type is quadratic
				if (quad_probe(key, 1) != NULL) {		// Checks that quadratic probing returns a valid integer
					int new_loc = quad_probe(key, 1);
					htable[new_loc] = next;
					return true;						//Quadratic worked, a cell was found, and return true.
				}
				else {
					return false;						// Returns false because quadratic found and issue
				}
			}
		}
	}

	else if(yes_no != -1){					//If the value was already in the table, update the previous value.
		htable[yes_no].value = value;
	}
}

//Attempts to remove a Pair from the hash table.
//If the value exists, the status to change to -1 to "lazy delete" it
//and return true. If the value does not exist, it will return false.
bool HashTable::remove_key(string key) {

	int position = find_cell(key);
	if (position == -1) {					//If the position returns false, there was an issue and return false
		return false;
	}

	else {									//Lazy delete by changing the status to -1
		htable[position].status = -1;
		return true;
	}
}

//Erases all the data in the table
void HashTable::erase_table() {					//Erase the table and sets all status back to 0
	for (int i = 0; i < num_cells; i++) {
		htable[i].key = "";
		htable[i].value = 0;
		htable[i].status = 0;
	}
}


//Resizes the table. And remaps all the old elements into 
//the new correct location of the hashtable. If the hashtable cannot 
//be resized into the new size; return false. Otherwise, remap and
//return true.
bool HashTable::resize_table(int new_size) {

	int full = 0;
	for (int i = 0; i < num_cells; i++) {			//Counts to see how many valid items are in the Hashtable
		if (htable[i].status == 1) {				
			full += 1;
		}
	}
		
	if (full > new_size) {							//If the new_size is not big enough to contain the old elements return false
		return false;
	}

	vector<Pair> copy;								//Making a new copy
	int old_size = num_cells;


/**********************************************
*The following is an implementation from 
* http://www.geeksforgeeks.org/ways-copy-vector-c/
* to copy a vector.
**********************************************/
	for (int i = 0; i < old_size; i++) {				//Copy the old vector in a temp copy
		copy.push_back(htable[i]);
	}



	htable.clear();							//Clears the vector and resizes the 
	htable.resize(new_size);	
	num_cells = new_size;

	for (int i = 0; i < old_size; i++){					//For all the items in the copy, rehash them into the new resized table
		if (copy[i].status == 1) {
			add_key(copy[i].key, copy[i].value);
		}
	}
	return true;			//They all fit into the new size and returns true
}


//Finds the cell to the key received by the string parameter and sets the int
//reference variable to associated value of the key - value pair.Returns true if the key is found, otherwise
//false.
bool HashTable::value(string key, int &found_value) {			
	int found = find_cell(key);							//Finds the cell where the key is stored

	if (found == -1) {									//If find cell sends back -1, then it is not in there, return false. 
		return false;
	}

	else {
		found_value = (htable[found].value);			//Else, the value exists, change the reference variable to it, and return true

		return true;
	}
}


//Prints all the key, value, and status of all the Pairs in the table.
void HashTable::print_table() {
	for (int i = 0; i < htable.size(); i++) {
		cout << "Key: " << htable[i].key << " Value: " << htable[i].value << " Status: " << htable[i].status << endl;		//prints all info of the cell
	}
}

