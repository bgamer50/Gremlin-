#ifndef HAS_STEP_H
#define HAS_STEP_H
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "TraversalStep.h"
#include "P.h"
#include "Vertex.h"

#define HAS_STEP 0x83

template<typename T>
class HasStep : public TraversalStep {
	private:
		std::string property_key_or_label;
		P<T>* predicate;
	public:
		HasStep(std::string key, P<T>* pred)
		: TraversalStep(FILTER, HAS_STEP) {
			predicate = pred;
			property_key_or_label = key;
		}

		virtual std::string	getInfo() {
			std::string info = "HasStep(";
			info = info + property_key_or_label + " " + predicate->getInfo() + ")";
			return info;
		}

		/**
            This is used for the expansion of has(prop) and has(prop, val)
            It tests whether the Vertex in question has the property/value
            in question and returns true if this is in fact the case.
		**/
		bool apply(Vertex* v) {
		    std::cout << "bvbvbvbv\n";
		    if(v->property(property_key_or_label) == nullptr) std::cout << "yhsdfier\n";
		    auto x = v->property(property_key_or_label)->value();
		    std::cout << "bvbvbvbv\n";
		    if(predicate == nullptr) return x == nullptr;
		    else return predicate->apply(&x);
		}
};

#endif
