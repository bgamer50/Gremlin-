#ifndef TO_STEP_H
#define TO_STEP_H

#include "step/TraversalStep.h"
#include <string>
class GraphTraversal;
class Vertex;

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		GraphTraversal* to_traversal;
	public:
		ToStep(std::string side_effect_label);

		ToStep(Vertex* to_vertex);

		ToStep(GraphTraversal* to_vertex_traversal)
		: TraversalStep(MODULATOR, TO_STEP) {
			to_traversal = to_vertex_traversal;
		}

		GraphTraversal* getTraversal() {
			return to_traversal;
		}

		virtual std::string getInfo();
};

#include "traversal/GraphTraversal.h"

ToStep::ToStep(std::string side_effect_label)
: TraversalStep(MODULATOR, TO_STEP) {
	to_traversal = (GraphTraversal*)__->select(side_effect_label);
}

ToStep::ToStep(Vertex* to_vertex)
: TraversalStep(MODULATOR, TO_STEP) {
	to_traversal = __->V(to_vertex);
}

std::string ToStep::getInfo() {
	return "ToStep {\n" + this->to_traversal->explain() + "\n}";
}

#endif