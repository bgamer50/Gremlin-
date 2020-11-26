#ifndef ADD_PROPERTY_STEP_H
#define ADD_PROPERTY_STEP_H

#define ADD_PROPERTY_STEP 0x75
#include "step/TraversalStep.h"
#include "step/InjectStep.h"
#include "structure/Vertex.h"
#include <boost/any.hpp>

// Edge properties currently not supported.
class AddPropertyStep : public TraversalStep {
	private:
		Cardinality cardinality;
		std::string key;
		boost::any value;
	public:
		AddPropertyStep(std::string property_key, boost::any& value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = SINGLE;
			this->key = std::string(property_key);
			this->value = boost::any(value);
		}

		AddPropertyStep(Cardinality card, std::string property_key, boost::any& value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = card;
			this->key = std::string(property_key);
			this->value = boost::any(value);
		}

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
				
				#pragma omp for
				//std::for_each(traversers.begin(), traversers.end(), [&](Traverser* trv) {
				for(int k = 0; k < traversers.size(); ++k) {
					Traverser& trv = traversers[k];
					//Element* e = get_element(trv->get());
					Vertex* e = boost::any_cast<Vertex*>(trv.get());
					GraphTraversal new_trv(current_traversal->getTraversalSource(), ap_anonymous_trv);
					
					// Execute traversal
					std::vector<boost::any> inj; inj.push_back(trv.get());
					InjectStep inject_step(inj);
					new_trv.insertStep(0, &inject_step);
					boost::any prop_value = new_trv.next();

					// Store the property; TODO deal w/ edges
					e->property(this->cardinality, this->key, prop_value);
					//std::cout << "property stored!\n";
				}
				//});
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