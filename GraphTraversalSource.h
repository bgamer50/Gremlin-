#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include "GraphTraversal.h"
class Graph;

class GraphTraversalSource {
private:
	Graph* graph;
public:
	GraphTraversalSource(Graph* gr);
	Graph* getGraph();
	virtual GraphTraversal* V() = 0;
	virtual GraphTraversal* E() = 0;
	virtual GraphTraversal* addV() = 0;
};

#endif