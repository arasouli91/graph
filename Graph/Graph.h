#pragma once
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <queue>
using namespace std;

template<class T, class numType> class Edge
{
public:
	numType weight;
	T v, w;
	Edge() : v(), w(), weight(0) {}
	Edge(T firstVertex, T secondVertex, numType edgeWeight) : v(firstVertex), w(secondVertex), weight(edgeWeight) {}
	bool operator<(const Edge<T, numType>& other) const { return (weight < other.weight); }
};

// Undirected weighted graph. 
// First template parameter must overload < and == operators
// A specialization of hash<T> must be defined for first template parameter
// Second template parameter must be numerical type
//  or a user defined type that overloads < and = operators and has a constructor
//  that takes int and initializes underlying type with a conceptual minimum value
// Both types need copy constructors
template<class T, class numType> class Graph
{
private:
	int numVertices = 0;
	int numEdges = 0;
	map<T, map<T, numType> > adjList; //map< First_Vertex, map< Second_Vertex, Edge_Weight > >
public:
	int getNumVertices() const;
	int getNumEdges() const;
	void addVertex(T v);

	//@pre The vertices exist in the graph.
	//@post Adds to both v and w's list.
	void addEdge(Edge<T, numType> e);

	void removeEdge(Edge<T, numType> e);
	Graph<T, numType> primsMinTree(T root);
};

template<class T, class numType> int Graph<T, numType>::getNumVertices() const { return numVertices; }
template<class T, class numType> int Graph<T, numType>::getNumEdges() const { return numEdges; }

template<class T, class numType>
void Graph<T, numType>::addVertex(T v)
{
	map<T, numType> emptyMap;
	adjList.insert(make_pair(v, emptyMap));
	++numVertices;
}

//@pre The vertices exist in the graph.
//@post Adds to both v and w's list.
template<class T, class numType>
void Graph<T, numType>::addEdge(Edge<T, numType> e)
{
	adjList[e.v].insert(make_pair(e.w, e.weight));
	adjList[e.w].insert(make_pair(e.v, e.weight));
	++numEdges;
}

template<class T, class numType>
void Graph<T, numType>::removeEdge(Edge<T, numType> e)
{
	adjList[e.v].erase(e.w);        //v->w
	adjList[e.w].erase(e.v);        //w->v
	--numEdges;
}

template<class T, class numType>
Graph<T, numType> Graph<T, numType>::primsMinTree(T root)
{
	Graph<T, numType> MST;	// minimum spanning tree
	for (auto it = adjList.begin(); it != adjList.end(); ++it)	// transfer vertices to MST
		MST.addVertex(it->first);

	// minimum distance to a vertex included in priority queue
	unordered_map<T, numType> minDist;	// <vertex, distance>
	unordered_set<T> visited;
	// distance, Edge
	priority_queue<pair<numType, Edge<T, numType>>, 
					vector<pair<numType, Edge<T, numType>>>,
					greater<pair<numType, Edge<T, numType>>>> pQ;

	// start with root. The edge is a self-loop with 0 distance
	pQ.push(make_pair<numType, Edge<T, numType>>(0, Edge<T, numType>(root, root, 0)));
	visited.insert(root);
	bool firstIteration = true;

	while (!pQ.empty() && visited.size() < numVertices)
	{
		// pop minimum distance paired with corresponding edge
		pair<numType, Edge<T, numType>> curEdge = pQ.top(); pQ.pop();
		// skip visited destination vertices 
		while (!firstIteration && visited.find(curEdge.second.w) != visited.end())
		{
			curEdge = pQ.top(); pQ.pop();
		}
		T curVertex = curEdge.second.w;	// Vertex currently being considered

		if (!firstIteration)
		{
			MST.addEdge(curEdge.second);		// push this edge to the MST
			visited.insert(curEdge.second.w);	// we are done with this destination vertex
			///only for testing
			cout << curEdge.second.v << "->" << curEdge.second.w << " d:" << curEdge.first << endl; 
		}

		// push edges going to minimum distance unvisited adjacent vertices to queue
		for (auto adjVertex : adjList[curVertex])	// adjVertex is a pair of type T vertex and int distance
		{
			auto curMinDist = minDist.find(adjVertex.first);
			// if dest vertex is unvisited AND 
			// dest vertex doesn't exist in minDist OR dest vertex is new minimum distance
			if (visited.find(adjVertex.first) == visited.end() &&
				(curMinDist == minDist.end() || adjVertex.second < curMinDist->second))
			{	// Push this edge to queue for consideration
				pQ.push( make_pair<numType, Edge<T, numType>>
							( static_cast<numType>(adjVertex.second), 
						      Edge<T, numType>(curVertex, adjVertex.first, adjVertex.second)));
				minDist[adjVertex.first] = adjVertex.second;	// update minimum distance to adjVertex
			}
		}
		firstIteration = false;
	}
	return MST;
}

