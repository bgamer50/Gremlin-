#include "GraphTraversalSource.h"
#include "Graph.h"

GraphTraversalSource::GraphTraversalSource(Graph* gr) {
	graph = gr;
}

Graph* GraphTraversalSource::getGraph() {
	return graph;
}

/*GraphTraversal traversal() {
	return GraphTraversal(this);
}*/
