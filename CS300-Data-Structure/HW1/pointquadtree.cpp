#include "pointquadtree.h"
#include <iostream>

using namespace std;

pointquadtree::pointquadtree() {
	head = NULL;
};
TreeCell* &pointquadtree::makeCell(int x_axis, int y_axis, string cname) {
	TreeCell* node = new TreeCell(x_axis, y_axis, cname);
	return node;
}

void pointquadtree::deleteTree(TreeCell* &node) {
	if (node != NULL)
	{
		deleteTree(node->NW);
		deleteTree(node->NE);
		deleteTree(node->SW);
		deleteTree(node->SE);
		delete node;
		node = NULL;
	}
}
pointquadtree::~pointquadtree() {
	deleteTree(head);
}

void pointquadtree::insert(TreeCell* &cell, int x_axis, int y_axis, string cname) {
	if (cell == NULL) {
		cell = makeCell(x_axis, y_axis, cname);
	}
	else
	{
		if (x_axis < cell->x)
		{
			if (y_axis < cell->y) {
				insert(cell->SW, x_axis, y_axis, cname);
			}
			else {
				insert(cell->NW, x_axis, y_axis, cname);
			}
		}
		else {
			if (y_axis < cell->y)
			{
				insert(cell->SE, x_axis, y_axis, cname);
			}
			else
			{
				insert(cell->NE, x_axis, y_axis, cname);
			}
		}
	}
}

void pointquadtree::insertCity(int x_axis, int y_axis, string cname) {
	
	insert(head, x_axis, y_axis, cname);
	
}

void pointquadtree::SearchCity(TreeCell* cell, int centerx, int centery, int radius, vector<string> & foundcities, vector<string> & searchedcities) {
	if (cell == NULL)
	{
		return;
	}
	searchedcities.push_back(cell->city);
	if ((cell->x - centerx) * (cell->x - centerx) + (cell->y - centery) * (cell->y - centery) <= radius * radius)
	{
		foundcities.push_back(cell->city);
		SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
		SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
		SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
		SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
	}
	else
	{
		if (centery + radius < cell->y)
		{
			if (centerx + radius < cell->x)
			{
				SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
			}
			else if (cell->x < centerx - radius)
			{
				SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
			}
			else
			{
				SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
				SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
			}
		}
		else if (cell->y < centery - radius)
		{
			if (centerx + radius < cell->x)
			{
				SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
			}
			else if (cell->x < centerx - radius)
			{
				SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
			}
			else
			{
				SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
				SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
			}
		}
		else
		{
			if (centerx + radius < cell->x)
			{
				SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
				SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
			}
			else if (cell->x < centerx - radius)
			{
				SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
				SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
			}
			else
			{
				if (centery < cell->y)
				{
					if (centerx < cell->x)
					{
						SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
					}
					else
					{
						SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
					}
				}
				else
				{
					if (centerx < cell->x)
					{
						SearchCity(cell->SW, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);
					}
					else
					{
						SearchCity(cell->SE, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NE, centerx, centery, radius, foundcities, searchedcities);
						SearchCity(cell->NW, centerx, centery, radius, foundcities, searchedcities);	
					}
				}
			}
		}
	}
}

void pointquadtree::SearchCircle(int centerx, int centery, int radius) {
	vector<string> foundcities;
	vector<string> searchedcities;
	SearchCity(head, centerx, centery, radius, foundcities, searchedcities);
	if (foundcities.size() == 0)
	{
		cout << "<None>";
	}
	else
	{
		cout << foundcities.at(0);
		for (int i = 1; i < foundcities.size(); i++)
		{
			cout << ", " << foundcities.at(i);
		}
	}
	
	cout << endl;
	if (0 < searchedcities.size())
	{
		cout << searchedcities.at(0);
	}
	for (int i = 1; i < searchedcities.size(); i++)
	{
		cout << ", " << searchedcities.at(i);
	}
	cout << endl;
}

void pointquadtree::PrintCity(TreeCell* cell) {
	if (cell != NULL)
	{
		cout << cell->city << endl;

		PrintCity(cell->SE);
		PrintCity(cell->SW);
		PrintCity(cell->NE);
		PrintCity(cell->NW);

	}
	
}
void pointquadtree::PrintTree() {
	PrintCity(head);
}