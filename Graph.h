#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <set>

using namespace std;

class Graph
{
public:
	//contructor
	Graph(int, int, string);
	//destructor
	~Graph();
	//cityArray variable
	int **cityArray;
	//methord to display matrix representation of graph
	void displayMatrix();
	//method to determine number of trips
	int trips(int, int, int);
	

private:

	//variables to store data that we throw away
	int numCities;
	int numRoads;

	//variables that store same data as above, but are constant
	const int CITIES;
	const int ROADS;

	//methord to add cities
	void addCity(int, int, int);
	//method to calculate shortest path
	void depth(int, int);
	
	//variables needed for depth functionality
	vector<int> bestPath;
	vector<int> path;
	set<int> onPath;
	int smallestEdge;

};



#endif