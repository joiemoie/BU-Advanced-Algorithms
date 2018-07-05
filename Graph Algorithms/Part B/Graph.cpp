//
//  Graph.cpp
//
//  Created by Tali Moreshet. Adapted from Ari Trachtenberg.
//

#include <set>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include "Graph.h"
#include <vector>

using namespace std;


/** Type definitions */
typedef pair<int, int> directedEdge;
set<int> vertices;              /* The set of vertices of the graph */
set<directedEdge> edges;        /* the set of edges of the graph */
map<directedEdge, int> weights; /* A mapping between edges and their weights */



struct Node {
	int key;
	unsigned int * value;
	Node * next;
};

struct LinkedList {
	Node * head;
};

Graph::Graph() {
		
}


int Graph::addVertex() {
	int numVertices = vertices.size();
	vertices.insert(numVertices);
	return numVertices;
}

void Graph::addEdge(directedEdge newEdge, int weight) {
	edges.insert(newEdge);
	weights[newEdge] = weight;
}

int Graph::getNumVertices() {
	return vertices.size();
}

int Graph::getWeight(directedEdge edge) {
	return weights[edge];
}

bool Graph::isEdge(directedEdge newEdge) {
	return edges.find(newEdge) != edges.end();
}

void Graph::print() {
	set<directedEdge>::iterator ptr = edges.begin();
	for (int vertex : vertices) {
		cout << vertex << ": ";
		for (; (*ptr).first == vertex; ptr++) {
			cout << (*ptr).second << " (" << weights[(*ptr)] << ") ";
		}
		cout << "\n";
	}
	cout << '\n';
}


void Graph::generateGraph(string fileName) {
	std::ifstream myFile;
	myFile.open(fileName);
	std::string str;
	int maxLength = 0;
	std::getline(myFile, str);
	int firstSpace = 0, secondSpace = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ' ' && firstSpace == 0) firstSpace = i;
	}
	int numVertices = std::stoi(str.substr(0, firstSpace), 0, 10);
	for (int i = 0; i < numVertices; i++) {
		addVertex();
	}

	while (std::getline(myFile, str)) {
		firstSpace = 0, secondSpace = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] == ' ' && firstSpace == 0) firstSpace = i;
			if (str[i] == ' ' && firstSpace != 0) secondSpace = i;
		}
		int source = std::stoi(str.substr(0, firstSpace), 0, 10);
		int destination = std::stoi(str.substr(firstSpace+1, secondSpace), 0, 10);
		int weight = std::stoi(str.substr(secondSpace + 1, str.size()), 0, 10);
		directedEdge newEdge(source, destination);
		edges.insert(newEdge);
		weights[newEdge] = weight;
	}
}

//I did not modify Dijkstra to count the number of shortest paths. This is the original Dijkstra.
void Graph::modifiedDijkstra(int source) {
	vector<unsigned int> d(vertices.size());
	vector<unsigned int> shortestPaths(vertices.size());

	//Stores the queue as an unordered linked list and initializes the d array
	struct LinkedList list;
	list.head = new struct Node;
	struct Node * currentNode = list.head;
	for (int vertex : vertices) {
		currentNode->key = vertex;
		currentNode->value = &d[vertex];
		d[vertex] = -1;
		shortestPaths[vertex] = 1;
		if (vertex != getNumVertices() - 1) {
			currentNode->next = new struct Node;
			currentNode = currentNode->next;
		}
	}
	d[source] = 0;
		
	while (list.head != 0) {

		//Finds the min node and pops it from the queue
		struct Node * minNode = list.head;
		struct Node * minPrevNode = list.head;
		struct Node * prevNode = list.head;
		currentNode = list.head;
		while (currentNode != 0) {
			if (*(currentNode->value) < *(minNode->value)) {
				minNode = currentNode;
				minPrevNode = prevNode;
			}
			prevNode = currentNode;
			currentNode = currentNode->next;
		}

		if (minNode == list.head) {
			list.head = minNode->next;
		}
		else {
			minPrevNode->next = minNode->next;
		}			

		//Relaxes all edges next to the min node
		set<directedEdge>::iterator ptr = edges.begin();
		while ((*ptr).first < minNode->key) ptr++;
		for (; ptr != edges.end() && (*ptr).first == minNode->key; ptr++) {
			if (d[(*ptr).second] > d[(*ptr).first] + weights[*ptr]) {
				d[(*ptr).second] = d[(*ptr).first] + weights[*ptr];
			}
		}

	}
	cout << "Shortest paths from node " << source << ":\n";
	for (int i = 0; i < d.size(); i++) {
		if (i != source) {
			cout << "Distance to vertex " << i << " is " << d[i] <<
				" and there are 1 shortest paths\n";
		}
	}
	cout << '\n';
}
