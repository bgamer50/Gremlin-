#ifndef BY_STEP_H
#define BY_STEP_H

class GraphTraversal;
class TraversalStep;

#include <string>

#define BY_STEP 0x92

class ByStep : public TraversalStep {
	private:
		GraphTraversal* by_traversal;
	public:
		ByStep(GraphTraversal* by_traversal);

		GraphTraversal* getTraversal();

		virtual std::string getInfo();
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

ByStep::ByStep(GraphTraversal* by_traversal)
: TraversalStep(MODULATOR, BY_STEP) {
	this->by_traversal = by_traversal;
}

GraphTraversal* ByStep::getTraversal() {
	return this->by_traversal;
}

std::string ByStep::getInfo() {
	return "ByStep {\n" + this->by_traversal->explain() + "\n}";
}

#endif