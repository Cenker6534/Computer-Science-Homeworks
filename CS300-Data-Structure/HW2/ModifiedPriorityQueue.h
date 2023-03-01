#ifndef ModifiedPriorityQueue_h
#define ModifiedPriorityQueue_h

#include <vector>

using namespace std;

struct QueueNode {
	int value;
	int label;
	QueueNode() {
		value = 0;
		label = 0;
	}
	QueueNode(int val, int lab) {
		value = val;
		label = lab;
	}
};

class ModifiedPriorityQueue {
private:
	vector<QueueNode> heapArray;
	int currentSize;

	// Perculates down the given index.
	void percolateUp(int hole);

	// Perculates up the given index.
	void percolateDown( int hole);
public:
	// Default const
	ModifiedPriorityQueue();

	// Since private members of the class has their own Destrucotor,
	//	nothing extra is needed.
	~ModifiedPriorityQueue();

	//	inserts new element to the Heap with given label and value.
	void insert(int value, int label);

	//	Removes the node with given label. Also it returns the removed node.
	//		Returns dummy node (value and label is -1) if it couldnt removed anything
	QueueNode Remove(int label);

	//	It returns the node with the maximum value. it does not remove it.
	//		Returns node with value=0 label=-1 if currentsize is 0
	QueueNode GetMax() const;

	// Returns true if current size is 0. Else, it returns false.
	bool IsEmpty() const;

	

};

//Comparisons are done with respect to values of QueueNode
bool operator<=(const QueueNode& lhs, const QueueNode& rhs);
bool operator>=(const QueueNode& lhs, const QueueNode& rhs);
bool operator<(const QueueNode& lhs, const QueueNode& rhs);
bool operator>(const QueueNode& lhs, const QueueNode& rhs);



#endif