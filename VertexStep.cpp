#include "VertexStep.h"
#include "TraversalStep.h"
#include "GraphStep.h"
#include <string>
#include <vector>

VertexStep::VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg)
: TraversalStep(map, VERTEX_STEP) {
	direction = dir;
	edge_labels = edge_labels_arg;
	gsType = gsType_arg;
}

// Return something like VertexStep(OUT, {x, y}, VERTEX) or just VertexStep(BOTH, VERTEX)
std::string VertexStep::getInfo() {
	std::string info = "VertexStep(";
	info += (direction == IN ? "IN" : direction == OUT ? "OUT" : "BOTH");
	info += ", ";
	if(edge_labels.size() > 0) {
		info += "{";
		for(int k = 0; k < edge_labels.size() - 1; k++) info = info + edge_labels[k] + ", ";
		info = info + edge_labels[edge_labels.size() - 1] +  "}";
	}
	else info += "{}";
	info = info + ", " + (gsType == VERTEX ? "VERTEX" : "EDGE");
	return info + ")";
}