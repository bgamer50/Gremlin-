#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include <string>
class Graph;
class Vertex;
class Edge;
template<typename U, typename W>
class GraphTraversal;

class GraphTraversalSource {
private:
	Graph* graph;
public:
	GraphTraversalSource(Graph* gr);
	Graph* getGraph();
	virtual GraphTraversal<Vertex, Vertex>* V() = 0;
	virtual GraphTraversal<Edge, Edge>* E() = 0;
	virtual GraphTraversal<Vertex, Vertex>* addV() = 0;
	virtual GraphTraversal<Vertex, Vertex>* addV(std::string label) = 0;
	virtual GraphTraversal<Edge, Edge>* addE(std::string label) = 0;
};

#endif