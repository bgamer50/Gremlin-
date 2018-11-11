#ifndef FROM_STEP_H
#define FROM_STEP_H

#include "__.h"

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		GraphTraversal<void*, Vertex>* from_traversal;
	public:
		FromStep(std::string side_effect_label)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = (GraphTraversal<void*, Vertex>*)__->select(side_effect_label);
		}

		FromStep(Vertex* to_vertex)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = __->V(to_vertex);
		}

		FromStep(GraphTraversal<void*, Vertex>* from_vertex_traversal)
		: TraversalStep(modulator, FROM_STEP) {
			from_traversal = from_vertex_traversal;
		}

		GraphTraversal<void*, Vertex>* getTraversal() {
			return from_traversal;
		}

		virtual std::string getInfo() {
			return "FromStep {\n" + this->from_traversal->explain() + "\n}";
		}
};

#endif