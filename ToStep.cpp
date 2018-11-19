#include "GraphTraversal.h"
#include "ToStep.h"

ToStep::ToStep(std::string side_effect_label)
: TraversalStep(MODULATOR, TO_STEP) {
	to_traversal = (GraphTraversal<void*, Vertex>*)__->select(side_effect_label);
}

ToStep::ToStep(Vertex* to_vertex)
: TraversalStep(MODULATOR, TO_STEP) {
	to_traversal = __->V(to_vertex);
}

ToStep::ToStep(GraphTraversal<void*, Vertex>* to_vertex_traversal)
: TraversalStep(MODULATOR, TO_STEP) {
	to_traversal = to_vertex_traversal;
}

GraphTraversal<void*, Vertex>* ToStep::getTraversal() {
	return to_traversal;
}

std::string ToStep::getInfo() {
	return "ToStep {\n" + this->to_traversal->explain() + "\n}";
}