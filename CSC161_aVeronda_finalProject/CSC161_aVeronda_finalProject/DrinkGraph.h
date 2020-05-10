#pragma once

#include "Beer.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "user.h"


using namespace std;



typedef pair<int, int> Pair; // short hand for later

// class to represent a graph object 
// heavily inspired by https://www.techiedelight.com/graph-implementation-using-stl/
// 

class DrinkGraph
	: public user
{
public:

	// data structure to store graph edges
	struct Edge 
	{
		int src, dest;
		double weight;
		Beer beerGraphNode;
	};

	// construct a vector of vectors of Pairs to represent an adjacency list
	vector<vector<Pair>> adjList;
	vector<Edge> edges;
	deque<Beer> beerGraphDBQue; // que of beers to create list, should've called function in beerDataBase

	// Graph Constructor
	DrinkGraph( );
	deque<Beer>& constructList( deque<Beer>& );	// list to pull from, change to pointer
	void setWeight( deque<Beer>&, vector<Edge>& );		// create edges and weight
	void changeOnLike();						// unused, for future better weight implementation
	void searchGraph();							// ditto
	void printGraph(DrinkGraph const&);			// prints graph using range based for loop
	

};

// vector<Edge> const& edges, int N
DrinkGraph::DrinkGraph( )
{
	beerGraphDBQue = constructList(beerGraphDBQue);

	adjList.resize(beerGraphDBQue.size());
	edges.resize(beerGraphDBQue.size());

	setWeight(beerGraphDBQue, edges);

	// add edges to the directed graph
	for (auto& edge : edges)
	{
		int src = edge.src;
		int dest = edge.dest;
		int weight = edge.weight;
		Beer beerGraphNode = edge.beerGraphNode;

		// insert at the end
		adjList[src].push_back(make_pair(dest, weight));

		// Uable to get working, when uncommented causes vector range error
		//adjList[dest].push_back(make_pair(src, weight));
	}
}


inline deque<Beer>& DrinkGraph::constructList( deque<Beer>& beerGraphDBQue)
{
	if (isNewUser())
	{
		ifstream inFile;
		inFile.open("drinkDB.txt");
		int count = 0;
		char getDBEntry[100];
		Beer beerInfo;



		if (inFile)
		{
			inFile.ignore(10000, '!');

			while (inFile.good()) // could be .eof() not sure of included checks in .good()
			{
				for (int i = 0; i < count; i++)
				{
					inFile.ignore(1000, '/n');
				}
				inFile.getline(getDBEntry, 256, '_');
				beerInfo.abv = stod(getDBEntry);

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.name = getDBEntry;

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.type = getDBEntry;

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.hoppiness = stoi(getDBEntry);

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.darkness = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.producer = getDBEntry;
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.microBrew = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.drankPreviously = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.likedDrink = stoi(getDBEntry);
				//getDBEntry.clear();

				beerGraphDBQue.push_back(beerInfo);

				try
				{
					inFile.peek();
				}
				catch (const std::exception& e)
				{
					break;
				}
			}

			inFile.close();
		}
	}
	else
	{
		ifstream inFile;
		inFile.open("userDB.txt");
		int count = 0;
		char getDBEntry[100];
		Beer beerInfo;



		if (inFile)
		{
			inFile.ignore(10000, '#');

			while (inFile.good()) // could be .eof() not sure of included checks in .good()
			{
				for (int i = 0; i < count; i++)
				{
					inFile.ignore(1000, '/n');
				}

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.abv = stod(getDBEntry);

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.name = getDBEntry;

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.type = getDBEntry;

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.hoppiness = stoi(getDBEntry);

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.darkness = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.producer = getDBEntry;
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.microBrew = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.drankPreviously = stoi(getDBEntry);
				//getDBEntry.clear();

				inFile.getline(getDBEntry, 256, '_');
				beerInfo.likedDrink = stoi(getDBEntry);
				//getDBEntry.clear();

				beerGraphDBQue.push_back(beerInfo);

				try
				{
					inFile.peek();
				}
				catch (const std::exception& e)
				{
					break;
				}
			}

			inFile.close();
		}
	}
	return beerGraphDBQue;
}

// TODO: better algorythim for weight determination, 0's should not touch 10's, better average, will need input from user class 
//	for better taste determination (order on hoppiness, order on darkness, compare and fudge weight from there, order based on 
//  computed value and add to graph)

inline void DrinkGraph::setWeight(deque<Beer>& beerWeightQue, vector<DrinkGraph::Edge>& edgeVector)				// create edges and weight
{
	int j = 0;

	for (int i = 0; i < beerWeightQue.size(); i++)
	{
		double hops = 10.0 - beerWeightQue[i].hoppiness;
		double dark = 10.0 - beerWeightQue[i].darkness;
		
		if (hops == 10 || dark == 10)
		{
			edgeVector[j] = { j, 0, 0 };
		}
		else
		{
			hops = ((hops * 5) + (dark * 5)) / 6; // arbituary
			edgeVector[j] = { j, j + 1, hops };
		}

		j++;
	}
}

inline void DrinkGraph::changeOnLike()
{


}

inline void DrinkGraph::searchGraph()
{

}


void DrinkGraph::printGraph(DrinkGraph const& graph)
{
	for (int i = 0; i < beerGraphDBQue.size(); i++)
	{
		cout << beerGraphDBQue[i];
		// print all neighboring vertices of given vertex
		for (Pair v : graph.adjList[i])
			cout << "(" << i << ", " << v.first <<
			", " << v.second << ") ";
		cout << endl;
	}
}

