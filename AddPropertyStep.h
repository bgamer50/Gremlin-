#ifndef ADD_PROPERTY_STEP_H
#define ADD_PROPERTY_STEP_H

#define ADD_PROPERTY_STEP 0x75
#include "TraversalStep.h"
#include "ApplicableStep.h"
#include "Vertex.h"

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
		
		virtual void apply(Vertex* v) {
			v->property(cardinality, key, value);
		}
};

#endif