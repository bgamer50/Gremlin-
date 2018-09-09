#include "TraversalStep.h"
#include <string>

TraversalStep::TraversalStep(TraversalStepType tsType, unsigned int id) {
	type = tsType;
	uid = id;
}

std::string TraversalStep::getInfo() {
	return "UnknownTraversalStep{}";
}