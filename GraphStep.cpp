#include "GraphStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

GraphStep::GraphStep(GraphStepType gsType_arg, std::vector<boost::any> eids)
: TraversalStep(MAP, GRAPH_STEP) {
	this->gs_type = gsType_arg;
	for(boost::any id_ctr : eids) this->element_ids.push_back(id_ctr);
}

// Return something like GraphStep(VERTEX, {...}) or GraphStep(Edge, {})
std::string GraphStep::getInfo() {
	std::string info = "GraphStep(";
	info += this->gs_type == VERTEX ? "VERTEX" : "EDGE";
	info = info + ", " + (element_ids.size() > 0 ? "{...}" : "{}");
	return info + ")";
}

GraphStepType GraphStep::getType() { return this->gs_type; }

std::vector<boost::any> GraphStep::get_element_ids() { return this->element_ids; }