//Dan Lesko

#include "Graph.h"
#include "Utility.h"
#include "MyExceptions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <vector>
#include <list>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

//constructor
Graph::Graph(int cities, int roads, string filename) : CITIES(cities), ROADS(roads)
{
	//test to see if file is present
	if (!(Utility::FileExists(filename.c_str())))
	{
		throw Exceptions(filename + " was not found!");
	}

	//open file for input
	ifstream inFile(filename.c_str());

	//intitialize smallestEdge
	smallestEdge = 0;

	//declare some variables
	int numCity;
	int numRoad;
	int city1;
	int city2;
	int weight;

	//taken in first two numbers, these become useless
	inFile >> numCity;
	inFile >> numRoad;
	numCities = numCity;
	numRoads = numRoad;

	//initialize cityArray
	cityArray = new int*[numCity];
	for (int i = 0; i < numCity; i++)
	{
		cityArray[i] = new int[numCity];
		for (int j=0; j < numCity; j++)
		{
			cityArray[i][j]=0;
		}
	}

	//fill cityArray
	do
	{
		inFile >> city1;
		inFile >> city2;
		inFile >> weight;

		addCity(city1-1,city2-1,weight);

	}
	while (!inFile.eof());

}

//destructor
Graph::~Graph()
{
	//deletes all values in the cityArray
	for (int i = 0; i < numCities; ++i)
		delete [] cityArray[i];

	delete [] cityArray;
}

//methord to add citys to matrix
void Graph::addCity(int city1, int city2, int numPPL)
{
	//cities are added in this fashion so that our graph is undirected
	cityArray[city1][city2] = numPPL;
	cityArray[city2][city1] = numPPL;
}

//function to cycle through matrix and display its values;
void Graph::displayMatrix()
{
	cout << "ADJACENCY MATRIX:" << endl;
	for(int i=0; i<numCities; i++)
	{
		for(int j=0; j<numCities; j++)
		{
			cout << setw(3) << cityArray[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void Graph::depth(int start, int end)
{
	path.push_back(start);//assign start to path vector
	onPath.insert(start);//asign start to onPath set

	if(start == end)//done aka complete path
	{
		//cout << endl <<  "We Made It!" << endl;
		vector<int> validPath;//copy all values from path to validPath
		validPath = path;

		vector<int> edges;//create a vector called edges

		for(unsigned int pos = 0; pos<path.size()-1; pos++)//cycle thru paths between cities
		{
			int x = path.at(pos);//first city
			int y = path.at(pos+1);//second city

			edges.push_back(cityArray[x][y]);//add edges between first and second cities
		}

		sort (edges.begin(), edges.end());//sort the weights of the edges in ascending order
		
		smallestEdge = edges[0]; // assign smallest edge to the smallest value in edges vector
		bestPath = validPath; // assign bestPath to valid path 
		/*for (int i = 0; i<bestPath.size(); i++)
		{
			cout << bestPath[i]+1 << " ";
		}
		cout << endl;*/
	}
	//consider all neighbors that would continue path with a repeating node
	else
	{
		for (int idx = 0; idx < CITIES; idx++)//loop thru the cities
		{
			int vertex = idx; //assign vertex to index
			if (onPath.find(vertex) != onPath.end()) continue; // if onPath already contains a given vertex, continue
			//cout << start << " " << idx << endl;
			int size = cityArray[start][idx]; //assign size to cityArray start
			if (size == 0 || size < smallestEdge) continue; // if we do not have an edge or if the edge is less than the smallest edge
			depth(vertex, end);//recursively call depth so that the current vertex we are at is now start
		}
	}
	
	path.pop_back();//pop path
	/*set<int>::iterator iter;
	for (iter = onPath.begin(); iter!=onPath.end(); ++iter)
		{
			cout << *iter+1 << " ";
		}
		cout << endl;*/
	onPath.erase(start); // remove start from the set
}

int Graph::trips(int s, int f, int ppl)
{
	//call depth
	depth(s, f);

	//calculate the number of trips
	float trips = 0;
	trips = ceil(static_cast<float>(ppl)/static_cast<float>(smallestEdge-1));
	//display path taken
	cout << "The path traveled is: ";
	for (unsigned int i = 0; i<bestPath.size(); i++)
	{
		cout << bestPath[i]+1 << " ";
	}
	cout << endl;
	return static_cast<int>(trips);

}

