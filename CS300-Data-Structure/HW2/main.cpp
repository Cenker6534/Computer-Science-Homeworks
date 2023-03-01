#include "ModifiedPriorityQueue.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// this struct is the node of the Array. it stores either left x value or right value of the building with given label which is also stored.
struct buildingX {
	int xVal;
	int label;
	bool isLeftX;
	buildingX(): xVal(-1),label(-1),isLeftX(true) {}
};

//			SORTING PART
// 
// 
// By Design choice, buildHeap() and deleteMin functions implemented as funtion in main file.
// There is no need to implement a class for this since it will be used to sorting only.
// it is Maxheap

void buildHeap( vector<buildingX> & Heap) {
	int sizeOfHeap = Heap.size() - 1; // removing dummy node
	for (int hole0 = sizeOfHeap / 2; hole0 > 0; hole0--)
	{
		// percolateDown (code is taken from slides of Lecture)
		int hole = hole0;
		int child;
		buildingX tmp = Heap[hole];
		
		for (; hole * 2 <= sizeOfHeap; hole = child)
		{
			child = hole * 2;
			if (child != sizeOfHeap && Heap[child + 1].xVal > Heap[child].xVal)
			{
				child++;
			}

			// Modification: if their Xvalues are equal, right end must be seen like higher
			//				 in order to be right side of the sorted vector.
			if (child != sizeOfHeap && Heap[child + 1].xVal == Heap[child].xVal && Heap[child +1].isLeftX == false)
			{
				child++;
			}
			if (Heap[child].xVal > tmp.xVal)
			{
				Heap[hole] = Heap[child];
			}
			// Modification:
			else if (Heap[child].xVal == tmp.xVal && Heap[child].isLeftX == false) {
				Heap[hole] = Heap[child];
			}
			else {
				break;
			}
		}
		Heap[hole] = tmp;
		// end of percolateDown
		
	}
}
buildingX DeleteMax(vector<buildingX>& Heap,int &sizeOfHeap) {
	buildingX maxVal;
	if (sizeOfHeap > 1)
	{
		maxVal = Heap[1];
		Heap[1] = Heap[sizeOfHeap];
		Heap[sizeOfHeap--] = maxVal;
		int hole = 1;
		// PercolateDown (code is taken from slides of Lecture)
		int child;
		buildingX tmp = Heap[hole];
		
		for (; hole * 2 <= sizeOfHeap; hole = child)
		{
			child = hole * 2;
			if (child != sizeOfHeap && Heap[child + 1].xVal > Heap[child].xVal)
			{
				child++;
			}

			// Modification: if their Xvalues are equal, right end must be seen like higher
			//				 in order to be right side of the sorted vector.
			// example-> xVal == 0 are sorted as (isLeftX) true,true,true,true,false,false 
			//					=> false will be always at the end for same xValues  
			if (child != sizeOfHeap && Heap[child + 1].xVal == Heap[child].xVal && Heap[child + 1].isLeftX == false)
			{
				child++;
			}
			if (Heap[child].xVal > tmp.xVal)
			{
				Heap[hole] = Heap[child];
			}
			// Modification:
			else if (Heap[child].xVal == tmp.xVal && Heap[child].isLeftX == false) {
				Heap[hole] = Heap[child];
			}
			else {
				break;
			}
		}
		Heap[hole] = tmp;
		
		// end of percolateDown
	}
	return maxVal;
}

// O(NlogN) 
void HeapSort(vector<buildingX>& Heap) {
	//O(N) complexity
	buildHeap(Heap);
	vector<buildingX> temp;
	int size = Heap.size()-1;
	// O(NlogN)
	while ( size > 1)
	{
		DeleteMax(Heap,size);
	}
}

/*		 END OF SORTING PART		*/	



int main() {
	ifstream inputfile;
	string filename = "input.txt";
	inputfile.open(filename.c_str());

	int buildingcount;
	inputfile >> buildingcount;

	vector<buildingX> xAxisArr(2 * buildingcount + 1);

	// index of values (heights) corresponds to labels of building 
	vector<int> heightsArr(buildingcount + 1);
	heightsArr[0] = -1;

	// Reading file into 2 different arrays
	// Bulding labels starts from 1 (loop also starts from 1)
	for (int i = 1; i <= buildingcount; i++)
	{
		// left X value of Building
		inputfile >> xAxisArr[2 * i -1].xVal;
		xAxisArr[2 * i -1].isLeftX = true;
		xAxisArr[2 * i -1].label = i;

		// height of building
		inputfile >> heightsArr[i];

		// right X value of Building
		inputfile >> xAxisArr[2 * i].xVal;
		xAxisArr[2 * i].isLeftX = false;
		xAxisArr[2 * i].label = i;
		

	}
	
	// Sorts the vector as ascending order with respect to their Xvalues 
	// (if XVals are same, left nodes are first) 
	HeapSort(xAxisArr);
	
	// If the xValue of the first node is not zero, it prints that there is no skyscraper at the 0th X.
	if (buildingcount > 0 && xAxisArr[1].xVal != 0)
	{
		cout << "0 0" << endl;
	}

	// This loop iterates every xValues node
	ModifiedPriorityQueue Heap;
	for (int i = 1, maxValBeforeRepeat = -1; i <= 2 * buildingcount; i++)
	{
		buildingX temp = xAxisArr[i];
		QueueNode maxValueNode;

		 

		// Checks if next element has same x value. if so, it will disable couts.
		// Printing will be done only in the last element of the same xValues.
		//		It will wait all the insertion and deletion for the same xValues
		bool isNextIsSameX = false;
		if (i < 2 * buildingcount && temp.xVal == xAxisArr[i+1].xVal)
		{
			isNextIsSameX = true;
		}
		

		if (temp.isLeftX)
		{
			// Insert
			int newVal = heightsArr[temp.label];
			Heap.insert(newVal,temp.label);
			
		}
		else
		{
			// Remove
			int oldVal = Heap.Remove(temp.label).value;
			
		}
		maxValueNode = Heap.GetMax();


		// Printing will be done if it is last element of the same x values(as mentioned above)
		//	and if max value is changed after insertions and deletions for the same xValues
		if (!isNextIsSameX && maxValBeforeRepeat != maxValueNode.value)
		{
			cout << temp.xVal << " " << maxValueNode.value << endl;
		}

		// If there is different xVal at the next idx, maxValBeforeRepeat will be updated
		if (!isNextIsSameX)
		{
			maxValBeforeRepeat = Heap.GetMax().value;
		}
	}


	return 0;
}
