#include "GraphTraversalSource.h"
#include "Graph.h"
#include "VertexStep.h"
#include "GraphStep.h"
#include "HasStep.h"
#include "Direction.h"

/*
	JIT compilation is supposed to check to see if these steps are valid;
	this has to be implemented at the actual compilation rather than
	pre-compilation.
*/

GraphTraversal::GraphTraversal(GraphTraversalSource* src) {
	source = src;
}

Graph* GraphTraversal::getGraph() {
	return (*source).getGraph();
}

GraphTraversalSource* GraphTraversal::getTraversalSource() {
	return source;
}

std::string GraphTraversal::explain() {
	std::string explanation = "GraphTraversal {\n";
	for(int k = 0; k < steps.size(); k++) explanation += steps[k]->getInfo() + "\n";

	return explanation + "}";
}

GraphTraversal* GraphTraversal::appendStep(TraversalStep* step) {
	steps.push_back(step);
	return this;
}

GraphTraversal* GraphTraversal::V() {
	return this->appendStep(new GraphStep(VERTEX, {}));
}

GraphTraversal* GraphTraversal::outE() {
	return this->appendStep(new VertexStep(OUT, {}, EDGE));
}

GraphTraversal* GraphTraversal::outE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, EDGE));
}

GraphTraversal* GraphTraversal::inE() {
	return this->appendStep(new VertexStep(IN, {}, EDGE));
}

GraphTraversal* GraphTraversal::inE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, EDGE));
}

GraphTraversal* GraphTraversal::bothE() {
	return this->appendStep(new VertexStep(BOTH, {}, EDGE));
}

GraphTraversal* GraphTraversal::bothE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, EDGE));
}

GraphTraversal* GraphTraversal::out() {
	return this->appendStep(new VertexStep(OUT, {}, VERTEX));
}

GraphTraversal* GraphTraversal::out(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, VERTEX));
}

GraphTraversal* GraphTraversal::in() {
	return this->appendStep(new VertexStep(IN, {}, VERTEX));
}

GraphTraversal* GraphTraversal::in(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, VERTEX));
}

GraphTraversal* GraphTraversal::both() {
	return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
}

GraphTraversal* GraphTraversal::both(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
}

GraphTraversal* GraphTraversal::has(std::string key, int value) {
	return this->appendStep(new HasStep<int>(key, new P<int>(EQ, value, value)));
}

GraphTraversal* GraphTraversal::has(std::string key, std::string value) {
	return this->appendStep(new HasStep<std::string>(key, new P<std::string>(EQ, value, value)));
}

template <typename T>
GraphTraversal* GraphTraversal::has(std::string key, P<T> pred) {
	return this->appendStep(new HasStep<T>(key, pred));
}
