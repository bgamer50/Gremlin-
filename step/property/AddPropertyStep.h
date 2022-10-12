#ifndef ADD_PROPERTY_STEP_H
#define ADD_PROPERTY_STEP_H

#define ADD_PROPERTY_STEP 0x75
#define ADD_PROPERTY_STEP_SIDE_EFFECT_KEY "__AddPropertyStep__originating_traverser__"

#include "step/TraversalStep.h"
#include "step/controlflow/InjectStep.h"
#include "step/math/MinStep.h"

#include "structure/Vertex.h"

#include "traversal/Scope.h"

#include <boost/any.hpp>

// Edge properties currently not supported.
class AddPropertyStep : public TraversalStep {
	private:
		Cardinality cardinality;
		std::string key;
		boost::any value;
	public:
		AddPropertyStep(std::string property_key, boost::any value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = SINGLE;
			this->key = std::string(property_key);
			this->value = boost::any(value);
		}

		AddPropertyStep(Cardinality card, std::string property_key, boost::any value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = card;
			this->key = std::string(property_key);
			this->value = boost::any(value);
		}

		Cardinality get_cardinality() { return this->cardinality; }

		std::string get_key() { return this->key; }

		boost::any get_value() { return this->value; };

		inline Element* get_element(boost::any& e) {
			const std::type_info& t = e.type();
			if(t == typeid(Vertex*)) return static_cast<Element*>(boost::any_cast<Vertex*>(e));
			else if(t == typeid(Edge*)) return static_cast<Element*>(boost::any_cast<Edge*>(e));
			else throw std::runtime_error("Add Property Step Error: Not an element!");
		}
		
		virtual void apply(GraphTraversal* current_traversal, TraverserSet& traversers) {
			if(this->value.type() == typeid(GraphTraversal*)) {
				GraphTraversal* ap_anonymous_trv = boost::any_cast<GraphTraversal*>(value);
				auto g = current_traversal->getTraversalSource();
				auto& eid_type = boost::any_cast<Vertex*>(traversers.front().get())->id().type();
				
				for(TraversalStep* step : ap_anonymous_trv->getSteps()) if(step->uid == MIN_STEP) {
					MinStep* min_step = static_cast<MinStep*>(step);
					min_step->set_scope_context(ScopeContext{Scope::local, ADD_PROPERTY_STEP_SIDE_EFFECT_KEY});
				}
				
				for(Traverser& trv : traversers) {
					boost::any v_id = boost::any_cast<Vertex*>(trv.get())->id();
					trv.get_side_effects()[ADD_PROPERTY_STEP_SIDE_EFFECT_KEY] = group_id_from_any(v_id);
				}

				TraverserSet temp_traversers(traversers.begin(), traversers.end());
				GraphTraversal new_trv(current_traversal->getTraversalSource(), ap_anonymous_trv);
				new_trv.setInitialTraversers(temp_traversers);
				new_trv.iterate();

				for(Traverser& trv : new_trv.getTraversers()) {
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
};

#endif