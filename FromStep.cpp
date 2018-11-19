#include "GraphTraversal.h"
#include "FromStep.h"

FromStep::FromStep(std::string side_effect_label)
		: TraversalStep(MODULATOR, FROM_STEP) {
			from_traversal = (GraphTraversal<void*, Vertex>*)__->select(side_effect_label);
		}

FromStep::FromStep(Vertex* to_vertex)
: TraversalStep(MODULATOR, FROM_STEP) {
	from_traversal = __->V(to_vertex);
}

FromStep::FromStep(GraphTraversal<void*, Vertex>* from_vertex_traversal)
: TraversalStep(MODULATOR, FROM_STEP) {
	from_traversal = from_vertex_traversal;
}

GraphTraversal<void*, Vertex>* FromStep::getTraversal() {
	return from_traversal;
}

std::string FromStep::getInfo() {
	return "FromStep {\n" + this->from_traversal->explain() + "\n}";
}