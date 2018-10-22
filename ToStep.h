#ifndef TO_STEP_H
#define TO_STEP_H

#include "__.h"

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		GraphTraversal* to_traversal;
	public:
		ToStep(std::string side_effect_label)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = __->select(side_effect_label);
		}

		ToStep(Vertex* to_vertex)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = __->V(to_vertex);
		}

		ToStep(GraphTraversal* to_vertex_traversal)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = to_vertex_traversal;
		}

		GraphTraversal* getTraversal() {
			return to_traversal;
		}
};

#endif