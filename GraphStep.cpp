#include "GraphStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

GraphStep::GraphStep(GraphStepType gsType_arg, std::vector<void*> eids)
: TraversalStep(map, GRAPH_STEP) {
	gsType = gsType_arg;
	element_ids = eids;
}

// Return something like GraphStep(VERTEX, {...}) or GraphStep(Edge, {})
std::string GraphStep::getInfo() {
	std::string info = "GraphStep(";
	info += gsType == VERTEX ? "VERTEX" : "EDGE";
	info = info + ", " + (element_ids.size() > 0 ? "{...}" : "{}");
	return info + ")";
}