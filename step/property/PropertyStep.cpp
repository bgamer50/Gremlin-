#include "step/property/PropertyStep.h"

#include "step/math/MinStep.h"

#include "structure/Element.h"
#include "structure/Vertex.h"

#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/arange.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/unique.h"
#include "maelstrom/algorithms/set.h"

#include <sstream>

namespace gremlinxx {

	PropertyStep::PropertyStep(std::string property_key, std::any value)
	: TraversalStep(MAP, PROPERTY_STEP) {
		this->cardinality = SINGLE;
		this->key = std::string(property_key);
		this->value = std::any(value);
	}

	PropertyStep::PropertyStep(Cardinality card, std::string property_key, std::any value)
	: TraversalStep(MAP, PROPERTY_STEP) {
		this->cardinality = card;
		this->key = std::string(property_key);
		this->value = std::any(value);
	}

	void PropertyStep::apply(GraphTraversal* current_traversal, gremlinxx::traversal::TraverserSet& traversers) {
		if(traversers.empty()) return;

		auto g = current_traversal->getTraversalSource();
		auto current_data_type = traversers.getCurrentDataType();
		if(current_data_type != g->getGraph()->get_vertex_dtype() && current_data_type != g->getGraph()->get_edge_dtype()) {
			throw std::domain_error("Can't add a property to something other than a vertex or edge!");
		}

		if(this->value.type() == typeid(GraphTraversal)) {
			GraphTraversal ap_anonymous_trv = std::any_cast<GraphTraversal>(value);
			
			for(auto& step : ap_anonymous_trv.getSteps()) {
				auto reduction_step = dynamic_cast<ReductionStep*>(step.get());
				if(reduction_step != nullptr) {
					reduction_step->set_scope_context(ScopeContext{Scope::local, PROPERTY_STEP_SIDE_EFFECT_KEY});
				}
			}

			GraphTraversal new_trv(current_traversal->getTraversalSource(), ap_anonymous_trv);
			new_trv.setInitialTraversers(traversers);

			// Need to initialize the scope context side effect
			auto indv = maelstrom::arange(traversers.getCurrentMemType(), traversers.size());
			new_trv.getTraverserSet().set_side_effects(PROPERTY_STEP_SIDE_EFFECT_KEY, std::move(indv));
			
			// Iterate the traversal
			new_trv.iterate();
			auto& retrieved_traversers = new_trv.getTraverserSet();

			// Will not update vertices or edges without a given property value

			maelstrom::vector original_keys = std::move(retrieved_traversers.getSideEffects()[PROPERTY_STEP_SIDE_EFFECT_KEY]);
			maelstrom::vector property_vals = retrieved_traversers.getTraverserData();
			retrieved_traversers.clear();

			auto unique_ix = maelstrom::unique(original_keys);
			original_keys = maelstrom::select(original_keys, unique_ix);
			property_vals = maelstrom::select(property_vals, unique_ix);
			
			maelstrom::vector elements = traversers.getTraverserData();
			elements = maelstrom::select(elements, original_keys);
			original_keys.clear();

			if(current_data_type == g->getGraph()->get_vertex_dtype()) {
				g->getGraph()->set_vertex_properties(this->key, elements, property_vals);
			} else {
				g->getGraph()->set_edge_properties(this->key, elements, property_vals);
			}
			
		}
		else {
			// Store the property
			auto elements = traversers.getTraverserData();
			auto unique_ix = maelstrom::unique(elements);
			elements = maelstrom::select(elements, unique_ix);
			unique_ix.clear();
			// FIXME deduplication may not be necessary but technically it is an API requirement
			// more research needs to be done on dropping that requirement

			maelstrom::vector val_vector(
				elements.get_mem_type(),
				g->get_dtype(this->value),
				elements.size()
			);
			maelstrom::set(val_vector, this->value);

			if(current_data_type == g->getGraph()->get_vertex_dtype()) {
				g->getGraph()->set_vertex_properties(this->key, elements, val_vector);
			} else {
				g->getGraph()->set_edge_properties(this->key, elements, val_vector);
			}
		}

		// Traversers aren't modified in this step.
	}

	std::string PropertyStep::getInfo() {
		std::stringstream sx;
		sx << "PropertyStep{" << this->key << "}";
		return sx.str();
	}

}