#include <vector>
#include "Edge.h"
#include "Vertex.h"
#include "Graph.h"
#include "GraphTraversalSource.h"


GraphTraversalSource Graph::traversal() {
	return GraphTraversalSource(this);
}

// This will eventually call a GraphTraversal.
std::vector<Vertex> Graph::vertices() {
	std::vector<Vertex> arr;
	Vertex v = Vertex(100L);
	arr.push_back(v);
	return arr;
}

// This will eventually call a GraphTraversal.
std::vector<Edge> Graph::edges() {
	std::vector<Edge> arr;
	Edge e = Edge(20L);
	arr.push_back(e);
	return arr;
}