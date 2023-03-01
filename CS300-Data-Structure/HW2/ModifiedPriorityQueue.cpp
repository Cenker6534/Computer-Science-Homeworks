#include "ModifiedPriorityQueue.h"

using namespace std;


ModifiedPriorityQueue::ModifiedPriorityQueue() {
	currentSize = 0;
	QueueNode node(-1, -1);
	heapArray.push_back(node); // First node of vector is dummy node.
}




// This implementation is modified version of codes in the lecture slides.
void ModifiedPriorityQueue::percolateDown(int hole) {
	int child;
	QueueNode tmp = heapArray[hole];

	for (; hole*2 <= currentSize; hole = child)
	{
		child = hole * 2; 
		if (child != currentSize && heapArray[child + 1] > heapArray[child])
		{
			child++;
		}
		if (heapArray[child] > tmp)
		{
			heapArray[hole] = heapArray[child];
		}
		else {
			break;
		}
	}
	heapArray[hole] = tmp;
}

// This implementation is modified version of codes in the lecture slides.
void ModifiedPriorityQueue::percolateUp(int hole) {
	QueueNode temp = heapArray[hole];
	for (; hole > 1 && temp > heapArray[hole/2] ; hole /= 2)
	{
		heapArray[hole] = heapArray[hole / 2];
	}
	heapArray[hole] = temp;
}

void ModifiedPriorityQueue::insert(int value, int label) {
	QueueNode Node(value, label);
	heapArray.push_back(Node);
	percolateUp(++currentSize);
}

QueueNode ModifiedPriorityQueue::Remove(int label) {
	QueueNode temp(-1, -1);
	for (int i = 1; i <= currentSize; i++)
	{
		if (heapArray[i].label == label) {
			temp.label = label;
			temp.value = heapArray[i].value;
			heapArray[i] = heapArray[currentSize--];
			heapArray.pop_back();
			if (!IsEmpty() && currentSize >= i)
			{
				percolateDown(i);
			}
			break;
		}
	}
	return temp;
}
bool ModifiedPriorityQueue::IsEmpty() const {
	return currentSize == 0;
}

QueueNode ModifiedPriorityQueue::GetMax() const {
	QueueNode node(0,-1);
	if (!IsEmpty())
	{
		node = heapArray[1];
	}
	return node;
}


ModifiedPriorityQueue::~ModifiedPriorityQueue() {

}

// Operator overloading => values will be compared of given nodes
bool operator<=(const QueueNode& lhs, const QueueNode& rhs) {
	return lhs.value <= rhs.value;
}
bool operator>=(const QueueNode& lhs, const QueueNode& rhs) {
	return lhs.value >= rhs.value;
}
bool operator<(const QueueNode& lhs, const QueueNode& rhs) {
	return lhs.value < rhs.value;
}
bool operator>(const QueueNode& lhs, const QueueNode& rhs) {
	return lhs.value > rhs.value;
}
