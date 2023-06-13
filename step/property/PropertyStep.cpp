#include "step/property/PropertyStep.h"

#include "step/math/MinStep.h"

#include "structure/Element.h"
#include "structure/Vertex.h"

#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

namespace gremlinxx {

	PropertyStep::PropertyStep(std::string property_key, boost::any value)
	: TraversalStep(MAP, ADD_PROPERTY_STEP) {
		this->cardinality = SINGLE;
		this->key = std::string(property_key);
		this->value = boost::any(value);
	}

	PropertyStep::PropertyStep(Cardinality card, std::string property_key, boost::any value)
	: TraversalStep(MAP, ADD_PROPERTY_STEP) {
		this->cardinality = card;
		this->key = std::string(property_key);
		this->value = boost::any(value);
	}

	void PropertyStep::apply(GraphTraversal* current_traversal, gremlinxx::traversal::TraverserSet& traversers) {
		auto g = current_traversal->getTraversalSource();
		if(traversers.getCurrentDataType() != g->getGraph()->get_vertex_dtype()) {
			throw std::runtime_error("Can't add a property to something other than a vertex!");
		}

		if(this->value.type() == typeid(GraphTraversal*)) {
			GraphTraversal* ap_anonymous_trv = boost::any_cast<GraphTraversal*>(value);
			
			for(TraversalStep* step : ap_anonymous_trv->getSteps()) {
				auto reduction_step = dynamic_cast<ReductionStep*>(step);
				if(reduction_step != nullptr) {
					reduction_step->set_scope_context(ScopeContext{Scope::local, ADD_PROPERTY_STEP_SIDE_EFFECT_KEY});
				}
			}
			
			// Need to initialize the scope context side effect
			traversers.set_side_effects(ADD_PROPERTY_STEP_SIDE_EFFECT_KEY, traversers.getTraverserData());

			GraphTraversal new_trv(current_traversal->getTraversalSource(), ap_anonymous_trv);
			new_trv.setInitialTraversers(traversers);
			new_trv.iterate();

			auto retrieved_traversers = new_trv.getTraversers();
			if(retrieved_traversers.size() < traversers.size()) {
				throw std::runtime_error("One of more traversers did not produce a valid property value!");
			}

			for(Traverser& trv : retrieved_traversers) {
				scope_group_t g_id = boost::any_cast<scope_group_t>(trv.get_side_effects()[ADD_PROPERTY_STEP_SIDE_EFFECT_KEY]);
				boost::any prop_value = trv.get();
				Vertex* v = boost::any_cast<Vertex*>(g->V(any_from_group_id(g_id, eid_type))->next());
				v->property(this->cardinality, this->key, prop_value);
			}
		} 
		else {
			// Store the propety; TODO deal w/ edges
			std::for_each(traversers.begin(), traversers.end(), [&](Traverser& trv){
				Vertex* e = boost::any_cast<Vertex*>(trv.get());
				e->property(this->cardinality, this->key, this->value);	
			});
			//std::cout << "property stored!\n";
		}

		// Traversers aren't modified in this step.
	}

}