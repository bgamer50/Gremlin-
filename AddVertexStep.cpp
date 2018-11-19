#include "AddVertexStep.h"
#include "TraversalStep.h"
#include <string>
#include <vector>

AddVertexStep::AddVertexStep(std::string label_arg)
: TraversalStep(MAP, ADD_VERTEX_STEP) {
	label = label_arg;
	has_label = true;
}

AddVertexStep::AddVertexStep()
: TraversalStep(MAP, ADD_VERTEX_STEP) {
	has_label = false;
}

// Return something like AddVertexStep([label])
std::string AddVertexStep::getInfo() {
	std::string info = "AddVertexStep(";
	info += has_label ? label : "";
	info += ")";
	return info;
}