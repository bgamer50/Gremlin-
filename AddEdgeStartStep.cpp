#include "AddEdgeStartStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

AddEdgeStartStep::AddEdgeStartStep(std::string label_arg)
: TraversalStep(map, ADD_EDGE_START_STEP) {
	label = label_arg;
}

// Return something like AddEdgeStarStep(label)
std::string AddEdgeStartStep::getInfo() {
	std::string info = "AddVertexStartStep(";
	info += label + ")";
	return info;
}