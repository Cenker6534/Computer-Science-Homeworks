#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {

	// Opening the files.
	ifstream compout;
	ofstream decompout;
	string inputFileName = "compout", outputFileName = "decompout";
	compout.open(inputFileName.c_str());
	decompout.open(outputFileName.c_str());

	// Creating a Dictionary
	vector<string> Dict(4096);


	// Putting the characters into dictionary
	int currentSizeOfDict = 0;
	for (int i = 0; i < 256; i++)
	{
		Dict[i] = string(1, char(i));
		currentSizeOfDict++;

		string charStr = string(1, char(i));
		
	}

	// getting the first code. it is done seperately since there is no prev before it 
	string temp="",c = "";
	int code, prev;
	compout >> c;
	if (!compout.eof()) {
		code = prev = stoi(c);
		decompout << Dict[code];

		compout >> c; // for next step
	}
	// Main loop that gets the code and directs Dict[code] to decompout.
	while (!compout.eof()) {
		
		code = stoi(c);
		if (code < currentSizeOfDict)
		{
			// if the code is in the dictionary
			temp = Dict[prev] + Dict[code].at(0);
			Dict[currentSizeOfDict] = temp;
			decompout << Dict[code];
		}
		else {
			// if the not in the dictionary; 
			temp = Dict[prev] + Dict[prev].at(0);
			Dict[currentSizeOfDict] = temp;
			decompout << Dict[code]; // we are directing temp to decompout (currentSizeOfDict always will be equal to code);
		}
		prev = code; // updating previous for the next iteration of the loop.
		currentSizeOfDict++;// increasing the size of the Dict in here since both cases appends string to Dict.
		
		compout >> c; // for next step
		
	}


	// Closing the files
	compout.close();
	decompout.close();

	return 0;
}