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

void TraversalStep::apply(GraphTraversal* trv, TraverserSet& traversers) {};

#endif