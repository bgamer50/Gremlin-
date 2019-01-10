#include "VertexStep.h"
#include "TraversalStep.h"
#include "GraphStep.h"
#include <string>
#include <vector>
#include <algorithm>

VertexStep::VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
	direction = dir;
	for_each(edge_labels_arg.begin(), edge_labels_arg.end(), [this](std::string str){ this->edge_labels.insert(str); });
	this->gsType = gsType_arg;
}

VertexStep::VertexStep(Direction dir, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
	direction = dir;
	this->gsType = gsType_arg;
}

Direction VertexStep::get_direction() {
	return this->direction;
}

std::set<std::string> VertexStep::get_labels() {
	return this->edge_labels;
}

// Return something like VertexStep(OUT, {x, y}, VERTEX) or just VertexStep(BOTH, VERTEX)
std::string VertexStep::getInfo() {
	std::string info = "VertexStep(";
	info += (direction == IN ? "IN" : direction == OUT ? "OUT" : "BOTH");
	info += ", ";
	if(!edge_labels.empty()) {
		info += "{";
		auto p = edge_labels.begin();
		for(int k = 0; k < edge_labels.size() - 1; k++) info = info + *(p++) + ", ";
		info = info + *p + "}";
	}
	else info += "{}";
	info = info + ", " + (gsType == VERTEX ? "VERTEX" : "EDGE");
	return info + ")";
}