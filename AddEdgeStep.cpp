#include "AddEdgeStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

AddEdgeStep::AddEdgeStep(std::string label_arg)
: TraversalStep(map, ADD_EDGE_STEP) {
	label = label_arg;
}

// Return something like AddEdgeStep(label)
std::string AddEdgeStep::getInfo() {
	std::string info = "AddVertexStep(";
	info += label + ")";
	return info;
}