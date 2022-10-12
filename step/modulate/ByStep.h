#ifndef BY_STEP_H
#define BY_STEP_H

class GraphTraversal;
class TraversalStep;

#include <string>
#include <boost/any.hpp>

#define BY_STEP 0x92

class ByStep : public TraversalStep {
	private:
		boost::any arg;
	public:
		ByStep(boost::any arg);
		boost::any get() { return arg; }

		using TraversalStep::getInfo;
		virtual std::string getInfo();
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

ByStep::ByStep(boost::any arg)
: TraversalStep(MODULATOR, BY_STEP) {
	this->arg = arg;
}

std::string ByStep::getInfo() {
	return "ByStep(?)";
}

#endif