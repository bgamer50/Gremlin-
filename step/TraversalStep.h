#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

#include <vector>
#include <string>

#include "GraphTraversal.h"

class Traverser;

enum TraversalStepType {MAP, FILTER, BARRIER, MODULATOR, SIDE_EFFECT};

class TraversalStep {
private:
	TraversalStepType type;
public:
	unsigned int uid;
	TraversalStep(TraversalStepType tsType, unsigned int id);
	virtual std::string getInfo();
	virtual void apply(GraphTraversal* trv, std::vector<Traverser*>& traversers);
};

#include "Traverser.h"

TraversalStep::TraversalStep(TraversalStepType tsType, unsigned int id) {
		type = tsType;
		uid = id;
}

std::string TraversalStep::getInfo() {
	return "UnknownTraversalStep{}";
}

void TraversalStep::apply(GraphTraversal* trv, TraverserSet& traversers) {};

#endif