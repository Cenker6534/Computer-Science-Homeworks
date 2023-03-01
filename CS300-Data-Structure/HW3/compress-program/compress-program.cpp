#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.h"

using namespace std;

//
//
//   !!! HashTable is a templated class, source file (HashTable.cpp) must be Exluded from the project !!! 
//
//

// Struct which is used to store key and elements.
struct MyHashedObj
{
	int code;
	string key;
	
	MyHashedObj() :code(-1), key(""){}
	MyHashedObj(int i,string k):code(i),key(k){}
};

// operator overloading is needed in hash() classes. this comparisons is done in its implementation
bool operator==(const MyHashedObj& lhs, const MyHashedObj& rhs) {
	return lhs.key == rhs.key;
}
bool operator!=(const MyHashedObj& lhs, const MyHashedObj& rhs) {
	return lhs.key != rhs.key;
}

int Hash(const MyHashedObj& x, int tableSize) {
	string key = x.key;
	int remainder = 0;
	for (int i = 0; i < key.size(); i++)
	{
		int charNUM = abs(int(key.at(i))); // abs() takes the absolute valur of the character number
		remainder += 7 * charNUM;
		
	}
	
	return abs(remainder) % tableSize; // abs() handles overflow if remainder becomes negative. also module make sures that it is in array range.
}

int main() {
	// Opening files
	ifstream compin;
	ofstream compout;
	string inputFileName = "compin", outputFileName = "compout";
	compin.open(inputFileName.c_str());
	compout.open(outputFileName.c_str());

	// Initializing NOT_FOUND object to determine what should be returned if find() does not find anything in table class.
	// in this case its default constructor of the HashedObj() Class.
	MyHashedObj NOT_FOUND = MyHashedObj();
	HashTable<MyHashedObj> table(NOT_FOUND,256); // initializing table
	
	// creating a Emty Dictionary.
	vector<string> Dict(4096);

	// putting the 256 character into Dict.
	int currentSizeOfDict = 0;
	for (int i = 0; i < 256; i++)
	{
		Dict[i] = string(1,char(i));
		currentSizeOfDict++;
		
		string charStr = string(1, char(i));
		table.insert(MyHashedObj(i,charStr));
	}
	
	// compressing part starts here.
	// p and c is implemented as same in the Assignment 3 homework PDF
	string p = "";
	string c = "";

	// getting the first char.
	c = compin.get();

	// the main loop that compress the file.
	bool isEOF = compin.eof();
	while (!isEOF)
	{
		
		string temp = p + c; // add character c to the back of the string p and store them in temp. (although type of c is string, it stores single character)

		// Checking if the temp is in the Hash Table or not.
		MyHashedObj tableEntry = table.find(MyHashedObj(-1,temp)); // the Code(-1) does not matter since it will only look for string temp.

		if (tableEntry != NOT_FOUND) // if it is found in the table
		{
			p = temp; // store temp in the p.
		}
		else
		{
			
			Dict[currentSizeOfDict] = temp;
			table.insert(MyHashedObj(currentSizeOfDict++, temp ));
			compout << table.find(MyHashedObj(-1,p)).code << " "; // the Code(-1) does not matter since it will only look for string p.
			p = c;
		}
		
		// next char is gotten for the next step iteration of the loop.
		c = compin.get(); 

		// This check if it has reached the EOF. If so, it print the code of the last p. Program will exit the loop in next check.
		if (compin.eof()) {
			compout << table.find(MyHashedObj(-1, p)).code << " ";
			isEOF = true;
		}
	}
	
	

	// Closing the files.
	compin.close();
	compout.close();

	return 0;
}