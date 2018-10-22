#include "GraphStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

GraphStep::GraphStep(GraphStepType gsType_arg, std::vector<void*> eids)
: TraversalStep(map, GRAPH_STEP) {
	this->gs_type = gsType_arg;
	this->element_ids = eids;
}

// Return something like GraphStep(VERTEX, {...}) or GraphStep(Edge, {})
std::string GraphStep::getInfo() {
	std::string info = "GraphStep(";
	info += this->gs_type == VERTEX ? "VERTEX" : "EDGE";
	info = info + ", " + (element_ids.size() > 0 ? "{...}" : "{}");
	return info + ")";
}

GraphStepType GraphStep::getType() { return this->gs_type; }

std::vector<void*> GraphStep::get_element_ids() { return this->element_ids; }