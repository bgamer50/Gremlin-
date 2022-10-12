#ifndef FROM_STEP_H
#define FROM_STEP_H

class GraphTraversal;
class TraversalStep;
class Vertex;

#include <string>

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		boost::any arg;
	public:
		FromStep(std::string side_effect_label);

		FromStep(Vertex* to_vertex);

		FromStep(GraphTraversal* from_vertex_traversal);

		using TraversalStep::getInfo;
		virtual std::string getInfo();

		boost::any get() { return arg; }
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

FromStep::FromStep(GraphTraversal* from_vertex_traversal)
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = from_vertex_traversal;
}

FromStep::FromStep(std::string side_effect_label)
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = __->select(side_effect_label);
}

FromStep::FromStep(Vertex* to_vertex) 
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = __->V(to_vertex);
}

std::string FromStep::getInfo() {
	return "FromStep {?}";
}

#endif