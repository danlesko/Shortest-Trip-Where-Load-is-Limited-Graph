#include "Graph.h"
#include "MyExceptions.h"
#include "Utility.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	//read the command line argument and generate a graph
	int cities, roads;

	string filename = argv[1];

	if (!(Utility::FileExists(filename.c_str())))
	{
		throw Exceptions(filename + " was not found!");
	}

	ifstream inFile(filename.c_str());
	inFile >> cities;
	inFile >> roads;
	inFile.close();

	Graph mygraph(cities, roads, filename);
	mygraph.displayMatrix();

	//
	//THESE ARE COMMENTED OUT CURRENTLY,
	//UNCOMMENT FOR TESTING / DEBUGGING
	//
	//mygraph.trips(0, 6, 99);

	//mygraph.depth(0,6);

	/*cout << mygraph.bestPath.size() << endl;
	for (int i = 0; i < mygraph.bestPath.size(); i++)
	{
		cout << mygraph.bestPath[i]+1 << " ";
	}*/

	int s, d, t;
	cout << "Please enter the starting city number: ";
	cin >> s;
	cout << "Please enter the ending city number: ";
	cin >> d;
	cout << "Please enter the number of travelers: ";
	cin >> t;

	//take user input on the source city, destination city, and the number of tourists
	//print the minimum number of trips
	s--;
	d--;
	cout<<"Minimum Number of Trip: "<< mygraph.trips(s,d,t) <<endl;
}
