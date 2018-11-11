#ifndef TO_STEP_H
#define TO_STEP_H

#include "__.h"

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		GraphTraversal<void*, Vertex>* to_traversal;
	public:
		ToStep(std::string side_effect_label)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = (GraphTraversal<void*, Vertex>*)__->select(side_effect_label);
		}

		ToStep(Vertex* to_vertex)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = __->V(to_vertex);
		}

		ToStep(GraphTraversal<void*, Vertex>* to_vertex_traversal)
		: TraversalStep(modulator, TO_STEP) {
			to_traversal = to_vertex_traversal;
		}

		GraphTraversal<void*, Vertex>* getTraversal() {
			return to_traversal;
		}

		virtual std::string getInfo() {
			return "ToStep {\n" + this->to_traversal->explain() + "\n}";
		}
};

#endif