#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include "Graph.h"

class GraphTraversalSource {
private:
	Graph * graph;
public:
	GraphTraversalSource(Graph* gr);
	Graph* getGraph();
};

#endif