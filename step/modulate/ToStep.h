#ifndef TO_STEP_H
#define TO_STEP_H

#include "step/TraversalStep.h"
#include <string>
class GraphTraversal;
class Vertex;

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		boost::any arg;
	public:
		ToStep(std::string side_effect_label);

		ToStep(Vertex* to_vertex);

		ToStep(GraphTraversal* to_vertex_traversal)
		: TraversalStep(MODULATOR, TO_STEP) {
			arg = to_vertex_traversal;
		}

		boost::any get() { return arg; }

		using TraversalStep::getInfo;
		virtual std::string getInfo();
};

#include "traversal/GraphTraversal.h"

ToStep::ToStep(std::string side_effect_label)
: TraversalStep(MODULATOR, TO_STEP) {
	arg = (GraphTraversal*)select(side_effect_label);
}

ToStep::ToStep(Vertex* to_vertex)
: TraversalStep(MODULATOR, TO_STEP) {
	arg = V(to_vertex);
}

std::string ToStep::getInfo() {
	return "ToStep {?}";
}

#endif