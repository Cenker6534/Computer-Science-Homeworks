#ifndef pointquadtree_h
#define pointquadtree_h
#include <vector>
#include <string>


using namespace std;

struct TreeCell {
	TreeCell* NW;
	TreeCell* NE;
	TreeCell* SW;
	TreeCell* SE;
	string city;
	int x;
	int y;
	TreeCell() :NW(NULL), NE(NULL),SW(NULL),SE(NULL), x(NULL),y(NULL),city("") {}
	TreeCell(int x_axis, int y_axis, string cname) :x(x_axis), y(y_axis), city(cname), NW(NULL), NE(NULL), SW(NULL), SE(NULL) {}
};

class pointquadtree {
private:
	TreeCell* head;

	void deleteTree(TreeCell * &node);
	TreeCell* &makeCell(int x_axis, int y_axis, string cname);
	void insert(TreeCell* &cell,int x_axis, int y_axis, string cname);
	void SearchCity(TreeCell* , int , int , int , vector<string> & , vector<string> & );
	void PrintCity(TreeCell*);
public:
	void insertCity(int x_axis, int y_axis, string cname);
	pointquadtree();
	~pointquadtree();

	void SearchCircle(int, int, int);
	void PrintTree();

};



#endif
