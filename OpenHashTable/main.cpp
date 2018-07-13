/*
*main.cpp
*Author: James Watters
*Date: 11-13-17
*
*Description: Tests the functionality of my hashtable
*			  Tests if it can add, delete, find, and
*			  resize properly.
*
*/

#include <iostream>
#include "HashTable.h"
using namespace std;

int main() {

	HashTable hasher(13, 'q', 50, 1,1);

	hasher.add_key("ab", 50);
	hasher.add_key("ba", 98);
	hasher.add_key("c", 1);
	hasher.add_key("e", 6);
	hasher.add_key("a", 51);
	hasher.add_key("t", 221);
	hasher.add_key("b", 89);

	hasher.add_key("t", 222);

	hasher.add_key("w", 662);
	hasher.add_key("zasdf", 111);

	hasher.add_key("zzzzzzzzz" ,9);

	hasher.remove_key("e");

	int finder;
	int neww = hasher.value("b", finder);


	cout << "VALUE: " << finder << endl;

	hasher.print_table();

	cout << "_____________________________________" << endl;

	hasher.resize_table(19);

	hasher.print_table();

	cout << "_____________________________________" << endl;
	hasher.erase_table();


	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Press ENTER to continue..." << flush;
	cin.get();

	return 0;
}