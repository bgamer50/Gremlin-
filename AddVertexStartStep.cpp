#include "AddVertexStartStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

AddVertexStartStep::AddVertexStartStep(std::string label_arg)
: TraversalStep(MAP, ADD_VERTEX_START_STEP) {
	label = label_arg;
	has_label = true;
}

AddVertexStartStep::AddVertexStartStep()
: TraversalStep(MAP, ADD_VERTEX_START_STEP) {
	has_label = false;
}

// Return something like AddVertexStarStep([label])
std::string AddVertexStartStep::getInfo() {
	std::string info = "AddVertexStartStep(";
	info += has_label ? label : "";
	info += ")";
	return info;
}