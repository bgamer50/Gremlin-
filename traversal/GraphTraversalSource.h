#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include <string>
#include <vector>
#include <functional>

class Graph;
class Vertex;
class Edge;
class TraversalStep;
class GraphTraversal;
typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;

class GraphTraversalSource {
private:
	Graph* graph;

protected:
	std::vector<TraversalStrategy> strategies;

public:
	GraphTraversalSource(Graph* gr);
	
	Graph* getGraph();

	GraphTraversalSource* withStrategy(TraversalStrategy strategy);

	std::vector<TraversalStrategy>& getStrategies();

	virtual GraphTraversal* V() = 0;
	virtual GraphTraversal* V(Vertex* v) = 0;
	virtual GraphTraversal* E() = 0;
	virtual GraphTraversal* addV() = 0;
	virtual GraphTraversal* addV(std::string label) = 0;
	virtual GraphTraversal* addE(std::string label) = 0;
};

#include "traversal/GraphTraversal.h"
#include "strategy/TraversalStrategy.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "strategy/AddEdgeStepCompletionStrategy.h"
#include "strategy/RepeatStepCompletionStrategy.h"

GraphTraversalSource::GraphTraversalSource(Graph* gr) {
		graph = gr;
		this->withStrategy(add_edge_step_completion_strategy);
		this->withStrategy(repeat_step_completion_strategy);
}

GraphTraversalSource* GraphTraversalSource::withStrategy(TraversalStrategy strategy) {
		this->strategies.push_back(strategy);
		return this;
}

std::vector<TraversalStrategy>& GraphTraversalSource::getStrategies() {
		return this->strategies;
	}

Graph* GraphTraversalSource::getGraph() {
		return graph;
	}

#endif