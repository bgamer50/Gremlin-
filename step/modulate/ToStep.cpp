#include "step/modulate/ToStep.h"

#include "traversal/GraphTraversal.h"
#include "traversal/SyntaxHelper.h"
#include "structure/Vertex.h"

namespace gremlinxx {
		
	ToStep::ToStep(GraphTraversal* to_vertex_traversal)
	: TraversalStep(MODULATOR, TO_STEP) {
		arg = to_vertex_traversal;
	}

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

}