#include "GraphTraversal.h"
#include "GraphTraversalSource.h"
#include "Graph.h"

GraphTraversal::GraphTraversal(GraphTraversalSource* src) {
	source = src;
}

Graph* GraphTraversal::getGraph() {
	return (*source).getGraph();
}

GraphTraversalSource* GraphTraversal::getTraversalSource() {
	return source;
}