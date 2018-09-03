#include "GraphTraversal.h"
#include "GraphTraversalSource.h"
#include "Graph.h"

template<typename T>
GraphTraversal<T>::GraphTraversal(GraphTraversalSource* src) {
	source = src;
}

template<typename T>
Graph* GraphTraversal<T>::getGraph() {
	return (*source).getGraph();
}

template<typename T>
GraphTraversalSource* GraphTraversal<T>::getTraversalSource() {
	return source;
}

template<typename T>
std::string GraphTraversal<T>::explain() {
	
}