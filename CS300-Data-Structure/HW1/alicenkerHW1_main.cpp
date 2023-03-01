#include <iostream>
#include <string>
#include <fstream>
#include "pointquadtree.h"
using namespace std;

int main() {
	string citiesFN = "cities.txt";
	string queriesFN = "queries.txt";

	ifstream cities;
	ifstream queries;

	cities.open(citiesFN.c_str());
	queries.open(queriesFN.c_str());

	pointquadtree qTree;
	int x, y, horizantaldim, verticaldim;
	string cityname;

	cities >> horizantaldim >> verticaldim;
	while (!cities.eof())
	{
		cities >> cityname >> x >> y;
		qTree.insertCity(x, y, cityname);
	}
	qTree.PrintTree();
	int radius;
	string xstr, ystr;
	while (!queries.eof())
	{
		cout << endl;
		queries >> xstr >> ystr >> radius;
		x = stoi(xstr.substr(0, xstr.length() - 1));
		y = stoi(ystr.substr(0, ystr.length() - 1));
		qTree.SearchCircle(x, y, radius);
		
	}
	
	return 0;
}