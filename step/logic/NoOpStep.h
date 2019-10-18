#ifndef NO_OP_STEP_H
#define NO_OP_STEP_H

#define NO_OP_STEP 0x00

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"

// Not technically part of Gremlin; just for
// use as a intermediate representation.
// Should not be confused with the identity
// step.
class NoOpStep: public TraversalStep {
	public:
		NoOpStep()
		: TraversalStep(MAP, NO_OP_STEP) {}

		virtual std::string getInfo() {
			return "NoOpStep()";
		}

		virtual void apply(GraphTraversal* traversal, TraverserSet traversers){}
};

#endif