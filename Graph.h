#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Edge.h"
#include "Vertex.h"

using namespace std;
class GraphTraversalSource;

class Graph {
public:
	GraphTraversalSource traversal();
	vector<Vertex> vertices();
	vector<Edge> edges();
};

#endif