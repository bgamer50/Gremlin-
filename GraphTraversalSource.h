#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include <string>

class GraphTraversal;
class Graph;
class Vertex;
class Edge;

class GraphTraversalSource {
private:
	Graph* graph;
public:
	GraphTraversalSource(Graph* gr) {
		graph = gr;
	}
	
	Graph* getGraph() {
		return graph;
	}

	virtual GraphTraversal* V() = 0;
	virtual GraphTraversal* V(Vertex* v) = 0;
	virtual GraphTraversal* E() = 0;
	virtual GraphTraversal* addV() = 0;
	virtual GraphTraversal* addV(std::string label) = 0;
	virtual GraphTraversal* addE(std::string label) = 0;
};

#endif