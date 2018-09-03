#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Edge.h"
#include "Vertex.h"

using namespace std;
class GraphTraversalSource;

class Graph {
public:
	virtual GraphTraversalSource traversal() = 0;
	virtual vector<Vertex> vertices() = 0;
	virtual vector<Edge> edges() = 0;
};

#endif