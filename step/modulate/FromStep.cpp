#include "step/modulate/FromStep.h"

#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "traversal/SyntaxHelper.h"

namespace gremlinxx {
	
	FromStep::FromStep(GraphTraversal from_vertex_traversal)
	: TraversalStep(MODULATOR, FROM_STEP) {
		traversal.emplace(std::move(from_vertex_traversal));
	}

	FromStep::FromStep(std::string side_effect_label)
	: TraversalStep(MODULATOR, FROM_STEP) {
		GraphTraversal trv = select(side_effect_label);
		traversal.emplace(std::move(trv));
	}

	FromStep::FromStep(Vertex to_vertex) 
	: TraversalStep(MODULATOR, FROM_STEP) {
		GraphTraversal trv = V(to_vertex);
		traversal.emplace(std::move(trv));
	}

	std::string FromStep::getInfo() {
		return "FromStep {?}";
	}

}