#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

#include <vector>
#include <string>

#include "traversal/GraphTraversal.h"

class Traverser;

enum TraversalStepType {MAP, FILTER, BARRIER, MODULATOR, SIDE_EFFECT};

class TraversalStep {
private:
	TraversalStepType type;

public:
	unsigned int uid;
	bool is_barrier;
	TraversalStep(TraversalStepType tsType, unsigned int id);
	TraversalStep(bool is_barrier, TraversalStepType tsType, unsigned int id);
	virtual std::string getInfo();
	virtual std::string getInfo(size_t indent);
	virtual void apply(GraphTraversal* trv, std::vector<Traverser>& traversers);

};

#include "traversal/Traverser.h"

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

#endif