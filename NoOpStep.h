#ifndef NO_OP_STEP_H
#define NO_OP_STEP_H

#define NO_OP_STEP 0x00

#include "TraversalStep.h"

// Not technically part of Gremlin; just for
// use as a intermediate representation.
// Should not be confused with the identity
// step.
class NoOpStep: public TraversalStep {
	public:
		NoOpStep()
		: TraversalStep(map, NO_OP_STEP) {}

		virtual std::string getInfo() {
			return "NoOpStep()";
		}
};

#endif