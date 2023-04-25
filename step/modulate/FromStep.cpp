#include "step/modulate/FromStep.h"

#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "traversal/SyntaxHelper.h"

FromStep::FromStep(GraphTraversal* from_vertex_traversal)
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = from_vertex_traversal;
}

FromStep::FromStep(std::string side_effect_label)
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = select(side_effect_label);
}

FromStep::FromStep(Vertex* to_vertex) 
: TraversalStep(MODULATOR, FROM_STEP) {
	arg = V(to_vertex);
}

std::string FromStep::getInfo() {
	return "FromStep {?}";
}
