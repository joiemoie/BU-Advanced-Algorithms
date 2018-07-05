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