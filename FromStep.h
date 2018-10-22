#ifndef FROM_STEP_H
#define FROM_STEP_H

#include "__.h"

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		GraphTraversal* from_traversal;
	public:
		FromStep(std::string side_effect_label)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = __->select(side_effect_label);
		}

		FromStep(Vertex* to_vertex)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = __->V(to_vertex);
		}

		FromStep(GraphTraversal* from_vertex_traversal)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = from_vertex_traversal;
		}

		GraphTraversal* getTraversal() {
			return from_traversal;
		}
};

#endif