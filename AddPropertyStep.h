#ifndef ADD_PROPERTY_STEP_H
#define ADD_PROPERTY_STEP_H

#define ADD_PROPERTY_STEP 0x75
#include "TraversalStep.h"
#include "ApplicableStep.h"
#include "Vertex.h"

template<typename T>
class AddPropertyStep : public TraversalStep {
	private:
		Cardinality cardinality;
		std::string key;
		T value;
	public:
		AddPropertyStep(std::string property_key, T value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = SINGLE;
			this->key = property_key;
			this->value = value;
		}

		AddPropertyStep(Cardinality card, std::string property_key, T value)
		: TraversalStep(MAP, ADD_PROPERTY_STEP) {
			this->cardinality = card;
			this->key = property_key;
			this->value = value;
		}

		std::string get_key() { return this->key; }

		T get_value() { return this->value; };
		
		virtual void apply(Vertex* v) {
			v->property(cardinality, key, (void*)&value);
		}
};

#endif