#include "VertexStep.h"
#include "TraversalStep.h"
#include "GraphStep.h"
#include <string>
#include <vector>
#include <algorithm>

VertexStep::VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
	direction = dir;
	this->edge_labels = new std::vector<std::string>;
	for_each(edge_labels_arg.begin(), edge_labels_arg.end(), [this](std::string str){ this->edge_labels->push_back(str); });
	this->gsType = gsType_arg;
}

VertexStep::VertexStep(Direction dir, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
	direction = dir;
	this->edge_labels = new std::vector<std::string>;
	this->gsType = gsType_arg;
}

// Return something like VertexStep(OUT, {x, y}, VERTEX) or just VertexStep(BOTH, VERTEX)
std::string VertexStep::getInfo() {
	std::string info = "VertexStep(";
	info += (direction == IN ? "IN" : direction == OUT ? "OUT" : "BOTH");
	info += ", ";
	if(edge_labels->size() > 0) {
		info += "{";
		for(int k = 0; k < edge_labels->size() - 1; k++) info = info + edge_labels->at(k) + ", ";
		info = info + edge_labels->at(edge_labels->size() - 1) +  "}";
	}
	else info += "{}";
	info = info + ", " + (gsType == VERTEX ? "VERTEX" : "EDGE");
	return info + ")";
}