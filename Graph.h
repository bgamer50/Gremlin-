#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Edge.h"
#include "Vertex.h"
#include "GraphTraversalSource.h"

using namespace std;

class Graph {
public:
	Graph();
	virtual GraphTraversalSource* traversal() = 0;
	virtual vector<Vertex*> vertices() = 0;
	virtual vector<Edge*> edges() = 0;
};

#endif