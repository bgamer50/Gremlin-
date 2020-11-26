#ifndef GRAPH_H
#define GRAPH_H

#include <list>

class Edge;
class Vertex;
class GraphTraversalSource;

class Graph {
public:
	Graph(){}
	virtual GraphTraversalSource* traversal() = 0;
	virtual std::list<Vertex*> vertices() = 0;
	virtual std::list<Edge*>& edges() = 0;
	virtual Vertex* add_vertex(std::string label) = 0;
	virtual Vertex* add_vertex() = 0;
	virtual Edge* add_edge(Vertex* from_vertex, Vertex* to_vertex, std::string label) = 0;
};

#include "structure/Edge.h"
#include "structure/Vertex.h"
#include "traversal/GraphTraversalSource.h"

#endif