#include "step/TraversalStep.h"

#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

TraversalStep::TraversalStep(bool is_barrier, TraversalStepType tsType, unsigned int id) {
		this->type = tsType;
		this->uid = id;
		this->is_barrier = is_barrier;
}

TraversalStep::TraversalStep(TraversalStepType tsType, unsigned int id) : TraversalStep(false, tsType, id){}

std::string TraversalStep::getInfo() {
	return "UnknownTraversalStep{}";
}

std::string TraversalStep::getInfo(size_t indent) {
	std::string s = "";
	for(size_t k = 0; k < indent; ++k) s += "  ";

	return s + getInfo();
}

void TraversalStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
	throw std::runtime_error("Non-executable traversal step! (" + std::to_string(uid) + ")");
};