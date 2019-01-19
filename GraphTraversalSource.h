#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include <string>
class Graph;
class Vertex;
class Edge;
class GraphTraversal;

class GraphTraversalSource {
private:
	Graph* graph;
public:
	GraphTraversalSource(Graph* gr);
	Graph* getGraph();
	virtual GraphTraversal* V() = 0;
	virtual GraphTraversal* V(Vertex* v) = 0;
	virtual GraphTraversal* E() = 0;
	virtual GraphTraversal* addV() = 0;
	virtual GraphTraversal* addV(std::string label) = 0;
	virtual GraphTraversal* addE(std::string label) = 0;
};

#endif